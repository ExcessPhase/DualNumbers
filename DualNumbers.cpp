#include <iostream>
#include <cmath>


	/// the dual number class
	/// SIZE is the number of independent variables
template<std::size_t SIZE>
struct DualNumbers
{		/// the value or 0th order derivative
	double m_dValue;
		/// the first order derivative wrt the independent variables
	double m_adDer[SIZE];
		/// a constructor to create an independent variable
	DualNumbers(const double _d, const std::size_t _i)
		:m_dValue(_d)
	{	for (std::size_t i = 0; i < SIZE; ++i)
			m_adDer[i] = i == _i ? 1.0 : 0.0;
	}
		/// a constructor to create a value whose derivatives are all zero
	DualNumbers(const double _d)
		:m_dValue(_d)
	{	for (std::size_t i = 0; i < SIZE; ++i)
			m_adDer[i] = 0.0;
	}
	DualNumbers(void) = default;
	DualNumbers(const DualNumbers&) = default;
	DualNumbers(DualNumbers&&) = default;
	DualNumbers&operator=(const DualNumbers&) = default;
	DualNumbers&operator=(DualNumbers&&) = default;
		/// assignment operator with a pure value
	DualNumbers&operator=(const double _d)
	{	m_dValue = _d;
		for (std::size_t i = 0; i < SIZE; ++i)
			m_adDer[i] = 0.0;
		return *this;
	}
		/// the multiplication operator
	DualNumbers operator*(const DualNumbers&_r) const
	{	DualNumbers s;
		s.m_dValue = m_dValue*_r.m_dValue;
		for (std::size_t i = 0; i < SIZE; ++i)
				/// the multiplication rule
			s.m_adDer[i] = m_dValue*_r.m_adDer[i] + _r.m_dValue*m_adDer[i];
		return s;
	}
		/// the negation operator
	DualNumbers operator-(void) const
	{	DualNumbers s;
		s.m_dValue = -m_dValue;
		for (std::size_t i = 0; i < SIZE; ++i)
			s.m_adDer[i] = -m_adDer[i];
		return s;
	}
		/// implementation of exp(x)
	friend DualNumbers exp(const DualNumbers&_r)
	{	DualNumbers s;
		s.m_dValue = std::exp(_r.m_dValue);
		for (std::size_t i = 0; i < SIZE; ++i)
				/// chain rule
			s.m_adDer[i] = s.m_dValue*_r.m_adDer[i];
		return s;
	}
		/// the output streaming operator
	friend std::ostream &operator<<(std::ostream &_rS, const DualNumbers&_r)
	{	_rS << "value=" << _r.m_dValue << "\n";
		for (std::size_t i = 0; i < SIZE; ++i)
			_rS << "der(" << i << ")=" << _r.m_adDer[i] << "\n";
		return _rS;
	}
};


int main()
{
	const DualNumbers<1> s0(1.2, 0);
	std::cout << exp(-s0*s0) << std::endl;
	
}
