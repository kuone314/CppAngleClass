#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

namespace math {

class Angle {
public:
	constexpr Angle() noexcept :Angle{ 0 } {}
	static constexpr Angle Rad( const double rad ) noexcept { return Angle{ rad } ; }
	static constexpr Angle Deg( const double deg ) noexcept { return Angle{ deg * rate_d_to_r } ; }

public:
	constexpr double Rad() const noexcept { return m_rad; }
	constexpr double Deg() const noexcept { return m_rad * rate_r_to_d ; }

public:
	constexpr Angle operator +() const { return *this ; }
	constexpr Angle operator -() const { return Angle{ -m_rad } ; }

public:
	constexpr bool operator == ( const Angle& a ) const { return m_rad == a.m_rad ; }
	constexpr bool operator != ( const Angle& a ) const { return m_rad != a.m_rad ; }
	constexpr bool operator <  ( const Angle& a ) const { return m_rad  < a.m_rad ; }
	constexpr bool operator >  ( const Angle& a ) const { return m_rad  > a.m_rad ; }
	constexpr bool operator <= ( const Angle& a ) const { return m_rad <= a.m_rad ; }
	constexpr bool operator >= ( const Angle& a ) const { return m_rad >= a.m_rad ; }

private:
	explicit constexpr Angle( const double rad ) noexcept :m_rad{ rad } {}

private:
	static constexpr double rate_d_to_r = M_PI / 180;
	static constexpr double rate_r_to_d = 180 / M_PI ;

private:
	double m_rad{};
};


} // namespace math 
