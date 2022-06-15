
#include "../Angle.h"
#include <assert.h>


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


	// Operator }
	assert( eq(
		-math::Angle::Deg( +30 ),
		+math::Angle::Deg( -30 )
	) );

	// Compare
	assert( angle_30 == angle_30 );
	assert( angle_30 != angle_45 );
	assert( angle_30 < angle_45 );
	assert( angle_30 > angle_0 );
}
