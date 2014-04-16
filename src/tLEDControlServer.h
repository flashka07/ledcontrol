#ifndef tLEDControlServerH
#define tLEDControlServerH
#include <string>
#include <memory>
#include <unordered_map>
#include "tLED.h"

class ILEDCommand;

class TLEDControlServer
{
public:
  TLEDControlServer() = delete;
  TLEDControlServer(const TLEDControlServer&) = delete;
  TLEDControlServer& operator=(const TLEDControlServer&) = delete;

  TLEDControlServer(
    const std::string& strPipeNameIn,
    const std::string& strPipeNameOut);

  void run();

private:
  typedef std::shared_ptr<ILEDCommand> TLEDCommandPtr;
  typedef std::unordered_map<std::string, TLEDCommandPtr> TLEDCommandsMap;

  int initLED();
  void loop();

  std::unique_ptr<TLED> m_spLed;
  std::string m_strPipeNameIn;
  std::string m_strPipeNameOut;
  TLEDCommandsMap m_CommandsMap;
};

#endif