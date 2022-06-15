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
	static constexpr Angle Zero    () noexcept { return Rad( 0 ) ; }
	static constexpr Angle Vertical() noexcept { return Rad( M_PI / 2 ) ; }
	static constexpr Angle Flat    () noexcept { return Rad( M_PI ) ; }
	static constexpr Angle Full    () noexcept { return Rad( 2 * M_PI ) ; }

public:
	// Only the following 5 parameter sets are valid.
	// Normalize<   0, 360>() ;
	// Normalize<-180, 180>() ;
	// Normalize<   0, 180>() ;
	// Normalize<   0,  90>() ;
	// Normalize< -90,  90>() ;
	template<int stt_deg, int end_deg>
	Angle Normalize() const noexcept = delete;

public:
	constexpr Angle operator +() const { return *this ; }
	constexpr Angle operator -() const { return Angle{ -m_rad } ; }

public:
	constexpr bool operator == ( const Angle& a ) const noexcept { return m_rad == a.m_rad ; }
	constexpr bool operator != ( const Angle& a ) const noexcept { return m_rad != a.m_rad ; }
	constexpr bool operator <  ( const Angle& a ) const noexcept { return m_rad  < a.m_rad ; }
	constexpr bool operator >  ( const Angle& a ) const noexcept { return m_rad  > a.m_rad ; }
	constexpr bool operator <= ( const Angle& a ) const noexcept { return m_rad <= a.m_rad ; }
	constexpr bool operator >= ( const Angle& a ) const noexcept { return m_rad >= a.m_rad ; }

public:
	Angle& operator += ( const Angle& a ) noexcept { m_rad += a.Rad() ; return *this ; }
	Angle& operator -= ( const Angle& a ) noexcept { m_rad -= a.Rad() ; return *this ; }
	Angle& operator *= ( const double val ) noexcept { m_rad *= val ; return *this ; }
	Angle& operator /= ( const double val ) noexcept { m_rad /= val ; return *this ; }

private:
	explicit constexpr Angle( const double rad ) noexcept :m_rad{ rad } {}

private:
	static constexpr double rate_d_to_r = M_PI / 180;
	static constexpr double rate_r_to_d = 180 / M_PI ;

private:
	double m_rad{};
};

///////////////////////////////////////////////////////////////////////////////////////////////////
constexpr inline Angle operator + ( const Angle& a1, const Angle& a2 ) noexcept { return Angle::Rad( a1.Rad() + a2.Rad() ) ; }
constexpr inline Angle operator - ( const Angle& a1, const Angle& a2 ) noexcept { return Angle::Rad( a1.Rad() - a2.Rad() ) ; }
constexpr inline Angle operator * ( const double val, const Angle& a ) noexcept { return Angle::Rad( val * a.Rad() ) ; }
constexpr inline Angle operator * ( const Angle& a, const double val ) noexcept { return Angle::Rad( a.Rad() * val ) ; }
constexpr inline Angle operator / ( const Angle& a, const double val ) noexcept { return Angle::Rad( a.Rad() / val ) ; }

///////////////////////////////////////////////////////////////////////////////////////////////////
inline double sin( const Angle& angle ) noexcept { return std::sin( angle.Rad() ) ; }
inline double cos( const Angle& angle ) noexcept { return std::cos( angle.Rad() ) ; }
inline double tan( const Angle& angle ) noexcept { return std::tan( angle.Rad() ) ; }

///////////////////////////////////////////////////////////////////////////////////////////////////
template<>
Angle Angle::Normalize<0, 360>() const noexcept
{
	constexpr auto full_rad = Full().Rad() ;
	const auto mod = std::fmod( m_rad, full_rad ) ;
	const auto result = ( mod >= 0 ) ? mod : mod + full_rad;
	return Angle::Rad( result ) ;
}

template<>
Angle Angle::Normalize<-180, 180>() const noexcept
{
	auto result = Normalize<0, 360>() ;
	if ( result >= Flat() ) { result -= Full() ; }
	return result ;
}

template<>
Angle Angle::Normalize<0, 180>() const noexcept
{
	auto result = Normalize<-180, 180>() ;
	if ( result < Zero() ) { result *= -1 ; }
	return result ;
}

template<>
Angle Angle::Normalize<-90, 90>() const noexcept
{
	auto result = Normalize<-180, 180>() ;
	if ( result >= Vertical() ) {
		result = +Flat() - result ;
	} else if ( result <= -Vertical() ) {
		result = -Flat() - result ;
	}
	return Angle{ result } ;
}

template<>
Angle Angle::Normalize<0, 90>() const noexcept
{
	auto result = Normalize<-90, 90>() ;
	if ( result < Zero() ) { result *= -1 ; }
	return result ;
}


} // namespace math 
