#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <system_error>

#include "tLEDControlServer.h"

const char* c_pipeName = "/tmp/myfifo1";

class TPipeMakeHolder
{
public:
  TPipeMakeHolder() = delete;
  TPipeMakeHolder(const TPipeMakeHolder&) = delete;
  TPipeMakeHolder& operator=(const TPipeMakeHolder&) = delete;

  TPipeMakeHolder(const std::string& astrPipeName)
  : m_strPipeName(astrPipeName)
  {
    int nResult = mkfifo(m_strPipeName.c_str(), S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    if((nResult != 0) && (errno != EEXIST))
      throw std::system_error(errno, std::system_category(), "Cannot create named pipe");
  }

  ~TPipeMakeHolder()
  {
    if(std::remove(m_strPipeName.c_str()) != 0)
      perror("Cannot delete fifo");
  }

  const std::string& getName() const
  {
    return m_strPipeName;
  }

private:
  std::string m_strPipeName;
};

int main(int argc, char* argv[])
{
  std::string strPipeName;
  if(argc == 2)
    strPipeName = argv[1];
  else
    strPipeName = c_pipeName;

  try
  {
    TPipeMakeHolder pipeIn(strPipeName + "_sr");
    TPipeMakeHolder pipeOut(strPipeName + "_sw");

    TLEDControlServer server(
      pipeIn.getName(),
      pipeOut.getName());

    server.run();
  }
  catch(const std::system_error& ex)
  {
    std::cerr << "Error in main: " << ex.code() << " - " << ex.what() << '\n';
    return 1;
  }
  
  return 0;
}