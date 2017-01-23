#pragma once

#include <utility>

constexpr int seed =
static_cast<int>(__TIME__[7]) * 1 +
static_cast<int>(__TIME__[6]) * 10 +
static_cast<int>(__TIME__[4]) * 60 +
static_cast<int>(__TIME__[3]) * 600 +
static_cast<int>(__TIME__[1]) * 3600 +
static_cast<int>(__TIME__[0]) * 36000;

template < int N >
struct RandomGenerator
{
private:
	static constexpr unsigned a = 16807; // 7^5
	static constexpr unsigned m = 2147483647; // 2^31 - 1

	static constexpr unsigned s = RandomGenerator< N - 1 >::value;
	static constexpr unsigned lo = a * (s & 0xFFFF); // Multiply lower 16 bits by 16807
	static constexpr unsigned hi = a * (s >> 16); // Multiply higher 16 bits by 16807
	static constexpr unsigned lo2 = lo + ((hi & 0x7FFF) << 16); // Combine lower 15 bits of hi with lo's upper bits
	static constexpr unsigned hi2 = hi >> 15; // Discard lower 15 bits of hi
	static constexpr unsigned lo3 = lo2 + hi;

public:
	static constexpr unsigned max = m;
	static constexpr unsigned value = lo3 > m ? lo3 - m : lo3;
};

template <>
struct RandomGenerator<0>
{
	static constexpr unsigned value = seed;
};

template <int N, int M>
struct RandomInt
{
	static constexpr unsigned value = RandomGenerator<N + 1>::value % M;
};

template <int N>
struct RandomChar
{
	static constexpr char value = char(RandomInt<N, 0xFF>::value);
};

template <size_t N, int K>
struct XorString
{
private:
	const char _key;
	char _encrypted[N + 1];

	constexpr char encryptc(char c) const
	{
		return c ^ _key;
	}

	char decryptc(char c) const
	{
		return c ^ _key;
	}

public:
	template < size_t... Is >
	constexpr __forceinline XorString(const char* str, std::index_sequence< Is... >) : _key(RandomChar< K >::value), _encrypted{ encryptc(str[Is])... }
	{
	}

	__forceinline char* decrypt(void)
	{
		for (size_t i = 0; i < N; ++i) {
			_encrypted[i] = decryptc(_encrypted[i]);
		}
		_encrypted[N] = '\0';
		return &_encrypted[0];
	}
};

#define XorStr(s) ( XorString <sizeof(s) - 1, __COUNTER__>(s, std::make_index_sequence<sizeof( s ) - 1>() ).decrypt() ) // 496 char max, 384 before name truncation