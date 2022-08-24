#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch.hpp>

#include "using_for_each.h"
#include "using_loop_if.h"
#include "using_absl_table.h"
#include "using_8.h"
#include <vector>
#include <random>


TEST_CASE("lowercase") {

	std::string ss = "AbCdEXghtiKjHGTosQ";
	REQUIRE( tolower_8(ss) == "abcdexghtikjhgtosq" );

	std::string s = "AbCdE";
	REQUIRE( tolower_loop_if(s) == "abcde" );

	std::random_device rd;
	std::mt19937	gen(rd());
	std::uniform_int_distribution<> distrib('A', 'z');
	auto randomWord = [&]()
	{
		std::string s;
		s.reserve( 64 );
		for ( auto i = 0; i < 64; ++i )
			s.push_back( distrib(gen) );
		return s;
	};

	std::vector<std::string> l;
	const int kCount = 10000;
	l.reserve( kCount );
	for ( auto i = 0; i < kCount; ++i )
	{
		l.push_back( randomWord() );
	}

	auto l1 = l;
    BENCHMARK("tolower - for_each") {
        
		for ( auto &it : l1 )
			tolower_for_each( it );
    };

	auto l2 = l;
    BENCHMARK("tolower - for loop with if") {
        
		for ( auto &it : l2 )
			tolower_loop_if( it );
    };

	auto l3 = l;
    BENCHMARK("tolower - absl table") {
        
		for ( auto &it : l3 )
			tolower_absl_table( it );
    };

	auto l4 = l;
    BENCHMARK("tolower - vec8") {
        
		for ( auto &it : l4 )
			tolower_8( it );
    };

	REQUIRE( l1 == l2 );
	REQUIRE( l1 == l3 );
	REQUIRE( l1.size() == l4.size() );
	for ( size_t i = 0; i < l1.size(); ++i )
	{
		if ( l1[i] != l4[i] )
			REQUIRE( l1[i] == l4[i] );
	}
}

TEST_CASE("strcasecmp") {

	std::random_device rd;
	std::mt19937	gen(rd());
	std::uniform_int_distribution<> distrib('A', 'z');
	auto randomWord = [&]()
	{
		std::string s;
		s.reserve( 64 );
		for ( auto i = 0; i < 64; ++i )
			s.push_back( distrib(gen) );
		return s;
	};

	std::vector<std::string> l;
	const int kCount = 10000;
	l.reserve( kCount );
	for ( auto i = 0; i < kCount; ++i )
	{
		l.push_back( randomWord() );
	}

	auto l1 = l;
    BENCHMARK("strcasecmp") {
		std::sort(l1.begin(), l1.end(),
		[]( const auto &lhs, const auto &rhs )
		{
			return strcasecmp( lhs.c_str(), rhs.c_str() ) < 0;
		});
	};

	auto l2 = l;
    BENCHMARK("StrCaseCmp - table") {
		std::sort(l2.begin(), l2.end(),
		[]( const auto &lhs, const auto &rhs )
		{
			return StrCaseCmp_absl_table( lhs, rhs ) < 0;
		});
	};

	auto l3 = l;
    BENCHMARK("StrCaseCmp - if") {
		std::sort(l3.begin(), l3.end(),
		[]( const auto &lhs, const auto &rhs )
		{
			return StrCaseCmpIf( lhs, rhs ) < 0;
		});
	};

	REQUIRE(strcasecmp("AbCd", "aBcD") == 0);
	REQUIRE(StrCaseCmp_absl_table("AbCd", "aBcD") == 0);

	REQUIRE(strcasecmp("AbCdE", "aBcD") == 101);
	REQUIRE(StrCaseCmp_absl_table("AbCdE", "aBcD") == 101);

	REQUIRE(strcasecmp("AbCd", "aBcDE") == -101);
	REQUIRE(StrCaseCmp_absl_table("AbCd", "aBcDE") == -101);

	REQUIRE(strcasecmp("AbCdE", "aBcDf") == -1);
	REQUIRE(StrCaseCmp_absl_table("AbCdE", "aBcDf") == -1);
}
