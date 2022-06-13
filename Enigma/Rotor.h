#pragma once
#include <array>
#include "Alphabet_mapping.h"


class Rotor
{
	alphabet_mapping  from_r_to_l_mapping;
	alphabet_mapping  from_l_to_r_mapping;
	uint8_t curr_pos;

	uint8_t pos_to_kick1;
	uint8_t pos_to_kick2;
public:
	Rotor();
	Rotor(const alphabet_mapping& mapping_array, uint8_t pos_to_kick1, uint8_t curr_pos = 0, uint8_t pos_to_kick2 = 0);

	Rotor(const Rotor&) = default;

	bool operator==(const Rotor& sec);

	void set_curr_pos(char pos) { curr_pos = pos - First_letter_of_alphabet; }
	void set_curr_pos(uint8_t pos) { curr_pos = pos; }
	uint8_t get_curr_pos() { return curr_pos; }

	char get_pos_to_kick1() { return pos_to_kick1; }
	char get_pos_to_kick2() { return pos_to_kick2; }

	bool next_pos();

	bool is_kick_next_rotor();
	uint8_t get_letter_r_to_l(uint8_t letter) { return from_r_to_l_mapping[letter]; }
	uint8_t get_letter_l_to_r(uint8_t letter) { return from_l_to_r_mapping[letter]; }

	~Rotor() = default;
};