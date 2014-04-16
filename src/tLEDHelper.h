#ifndef tLEDHelperH
#define tLEDHelperH
#include "tLED.h"

namespace TLEDHelper
{
  TLEDStatus statusFromString(const std::string& value);
  std::string toString(const TLEDStatus& value);

  TLEDColor colorFromString(const std::string& value);
  std::string toString(const TLEDColor& value);

  TFrequency freqFromString(const std::string& value);
  std::string toString(TFrequency value);
}

#endif