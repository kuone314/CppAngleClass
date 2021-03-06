
#include "../Angle.h"
#include <assert.h>

#include <memory>


bool eq( const double v_1, const double v_2 ) { return abs( v_1 - v_2 ) < 0.001; }
bool eq( const math::Angle& v_1, const math::Angle& v_2 ) { return eq( v_1.Rad(), v_2.Rad() ); }

int main()
{
	// Define, Get Value.
	const auto angle_0 = math::Angle{};
	assert( eq( angle_0.Deg(), 0 ) );
	assert( eq( angle_0.Rad(), 0 ) );

	const auto angle_30 = math::Angle::Deg( 30 );
	assert( eq( angle_30.Deg(), 30 ) );
	assert( eq( angle_30.Rad(), M_PI / 6 ) );

	const auto angle_45 = math::Angle::Rad( M_PI / 4 );
	assert( eq( angle_45.Deg(), 45 ) );
	assert( eq( angle_45.Rad(), M_PI / 4 ) );

	const auto angle_ptr = std::make_shared<math::Angle>( math::Angle::Deg( 10 ) );
	assert( eq( angle_ptr->Deg(), 10 ) );

	// Operator �}
	assert( eq(
		-math::Angle::Deg( +30 ),
		+math::Angle::Deg( -30 )
	) );

	// Compare
	assert( angle_30 == angle_30 );
	assert( angle_30 != angle_45 );
	assert( angle_30 < angle_45 );
	assert( angle_30 > angle_0 );

	// Operator +-*/
	const auto angle_15 = math::Angle::Deg( 15 );
	assert( eq( angle_15 + angle_30, angle_45 ) );
	assert( eq( angle_15 - angle_30, -angle_15 ) );
	assert( eq( angle_15 * 2, angle_30 ) );
	assert( eq( 2 * angle_15, angle_30 ) );
	assert( eq( angle_30 / 2, angle_15 ) );

	// Charactaristic Angle
	assert( eq( math::Angle::Zero().Deg(), 0 ) );
	assert( eq( math::Angle::Vertical().Deg(), 90 ) );
	assert( eq( math::Angle::Flat().Deg(), 180 ) );
	assert( eq( math::Angle::Full().Deg(), 360 ) );

	// Normalize
	assert( eq( math::Angle::Deg(  -30 ).Normalize<   0, 360>(), math::Angle::Deg(  330 ) ) );
	assert( eq( math::Angle::Deg(  200 ).Normalize<-180, 180>(), math::Angle::Deg( -160 ) ) );
	assert( eq( math::Angle::Deg(  200 ).Normalize<   0, 180>(), math::Angle::Deg(  160 ) ) );
	assert( eq( math::Angle::Deg( -120 ).Normalize<   0,  90>(), math::Angle::Deg(   60 ) ) );
	assert( eq( math::Angle::Deg( -120 ).Normalize< -90,  90>(), math::Angle::Deg(  -60 ) ) );

	// Trigonometric function
	assert( eq( sin( angle_30 ), 0.5 ) );
	assert( eq( cos( angle_15 ), cos( angle_15.Rad() ) ) );
	assert( eq( tan( angle_45 ), 1 ) );
}
