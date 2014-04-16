#include "tLEDCommandResult.h"

std::string TLEDCommandResult::s_strSuccess("OK");
std::string TLEDCommandResult::s_strFail("FAILED");
std::string TLEDCommandResult::s_strUndefined("UNDEFINED_ERROR_CODE");

TLEDCommandResult::TLEDCommandResult()
: m_result(enTLEDCmdSuccess)
{}

TLEDCommandResult::TLEDCommandResult(TLEDIntCommandResult result)
: m_result(result)
{}

TLEDCommandResult::TLEDCommandResult(
  TLEDIntCommandResult result,
  const std::string& optionalResult)
  : m_result(result),
    m_strOptionalResult(optionalResult)
{}

const std::string& TLEDCommandResult::toStringShort() const
{
  switch(m_result)
  {
  case enTLEDCmdSuccess:
    return s_strSuccess;
  case enTLEDCmdFail:
    return s_strFail;
  }
  return s_strUndefined;
}

std::string TLEDCommandResult::toString() const
{
  if(m_strOptionalResult.size() == 0)
    return toStringShort();
  return toStringShort() + " " + m_strOptionalResult;
}