#ifndef H_TOLOWER1
#define H_TOLOWER1

#include <string>
#include <algorithm>
#include <cctype>

inline void mklower( char &c )
{
	c = std::tolower( c );
}

inline std::string &tolower1( std::string &s )
{
	for_each( s.begin(), s.end(), mklower );
	return s;
}

#endif
