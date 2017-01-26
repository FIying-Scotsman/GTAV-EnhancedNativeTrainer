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

/*

#pragma once

//-------------------------------------------------------------//
// "Malware related compile-time hacks with C++11" by LeFF   //
// You can use this code however you like, I just don't really //
// give a shit, but if you feel some respect for me, please //
// don't cut off this comment when copy-pasting... ;-)       //
//-------------------------------------------------------------//


#include <utility>

namespace utils {


	template <int X> struct EnsureCompileTime {
		enum : int {
			Value = X
		};
	};

	//Use Compile-Time as seed
#define compile_seed (	(__TIME__[7] - '0') * 1  + (__TIME__[6] - '0') * 10		+	\
						(__TIME__[4] - '0') * 60   + (__TIME__[3] - '0') * 600	+	\
						(__TIME__[1] - '0') * 3600 + (__TIME__[0] - '0') * 36000	)

	constexpr int LinearCongruentGenerator(int Rounds) {
		return 1013904223 + 1664525 * ((Rounds > 0) ? LinearCongruentGenerator(Rounds - 1) : compile_seed & 0xFFFFFFFF);
	}

#define Random() EnsureCompileTime<LinearCongruentGenerator(10)>::Value //10 Rounds
#define RandomNumber(Min, Max) (Min + (Random() % (Max - Min + 1)))

	template <int... Pack> struct IndexList {};

	template <typename IndexList, int Right> struct Append;
	template <int... Left, int Right> struct Append<IndexList<Left...>, Right> {
		typedef IndexList<Left..., Right> Result;
	};

	template <int N> struct ConstructIndexList {
		typedef typename Append<typename ConstructIndexList<N - 1>::Result, N - 1>::Result Result;
	};

	template <> struct ConstructIndexList<0> {
		typedef IndexList<> Result;
	};

	template <typename Char, typename IndexList> class XorStringT;
	template <typename Char, int... Index> class XorStringT<Char, IndexList<Index...> > {

	private:
		Char Value[sizeof...(Index)+1];

		static const Char XORKEY = static_cast<Char>(RandomNumber(0, 0xFFFF));

		template <typename Char>
		constexpr Char EncryptCharacterT(const Char Character, int Index) {
			return Character ^ (XORKEY + Index);
		}

	public:
		__forceinline constexpr XorStringT(const Char* const String)
			: Value{ EncryptCharacterT(String[Index], Index)... } {}

		const Char *decrypt() {
			for (int t = 0; t < sizeof...(Index); t++) {
				Value[t] = Value[t] ^ (XORKEY + t);
			}

			Value[sizeof...(Index)] = static_cast<Char>(0);

			return Value;
		}

		const Char *get() {
			return Value;
		}
	};

#define XorStr( String ) ( utils::XorStringT<char, utils::ConstructIndexList<sizeof( String ) - 1>::Result>( String ).decrypt() )
#define XORWSTR( String ) ( utils::XorStringT<wchar_t, utils::ConstructIndexList<(sizeof( String ) - 1) / 2>::Result>( String ).decrypt() ) //Long string

}
*/