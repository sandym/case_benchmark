#ifndef H_TOLOWER3
#define H_TOLOWER3

#include <string>
#include <absl/strings/ascii.h>

inline std::string &tolower3( std::string &s )
{
	auto ptr = reinterpret_cast<unsigned char *>( s.data() );
	auto len = s.length();
	for ( size_t i = 0; i < len; ++i )
	{
		ptr[i] = absl::ascii_tolower( ptr[i] );
	}
	return s;
}

#endif
