#pragma once
#include <array>
#include <stdint.h>

constexpr uint8_t alphabet_cardinality = 26;

using alphabet_mapping = std::array<uint8_t, alphabet_cardinality>;

//class alphabet_mapping : public std::array<char, alphabet_cardinality>
//{
//public:
//	alphabet_mapping() = default;
//	alphabet_mapping(const alphabet_mapping&) = default;
//	alphabet_mapping(std::array<char, alphabet_cardinality> arr) :std::array<char, alphabet_cardinality>(arr) {}
//
//	char& operator[](char c)
//	{
//		return std::array<char, alphabet_cardinality>::operator[](c - 'A');
//	}
//
//	const char& operator[](char c) const
//	{
//		return std::array<char, alphabet_cardinality>::operator[](c - 'A');
//	}
//};