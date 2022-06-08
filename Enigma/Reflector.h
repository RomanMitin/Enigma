#pragma once
#include <array>
#include "Alphabet_mapping.h"


class Reflector
{
	alphabet_mapping reflect_mapping;
public:
	Reflector() :reflect_mapping() {}
	Reflector(const Reflector&) = default;

	Reflector(const alphabet_mapping& mapping_array) :reflect_mapping(mapping_array) {}

	bool operator==(const Reflector& sec) { return reflect_mapping == sec.reflect_mapping; };

	uint8_t reflect_letter(uint8_t letter) { return reflect_mapping[letter]; }

	~Reflector() = default;
};