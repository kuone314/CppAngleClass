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
	static constexpr Angle Zero() { return Rad( 0 ) ; }
	static constexpr Angle Vertical() { return Rad( M_PI / 2 ) ; }
	static constexpr Angle Flat() { return Rad( M_PI ) ; }
	static constexpr Angle Full() { return Rad( 2 * M_PI ) ; }

public:
	constexpr Angle operator +() const { return *this ; }
	constexpr Angle operator -() const { return Angle{ -m_rad } ; }

public:
	constexpr bool operator == ( const Angle& a ) const { return m_rad == a.m_rad ; }
	constexpr bool operator != ( const Angle& a ) const { return m_rad != a.m_rad ; }
	constexpr bool operator <  ( const Angle& a ) const { return m_rad < a.m_rad ; }
	constexpr bool operator >  ( const Angle& a ) const { return m_rad > a.m_rad ; }
	constexpr bool operator <= ( const Angle& a ) const { return m_rad <= a.m_rad ; }
	constexpr bool operator >= ( const Angle& a ) const { return m_rad >= a.m_rad ; }

public:
	Angle& operator += ( const Angle& a ) { m_rad += a.Rad() ; return *this ; }
	Angle& operator -= ( const Angle& a ) { m_rad -= a.Rad() ; return *this ; }
	Angle& operator *= ( const double val ) { m_rad *= val ; return *this ; }
	Angle& operator /= ( const double val ) { m_rad /= val ; return *this ; }

private:
	explicit constexpr Angle( const double rad ) noexcept :m_rad{ rad } {}

private:
	static constexpr double rate_d_to_r = M_PI / 180;
	static constexpr double rate_r_to_d = 180 / M_PI ;

private:
	double m_rad{};
};

///////////////////////////////////////////////////////////////////////////////////////////////////
constexpr inline Angle operator + ( const Angle& a1, const Angle& a2 ) { return Angle::Rad( a1.Rad() + a2.Rad() ) ; }
constexpr inline Angle operator - ( const Angle& a1, const Angle& a2 ) { return Angle::Rad( a1.Rad() - a2.Rad() ) ; }
constexpr inline Angle operator * ( const double val, const Angle& a ) { return Angle::Rad( val * a.Rad() ) ; }
constexpr inline Angle operator * ( const Angle& a, const double val ) { return Angle::Rad( a.Rad() * val ) ; }
constexpr inline Angle operator / ( const Angle& a, const double val ) { return Angle::Rad( a.Rad() / val ) ; }


} // namespace math 
