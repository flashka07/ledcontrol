#include <stdexcept>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include "tLEDControlServer.h"
#include "tLEDCommand.h"
#include "tPipe.h"

TLEDControlServer::TLEDControlServer(
  const std::string& strPipeNameIn,
  const std::string& strPipeNameOut)
  : m_strPipeNameIn(strPipeNameIn),
    m_strPipeNameOut(strPipeNameOut)
{
  m_CommandsMap["set-led-state"] = std::make_shared<TLEDCmdSetStatus>();
  m_CommandsMap["get-led-state"] = std::make_shared<TLEDCmdGetStatus>();
  m_CommandsMap["set-led-color"] = std::make_shared<TLEDCmdSetColor>();
  m_CommandsMap["get-led-color"] = std::make_shared<TLEDCmdGetColor>();
  m_CommandsMap["set-led-rate"] = std::make_shared<TLEDCmdSetFrequency>();
  m_CommandsMap["get-led-rate"] = std::make_shared<TLEDCmdGetFrequency>();
}

void TLEDControlServer::run()
{
  int nResult = initLED();
  if(nResult)
    throw std::runtime_error("Cannot initialize LED");

  std::cout << "\nLED control server started\n";

  loop();
}

int TLEDControlServer::initLED()
{
  m_spLed.reset(new TLED);
  return 0;
}

void TLEDControlServer::loop()
{
  while(true)
  {
    TPipe pipeR(m_strPipeNameIn, O_RDONLY);
    TPipe pipeW(m_strPipeNameOut, O_WRONLY);

    std::istringstream inStream(pipeR.read());
    std::string strCommand;
    std::string strArgs;

    inStream >> strCommand >> strArgs;
    if(strCommand.size() == 0)
      continue;

    if(strCommand == "exit")
    {
      std::cout << "Received 'exit' command. Server will stop.\n";
      break;
    }

    TLEDCommandsMap::const_iterator i = m_CommandsMap.find(strCommand);
    if(i == m_CommandsMap.cend())
    {
      std::cout << "Command '" << strCommand << "' is not implemented\n";
      pipeW.write(TLEDCommandResult(TLEDCommandResult::enTLEDCmdFail).toStringShort());
      continue;
    }

    TLEDCommandResult result;
    try
    {
      result = i->second->execute(*m_spLed.get(), strArgs);
    }
    catch(std::runtime_error& ex)
    {
      std::cerr << "Error handling command '" << strCommand << "' - " << ex.what() << '\n';
      result = TLEDCommandResult(TLEDCommandResult::enTLEDCmdFail);
    }
    pipeW.write(result.toString());
  }
}