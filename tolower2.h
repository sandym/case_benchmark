#ifndef H_TOLOWER2
#define H_TOLOWER2

#include <string>

inline std::string &tolower2( std::string &s )
{
	auto ptr = s.data();
	auto len = s.length();
	for ( size_t i = 0; i < len; ++i )
	{
		if ( ptr[i] >= 'A' and ptr[i] <= 'Z' )
			ptr[i] = ptr[i] + ' ';
	}
	return s;
}

#endif
