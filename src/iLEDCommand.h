#ifndef iLEDCommandH
#define iLEDCommandH
#include <string>
#include "tLEDCommandResult.h"

class TLED;

class ILEDCommand
{
public:
  virtual TLEDCommandResult execute(TLED& led, const std::string& strArgs) = 0;
};

#endif