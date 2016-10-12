#include "alphabetafilter.h"

#include <cassert>
#include <stdexcept>

AlphaBetaFilter::AlphaBetaFilter(
  const double alpha,
  const double beta,
  const double dt)
  : m_alpha(alpha),
    m_beta(beta),
    m_dt(dt),
    m_hidden(0.0),
    m_output(0.0)
{
  if (m_dt <= 0.0)
  {
    throw std::invalid_argument("dt must be bigger than zero");
  }
}


double AlphaBetaFilter::Estimate(const double input) noexcept
{
  double new_output = m_output + ( m_hidden * m_dt );
  double new_hidden = m_hidden;

  const double difference = input - new_output;

  new_output += m_alpha * difference;
  new_hidden += m_beta  * difference / m_dt;

  m_output = new_output;
  m_hidden = new_hidden;

  return m_output;
}
