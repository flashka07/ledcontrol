#ifndef tLEDCommandH
#define tLEDCommandH
#include "iLEDCommand.h"

class TLEDCmdSetStatus : public ILEDCommand
{
public:
  TLEDCommandResult execute(TLED& led, const std::string& strArgs);
};

class TLEDCmdGetStatus : public ILEDCommand
{
public:
  TLEDCommandResult execute(TLED& led, const std::string& strArgs);
};

class TLEDCmdSetColor : public ILEDCommand
{
public:
  TLEDCommandResult execute(TLED& led, const std::string& strArgs);
};

class TLEDCmdGetColor : public ILEDCommand
{
public:
  TLEDCommandResult execute(TLED& led, const std::string& strArgs);
};

class TLEDCmdSetFrequency : public ILEDCommand
{
public:
  TLEDCommandResult execute(TLED& led, const std::string& strArgs);
};

class TLEDCmdGetFrequency : public ILEDCommand
{
public:
  TLEDCommandResult execute(TLED& led, const std::string& strArgs);
};

#endif