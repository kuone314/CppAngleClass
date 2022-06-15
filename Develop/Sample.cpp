
#include "../Angle.h"
#include <assert.h>


bool eq( const double v_1, const double v_2 ) { return abs( v_1 - v_2 ) < 0.001; }

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


}
