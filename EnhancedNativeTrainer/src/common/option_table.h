#pragma once
#include <string>
#include <vector>

// A single (caption, value) row for a menu option list. Storing both fields
// together - instead of two hand-maintained parallel vectors that must be
// kept the same length and order - makes it impossible for a caption and
// its value to drift out of sync.
template<class T>
struct Option {
	const char* caption;
	T value;
};

// Extracts the captions from a fixed-size Option table, in order.
template<class T, size_t N>
inline std::vector<std::string> captionsOf(const Option<T>(&table)[N]) {
	std::vector<std::string> out;
	out.reserve(N);
	for (auto& o : table) out.push_back(o.caption);
	return out;
}

// Extracts the values from a fixed-size Option table, in order.
template<class T, size_t N>
inline std::vector<T> valuesOf(const Option<T>(&table)[N]) {
	std::vector<T> out;
	out.reserve(N);
	for (auto& o : table) out.push_back(o.value);
	return out;
}
