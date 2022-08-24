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

#endif
