#include <sstream>
#include <string>
#include <stdexcept>
#include "tLEDHelper.h"

namespace TLEDHelper
{
  TLEDStatus statusFromString(const std::string& value)
  {
    if(value == "on")
      return TLEDStatus::on();
    else if(value == "off")
      return TLEDStatus::off();
    
    throw std::runtime_error("Unknown LED status: " + value);
  }
  std::string toString(const TLEDStatus& value)
  {
    if(value == TLEDStatus::on())
      return "on";
    else if(value == TLEDStatus::off())
      return "off";

    throw std::runtime_error("Unknown LED status");
  }

  TLEDColor colorFromString(const std::string& value)
  {
    if(value == "red")
      return TLEDColor::red();
    else if(value == "green")
      return TLEDColor::green();
    else if(value == "blue")
      return TLEDColor::blue();

    throw std::runtime_error("Unknown LED color: " + value);
  }

  std::string toString(const TLEDColor& value)
  {
    if(value == TLEDColor::red())
      return "red";
    else if(value == TLEDColor::green())
      return "green";
    else if(value == TLEDColor::blue())
      return "blue";

    throw std::runtime_error("Unknown LED color");
  }

  TFrequency freqFromString(const std::string& value)
  {
    TFrequency freq = c_FreqValueMin;
    std::istringstream inStream(value);
    inStream >> freq;
    return freq;
  }

  std::string toString(TFrequency value)
  {
    std::ostringstream outStream;
    outStream << value;
    return outStream.str();
  }
}