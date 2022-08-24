#ifndef H_TOLOWER_LOOP_IF
#define H_TOLOWER_LOOP_IF

#include <string>

inline std::string &tolower_loop_if( std::string &s )
{
	auto ptr = s.data();
	auto len = s.length();
	for ( size_t i = 0; i < len; ++i )
	{
		if ( s[i] >= 'A' and s[i] <= 'Z' )
			s[i] = s[i] + ' ';
	}
	return s;
}

#endif
