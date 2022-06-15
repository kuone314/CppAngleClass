#include "pch.h"
#include "CppUnitTest.h"

#include "../../Angle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


//// double equality comparison:
//static void AreEqual(double expected, double actual, double tolerance, const wchar_t* message = NULL, const __LineInfo* pLineInfo = NULL)
//{
//	double diff = expected - actual;
//	FailOnCondition(fabs(diff) <= fabs(tolerance), EQUALS_MESSAGE(expected, actual, message), pLineInfo);
//}

namespace UnitTest {

///////////////////////////////////////////////////////////////////////////////////////////////////
constexpr auto angle_0 = math::Angle{};
constexpr auto angle_30 = math::Angle::Deg( 30 );
constexpr auto angle_45 = math::Angle::Rad( M_PI / 4 );
constexpr auto angle_15 = math::Angle::Deg( 15 );

///////////////////////////////////////////////////////////////////////////////////////////////////
constexpr double tolerance = 0.001 ;
void CheckEqual(
	const math::Angle& v_1,
	const math::Angle& v_2 )
{
	Assert::AreEqual( v_1.Rad(), v_2.Rad(), tolerance );
}

///////////////////////////////////////////////////////////////////////////////////////////////////
template<int stt_deg, int end_deg>
void CheckNormalized( const math::Angle& org, const math::Angle& noemalized ) ;


template<> void CheckNormalized<0, 360>( const math::Angle& org, const math::Angle& noemalized ) {
	Assert::AreEqual( sin( org ), sin( noemalized ), tolerance ) ;
	Assert::AreEqual( cos( org ), cos( noemalized ), tolerance ) ;
}
template<> void CheckNormalized<-180, 180>( const math::Angle& org, const math::Angle& noemalized ) {
	Assert::AreEqual( sin( org ), sin( noemalized ), tolerance ) ;
	Assert::AreEqual( cos( org ), cos( noemalized ), tolerance ) ;
}
template<> void CheckNormalized<0, 180>( const math::Angle& org, const math::Angle& noemalized ) {
	Assert::AreEqual( cos( org ), cos( noemalized ), tolerance ) ;
}
template<> void CheckNormalized<-90, 90>( const math::Angle& org, const math::Angle& noemalized ) {
	Assert::AreEqual( sin( org ), sin( noemalized ), tolerance ) ;
}
template<> void CheckNormalized<0, 90>( const math::Angle& org, const math::Angle& noemalized ) {
	Assert::AreEqual( abs( cos( org ) ), abs( cos( noemalized ) ), tolerance ) ;
}

template<int stt_deg, int end_deg>
void TestNormalize( const math::Angle& angle ) {
	const auto normalized = angle.Normalize<stt_deg, end_deg>();
	Assert::IsTrue( stt_deg <= normalized.Deg() );
	Assert::IsTrue( normalized.Deg() <= end_deg );
	CheckNormalized<stt_deg, end_deg>( angle, normalized );
}
void TestNormalize( const double test_val ) {
	const auto org = math::Angle::Deg( test_val );
	TestNormalize<-180, 180>( org ) ;
	TestNormalize<0, 180>( org ) ;
	TestNormalize<-90, 90>( org ) ;
	TestNormalize<0, 90>( org ) ;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
TEST_CLASS( UnitTest ) {
public:

	TEST_METHOD( Noremlize ) {
		for ( int tst_val = -500; tst_val <= 500; tst_val++ ) {
			TestNormalize( tst_val );
		}
	}

	TEST_METHOD( Noremlize_2 ) {
		Assert::AreEqual( math::Angle::Deg( 365 ).Normalize<0, 360>().Deg(), 5, tolerance );
		Assert::AreEqual( math::Angle::Deg( -30 ).Normalize<0, 360>().Deg(), 330, tolerance );

		Assert::AreEqual( math::Angle::Deg( 365 ).Normalize<-180, 180>().Deg(), 5, tolerance );
		Assert::AreEqual( math::Angle::Deg( 330 ).Normalize<-180, 180>().Deg(), -30, tolerance );

		Assert::AreEqual( math::Angle::Deg( 190 ).Normalize<0, 180>().Deg(), 170, tolerance );
		Assert::AreEqual( math::Angle::Deg( -50 ).Normalize<0, 180>().Deg(), 50, tolerance );

		Assert::AreEqual( math::Angle::Deg( 120 ).Normalize<0, 90>().Deg(), 60, tolerance );
		Assert::AreEqual( math::Angle::Deg( 240 ).Normalize<0, 90>().Deg(), 60, tolerance );

		Assert::AreEqual( math::Angle::Deg( 120 ).Normalize<-90, 90>().Deg(), 60, tolerance );
		Assert::AreEqual( math::Angle::Deg( 300 ).Normalize<-90, 90>().Deg(), -60, tolerance );
	}

	TEST_METHOD( GetValue )
	{
		Assert::AreEqual( angle_0.Deg(), 0, tolerance ) ;
		Assert::AreEqual( angle_0.Rad(), 0, tolerance ) ;

		Assert::AreEqual( angle_30.Deg(), 30, tolerance ) ;
		Assert::AreEqual( angle_30.Rad(), M_PI / 6, tolerance ) ;

		Assert::AreEqual( angle_45.Deg(), 45, tolerance ) ;
		Assert::AreEqual( angle_45.Rad(), M_PI / 4, tolerance ) ;
	}

	TEST_METHOD( Operators )
	{
		Assert::IsTrue( angle_30 == angle_30 );
		Assert::IsTrue( angle_30 != angle_45 );
		Assert::IsTrue( angle_30 < angle_45 );
		Assert::IsTrue( angle_30 > angle_0 );

		CheckEqual( -angle_30, math::Angle::Deg( -30 ) ) ;

		CheckEqual( angle_15 + angle_30, angle_45 ) ;
		CheckEqual( angle_15 - angle_30, -angle_15 ) ;
		CheckEqual( angle_15 * 2, angle_30 ) ;
		CheckEqual( 2 * angle_15, angle_30 ) ;
		CheckEqual( angle_30 / 2, angle_15 ) ;
	}

	TEST_METHOD( SelfDestructionOperators )
	{
		math::Angle angle ;

		angle += angle_30;
		CheckEqual( angle, angle_30 ) ;
		
		angle -= angle_45;
		CheckEqual( angle, -angle_15 ) ;
		
		angle *= -3;
		CheckEqual( angle, angle_45 ) ;

		angle /= 45;
		CheckEqual( angle, math::Angle::Deg( 1 ) ) ;
	}

	TEST_METHOD( CharacteristicAngles )
	{
		Assert::AreEqual( math::Angle::Zero().Deg(), 0, tolerance ) ;
		Assert::AreEqual( math::Angle::Vertical().Deg(), 90, tolerance ) ;
		Assert::AreEqual( math::Angle::Flat().Deg(), 180, tolerance ) ;
		Assert::AreEqual( math::Angle::Full().Deg(), 360, tolerance ) ;
	}	

	TEST_METHOD( misc )
	{
		const auto a = math::Angle::Deg( -30 );
		const auto b = math::Angle::Deg( +60 );
		const auto c = math::Angle::Deg( 330 );

		Assert::IsTrue( a < b );
		Assert::IsFalse( a == c );

		Assert::AreEqual( sin( angle_30 ), 0.5, tolerance );
	}	
};
}
