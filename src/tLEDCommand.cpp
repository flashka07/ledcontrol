#include <string>
#include "tLEDCommand.h"
#include "tLED.h"
#include "tLEDHelper.h"


TLEDCommandResult TLEDCmdSetStatus::execute(TLED& led, const std::string& strArgs)
{
  led.setStatus(TLEDHelper::statusFromString(strArgs));
  return TLEDCommandResult(TLEDCommandResult::enTLEDCmdSuccess);
}

TLEDCommandResult TLEDCmdGetStatus::execute(TLED& led, const std::string& strArgs)
{
  return TLEDCommandResult(
    TLEDCommandResult::enTLEDCmdSuccess,
    TLEDHelper::toString(led.getStatus()));
}

TLEDCommandResult TLEDCmdSetColor::execute(TLED& led, const std::string& strArgs)
{
  led.setColor(TLEDHelper::colorFromString(strArgs));
  return TLEDCommandResult(TLEDCommandResult::enTLEDCmdSuccess);
}

TLEDCommandResult TLEDCmdGetColor::execute(TLED& led, const std::string& strArgs)
{
  return TLEDCommandResult(
    TLEDCommandResult::enTLEDCmdSuccess,
    TLEDHelper::toString(led.getColor()));
}

TLEDCommandResult TLEDCmdSetFrequency::execute(TLED& led, const std::string& strArgs)
{
  led.setFrequency(TLEDHelper::freqFromString(strArgs));
  return TLEDCommandResult(TLEDCommandResult::enTLEDCmdSuccess);
}

TLEDCommandResult TLEDCmdGetFrequency::execute(TLED& led, const std::string& strArgs)
{
  return TLEDCommandResult(
    TLEDCommandResult::enTLEDCmdSuccess,
    TLEDHelper::toString(led.getFrequency()));
}