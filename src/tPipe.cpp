#include <string>
#include <system_error>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include "tPipe.h"

TPipe::TPipe(const std::string& strPipeName, mode_t mode)
: m_fifo(open(strPipeName.c_str(), mode))
{
  if(m_fifo < 0)
    throw std::system_error(errno, std::system_category(), "Cannot open fifo");
}

TPipe::~TPipe()
{
  close(m_fifo);
}

std::string TPipe::read()
{
  const size_t c_szBufSize = PIPE_BUF;
  char buf[c_szBufSize] = {0};
  size_t szRead = ::read(m_fifo, buf, c_szBufSize);
  if(szRead > 0)
  {
    return buf;
  }
  else if(szRead < 0)
  {
    perror("Error reading from fifo");
  }
  return "";
}


void TPipe::write(const std::string& data)
{
  size_t szWritten = ::write(m_fifo, data.c_str(), data.size());
  if(szWritten == 0)
    printf("Cannot write anything to pipe. No errors, but written 0 bytes.");
  if(szWritten < 0)
    perror("Error writing to fifo");
}