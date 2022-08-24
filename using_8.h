#ifndef H_TOLOWER_8
#define H_TOLOWER_8

#include <string>

namespace tolower_8_details {

constexpr unsigned char g_mask_table[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0
};

static_assert(sizeof(g_mask_table) == 256);
static_assert(g_mask_table['A'-1] == 0);
static_assert(g_mask_table['A'] == 0x20);
static_assert(g_mask_table['Z'] == 0x20);
static_assert(g_mask_table['Z'+1] == 0);

}

inline std::string &tolower_8( std::string &s )
{
	using namespace tolower_8_details;

	auto ptr = reinterpret_cast<unsigned char *>( s.data() );
	auto len = s.length();
	size_t i = 0;
	for( ; i < len/8 * 8 ; i += 8 )
	{
		uint64_t m = 0;
		reinterpret_cast<unsigned char *>(&m)[0] |= g_mask_table[ptr[i+0]];
		reinterpret_cast<unsigned char *>(&m)[1] |= g_mask_table[ptr[i+1]];
		reinterpret_cast<unsigned char *>(&m)[2] |= g_mask_table[ptr[i+2]];
		reinterpret_cast<unsigned char *>(&m)[3] |= g_mask_table[ptr[i+3]];
		reinterpret_cast<unsigned char *>(&m)[4] |= g_mask_table[ptr[i+4]];
		reinterpret_cast<unsigned char *>(&m)[5] |= g_mask_table[ptr[i+5]];
		reinterpret_cast<unsigned char *>(&m)[6] |= g_mask_table[ptr[i+6]];
		reinterpret_cast<unsigned char *>(&m)[7] |= g_mask_table[ptr[i+7]];
		*reinterpret_cast<uint64_t*>(ptr + i) |= m;
	}
	for (; i < len; ++i )
	{
		ptr[i] |= g_mask_table[ptr[i]];
	}
	return s;
}

inline int StrCaseCmp_8(std::string_view lhs, std::string_view rhs)
{
	using namespace tolower_8_details;

	auto ulhs = reinterpret_cast<const unsigned char*>(lhs.data());
	auto urhs = reinterpret_cast<const unsigned char*>(rhs.data());
	auto len = std::min(lhs.size(), rhs.size());
	size_t i = 0;
	for( ; i < len/8 * 8 ; i += 8 )
	{
		uint64_t mlhs = 0;
		reinterpret_cast<unsigned char *>(&mlhs)[0] |= g_mask_table[ulhs[i+0]];
		reinterpret_cast<unsigned char *>(&mlhs)[1] |= g_mask_table[ulhs[i+1]];
		reinterpret_cast<unsigned char *>(&mlhs)[2] |= g_mask_table[ulhs[i+2]];
		reinterpret_cast<unsigned char *>(&mlhs)[3] |= g_mask_table[ulhs[i+3]];
		reinterpret_cast<unsigned char *>(&mlhs)[4] |= g_mask_table[ulhs[i+4]];
		reinterpret_cast<unsigned char *>(&mlhs)[5] |= g_mask_table[ulhs[i+5]];
		reinterpret_cast<unsigned char *>(&mlhs)[6] |= g_mask_table[ulhs[i+6]];
		reinterpret_cast<unsigned char *>(&mlhs)[7] |= g_mask_table[ulhs[i+7]];
		uint64_t mrhs = 0;
		reinterpret_cast<unsigned char *>(&mrhs)[0] |= g_mask_table[urhs[i+0]];
		reinterpret_cast<unsigned char *>(&mrhs)[1] |= g_mask_table[urhs[i+1]];
		reinterpret_cast<unsigned char *>(&mrhs)[2] |= g_mask_table[urhs[i+2]];
		reinterpret_cast<unsigned char *>(&mrhs)[3] |= g_mask_table[urhs[i+3]];
		reinterpret_cast<unsigned char *>(&mrhs)[4] |= g_mask_table[urhs[i+4]];
		reinterpret_cast<unsigned char *>(&mrhs)[5] |= g_mask_table[urhs[i+5]];
		reinterpret_cast<unsigned char *>(&mrhs)[6] |= g_mask_table[urhs[i+6]];
		reinterpret_cast<unsigned char *>(&mrhs)[7] |= g_mask_table[urhs[i+7]];

    	if ( (*reinterpret_cast<const uint64_t*>(ulhs + i)|mlhs) !=
				(*reinterpret_cast<const uint64_t*>(urhs + i)|mrhs) )
		{

		}
	}
	for (; i < len; ++i )
	{
    // const int diff =
    //     int{static_cast<unsigned char>(absl::ascii_tolower(ulhs[i]))} -
    //     int{static_cast<unsigned char>(absl::ascii_tolower(urhs[i]))};
    // if (diff != 0) return diff;
	}
	return 0;
}

#endif
