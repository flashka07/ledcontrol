#ifndef tLEDCommandResultH
#define tLEDCommandResultH
#include <string>

class TLEDCommandResult
{
public:
  enum TLEDIntCommandResult
  {
    enTLEDCmdSuccess = 0,
    enTLEDCmdFail
  };

  TLEDCommandResult();
  TLEDCommandResult(TLEDIntCommandResult result);
  TLEDCommandResult(
    TLEDIntCommandResult result,
    const std::string& optionalResult);

  const std::string& toStringShort() const;
  std::string toString() const;

private:
  static std::string s_strSuccess;
  static std::string s_strFail;
  static std::string s_strUndefined;

  TLEDIntCommandResult m_result;
  std::string m_strOptionalResult;
};

#endif