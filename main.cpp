#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch.hpp>

#include "tolower_for_each.h"
#include "tolower_loop_if.h"
#include "tolower_absl_table.h"
#include "tolower_8.h"
#include <vector>
#include <random>

inline int StrCaseCmp(std::string_view lhs, std::string_view rhs)
{
  auto ulhs = reinterpret_cast<const unsigned char*>(lhs.data());
  auto urhs = reinterpret_cast<const unsigned char*>(rhs.data());
	auto len = std::min(lhs.size(), rhs.size());
	size_t i = 0;
  for (; i < len; i++) {
    const int diff =
        int{static_cast<unsigned char>(absl::ascii_tolower(ulhs[i]))} -
        int{static_cast<unsigned char>(absl::ascii_tolower(urhs[i]))};
    if (diff != 0) return diff;
  }
  if (i > lhs.size())
  {
	if (i > rhs.size())
		return 0;
	return int{static_cast<unsigned char>(absl::ascii_tolower(urhs[i]))};
  }
  if (i > rhs.size())
  {
	return -int{static_cast<unsigned char>(absl::ascii_tolower(ulhs[i]))};
  }
  return int{static_cast<unsigned char>(absl::ascii_tolower(ulhs[i]))} -
        int{static_cast<unsigned char>(absl::ascii_tolower(urhs[i]))};
}

inline int StrCaseCmpIf(std::string_view lhs, std::string_view rhs)
{
  auto ulhs = reinterpret_cast<const unsigned char*>(lhs.data());
  auto urhs = reinterpret_cast<const unsigned char*>(rhs.data());
	auto len = std::min(lhs.size(), rhs.size());
	size_t i = 0;

	auto TOLOWER = [](unsigned  char c ) -> unsigned char
	{
		return ( c >= 'A' and c <= 'Z' ) ? c + ' ' : c;
	};
  for (; i < len; i++) {
    const int diff =
        TOLOWER(ulhs[i]) -
        TOLOWER(urhs[i]);
    if (diff != 0) return diff;
  }
  if (i > lhs.size())
  {
	if (i > rhs.size())
		return 0;
	return TOLOWER(urhs[i]);
  }
  if (i > rhs.size())
  {
	return -TOLOWER(ulhs[i]);
  }
  return TOLOWER(ulhs[i]) -
        TOLOWER(urhs[i]);
}

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
			return StrCaseCmp( lhs, rhs ) < 0;
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
	REQUIRE(StrCaseCmp("AbCd", "aBcD") == 0);

	REQUIRE(strcasecmp("AbCdE", "aBcD") == 101);
	REQUIRE(StrCaseCmp("AbCdE", "aBcD") == 101);

	REQUIRE(strcasecmp("AbCd", "aBcDE") == -101);
	REQUIRE(StrCaseCmp("AbCd", "aBcDE") == -101);

	REQUIRE(strcasecmp("AbCdE", "aBcDf") == -1);
	REQUIRE(StrCaseCmp("AbCdE", "aBcDf") == -1);
}
