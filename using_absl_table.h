#ifndef H_TOLOWER_ABSL_TABLE
#define H_TOLOWER_ABSL_TABLE

#include <string>
#include <absl/strings/ascii.h>

inline std::string &tolower_absl_table( std::string &s )
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
