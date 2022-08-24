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

inline int StrCaseCmp_absl_table(std::string_view lhs, std::string_view rhs)
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

#endif
