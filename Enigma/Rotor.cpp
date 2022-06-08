#include <algorithm>
#include "Rotor.h"

Rotor::Rotor()
	:from_r_to_l_mapping(), from_l_to_r_mapping(), curr_pos(0), pos_to_kick1(alphabet_cardinality), pos_to_kick2(alphabet_cardinality)
{}

Rotor::Rotor(const alphabet_mapping& mapping_array, uint8_t pos_to_kick1, uint8_t curr_pos, uint8_t pos_to_kick2)
	:from_r_to_l_mapping(mapping_array), from_l_to_r_mapping(), curr_pos(curr_pos), pos_to_kick1(pos_to_kick1), pos_to_kick2(pos_to_kick2)
{
	for (char i =  0; i < alphabet_cardinality; i++)
	{
		from_l_to_r_mapping[from_r_to_l_mapping[i]] = i;
	}
}

bool Rotor::operator==(const Rotor& sec)
{
	return from_r_to_l_mapping == sec.from_r_to_l_mapping && pos_to_kick1 == sec.pos_to_kick1 && pos_to_kick2 == sec.pos_to_kick2;
}

bool Rotor::is_kick_next_rotor()
{
	return (curr_pos == pos_to_kick1) || (curr_pos == pos_to_kick2);
}

bool Rotor::next_pos()
{
	curr_pos = (curr_pos + 1) % alphabet_cardinality;
	return is_kick_next_rotor();
}