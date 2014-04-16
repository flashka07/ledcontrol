#include <stdexcept>
#include <iostream>
#include "tLED.h"
#include "tLEDHelper.h"

TLED::TLED()
: m_status(TLEDStatus::off()),
  m_color(TLEDColor::red()),
  m_freq(c_FreqValueMin)
{
}

const TLEDStatus& TLED::getStatus() const
{
  return m_status;
}

void TLED::setStatus(const TLEDStatus& newValue)
{
  std::cout << "LED status change from " << TLEDHelper::toString(m_status)
    << " to " << TLEDHelper::toString(newValue) << '\n';
  m_status = newValue;
}

const TLEDColor& TLED::getColor() const
{
  return m_color;
}

void TLED::setColor(const TLEDColor& newValue)
{
  std::cout << "LED color change from " << TLEDHelper::toString(m_color)
    << " to " << TLEDHelper::toString(newValue) << '\n';
  m_color = newValue;
}

TFrequency TLED::getFrequency() const
{
  return m_freq;
}

void TLED::setFrequency(TFrequency newValue)
{
  if(newValue < c_FreqValueMin || newValue > c_FreqValueMax)
    throw std::runtime_error("Wrong value for LED frequency");
  std::cout << "LED frequency change from " << TLEDHelper::toString(m_freq)
    << " to " << TLEDHelper::toString(newValue) << '\n';
  m_freq = newValue;
}

bool operator==(const TLEDStatus& lhs, const TLEDStatus& rhs)
{
  return lhs.m_value == rhs.m_value;
}

bool operator==(const TLEDColor& lhs, const TLEDColor& rhs)
{
  return lhs.m_value == rhs.m_value;
}