#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch.hpp>

#include "tolower1.h"
#include "tolower2.h"
#include "tolower3.h"
#include <vector>
#include <random>

TEST_CASE("lowercase") {

	std::string s = "AbCdE";
	REQUIRE( tolower2(s) == "abcde" );

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
			tolower1( it );
    };

	auto l2 = l;
    BENCHMARK("tolower - for loop with if") {
        
		for ( auto &it : l2 )
			tolower2( it );
    };

	auto l3 = l;
    BENCHMARK("tolower - absl table") {
        
		for ( auto &it : l3 )
			tolower3( it );
    };

	REQUIRE( l1 == l2 );
	REQUIRE( l1 == l3 );
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

	auto target = l[distrib(gen)];
	int count = 0;
    BENCHMARK("strcasecmp") {
		for ( auto &it : l )
		{
			if (strcasecmp( it.c_str(), target.c_str() ) == 0 )
				++count;
		}
	};
}
