#ifndef TLEDH
#define TLEDH

class TLEDStatus
{
private:
  enum TIntLEDStatus
  {
    enLEDStatusOn,
    enLEDStatusOff
  };
public:
  TLEDStatus() = delete;

  static TLEDStatus on()
  {
    return TLEDStatus(enLEDStatusOn);
  }
  static TLEDStatus off()
  {
    return TLEDStatus(enLEDStatusOff);
  }
  friend bool operator==(const TLEDStatus&, const TLEDStatus&);
private:
  TLEDStatus(TIntLEDStatus value) : m_value(value) {}

  TIntLEDStatus m_value;
};


class TLEDColor
{
private:
  enum TIntLEDColor
  {
    enLEDColorRed,
    enLEDColorGreen,
    enLEDColorBlue
  };
public:
  TLEDColor() = delete;

  static TLEDColor red()
  {
    return TLEDColor(enLEDColorRed);
  }
  static TLEDColor green()
  {
    return TLEDColor(enLEDColorGreen);
  }
  static TLEDColor blue()
  {
    return TLEDColor(enLEDColorBlue);
  }
  friend bool operator==(const TLEDColor&, const TLEDColor&);
private:
  TLEDColor(TIntLEDColor value) : m_value(value) {}

  TIntLEDColor m_value;
};


typedef unsigned int TFrequency;
const TFrequency c_FreqValueMin = 0;
const TFrequency c_FreqValueMax = 5;


class TLED
{
public:
  TLED();

  const TLEDStatus& getStatus() const;
  void setStatus(const TLEDStatus& newValue);

  const TLEDColor& getColor() const;
  void setColor(const TLEDColor& newValue);

  TFrequency getFrequency() const;
  void setFrequency(TFrequency newValue);

private:
  TLEDStatus m_status;
  TLEDColor m_color;
  TFrequency m_freq;
};

#endif