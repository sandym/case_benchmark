#ifndef H_TOLOWER_FOR_EACH
#define H_TOLOWER_FOR_EACH

#include <string>
#include <algorithm>
#include <cctype>

inline void mklower( char &c )
{
	c = std::tolower( c );
}

inline std::string &tolower_for_each( std::string &s )
{
	for_each( s.begin(), s.end(), mklower );
	return s;
}

#endif
