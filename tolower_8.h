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
		ptr[i] |= g_mask_table[ptr[i]];;
	}
	return s;
}

#endif
