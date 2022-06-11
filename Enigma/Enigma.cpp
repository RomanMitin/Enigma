#include "Enigma.h"


uint8_t mathabs(int c)
{
	while (c < 0)
		c += alphabet_cardinality;
	return c;
}

Enigma::Enigma(const Rotor& first_rotor, const Rotor& second_rotor, const Rotor& third_rotor, const Reflector& reflector)
	:enigma_state(), rotors({ first_rotor,second_rotor,third_rotor }), reflector(reflector)
{
	Rotor default_rotor = Rotor();
	Reflector default_reflector = Reflector();

	if (second_rotor != default_rotor)
	{
		enigma_state |= no_second_rotor;
		if (third_rotor != default_rotor)
		{
			enigma_state |= no_third_rotor;
			if (reflector != default_reflector)
				enigma_state |= no_reflector;
		}
	}
}

void Enigma::set_reflector(const Reflector& reflector)
{
	enigma_state |= Enigma_states::no_reflector;
	this->reflector = reflector;
}

Reflector Enigma::erase_reflector()
{
	enigma_state &= ~(Enigma_states::no_reflector);
	return reflector;
}

void Enigma::set_rotor(const Rotor& new_rotor, uint8_t place_for_new_rotor)
{
	switch (place_for_new_rotor)
	{
	case 0:
		enigma_state |= Enigma_states::no_first_rotor;
		break;
	case 1:
		enigma_state |= Enigma_states::no_second_rotor;
		break;
	case 2:
		enigma_state |= Enigma_states::no_third_rotor;
		break;
	default:
		throw std::string("Wrong place for rotor");
		break;
	}

	rotors[place_for_new_rotor] = new_rotor;
}

Rotor Enigma::erase_rotor(uint8_t rotor_number)
{
	switch (rotor_number)
	{
	case 0:
		enigma_state &= ~(Enigma_states::no_first_rotor);
		break;
	case 1:
		enigma_state &= ~(Enigma_states::no_second_rotor);
		break;
	case 2:
		enigma_state &= ~(Enigma_states::no_third_rotor);
		break;
	default:
		throw std::string("Wrong place for rotor");
		break;
	}

	return rotors[rotor_number];
}

void Enigma::set_rotors_pos(uint8_t pos1, uint8_t pos2, uint8_t pos3)
{
	if (pos1 >= alphabet_cardinality || pos2 >= alphabet_cardinality || pos3 >= alphabet_cardinality)
		throw std::string("Wrong position to set in Enigma");

	rotors[0].set_curr_pos(pos1);
	rotors[1].set_curr_pos(pos2);
	rotors[2].set_curr_pos(pos3);
}

void Enigma::set_rotors_pos(char pos1, char pos2, char pos3)
{
	set_rotors_pos(uint8_t(pos1 - 'A'), uint8_t(pos2 - 'A'), uint8_t(pos3 - 'A'));
}

void Enigma::set_rotors_pos(Rotors_pos pos)
{
	set_rotors_pos(pos.first_rotor_pos, pos.second_rotor_pos, pos.third_rotor_pos);
}

Rotors_pos Enigma::get_rotors_pos()
{
	return Rotors_pos(rotors[0].get_curr_pos(), rotors[1].get_curr_pos(), rotors[2].get_curr_pos());
}

char Enigma::encrypt_letter(char letter)
{
	if (!check_letter_correctness(letter))
		throw std::string("Wrong input letter in enigma");

	uint8_t _letter = letter - 'A';

	if (rotors[2].next_pos())
		if (rotors[1].next_pos())
			rotors[0].next_pos();

	// right rotor mapping
	_letter = (_letter + rotors[2].get_curr_pos()) % alphabet_cardinality;
	_letter = rotors[2].get_letter_r_to_l(_letter);

	// middle rotor mapping
	_letter = (_letter + mathabs(rotors[1].get_curr_pos() - rotors[2].get_curr_pos())) % alphabet_cardinality;
	_letter = rotors[1].get_letter_r_to_l(_letter);

	// left rotor mapping
	_letter = (_letter + mathabs(rotors[0].get_curr_pos() - rotors[1].get_curr_pos())) % alphabet_cardinality;
	_letter = rotors[0].get_letter_r_to_l(_letter);

	//reflector mapping
	_letter = mathabs(_letter - rotors[0].get_curr_pos()) % alphabet_cardinality;
	_letter = reflector.reflect_letter(_letter);

	// left rotor mapping
	_letter = (_letter + rotors[0].get_curr_pos()) % alphabet_cardinality;
	_letter = rotors[0].get_letter_l_to_r(_letter);

	// middle rotor mapping
	_letter = (_letter + mathabs(rotors[1].get_curr_pos() - rotors[0].get_curr_pos())) % alphabet_cardinality;
	_letter = rotors[1].get_letter_l_to_r(_letter);

	// right rotor mapping
	_letter = (_letter + mathabs(rotors[2].get_curr_pos() - rotors[1].get_curr_pos())) % alphabet_cardinality;
	_letter = rotors[2].get_letter_l_to_r(_letter);

	_letter = mathabs(_letter - rotors[2].get_curr_pos()) % alphabet_cardinality;

	return _letter + 'A';
}

char Enigma::set_positions_and_encrypt_letter(char letter, char pos1, char pos2, char pos3)
{
	return set_positions_and_encrypt_letter(letter, uint8_t(pos1 - 'A'), uint8_t(pos2 - 'A'), uint8_t(pos3 - 'A'));
}

std::string Enigma::encrypt_text(const std::string& text)
{
	if (!check_text_correctness(text))
		throw std::string("Wrong input text in enigma");

	std::string result;
	result.reserve(text.capacity());
	for (const char letter : text)
	{
		result.push_back(encrypt_letter(letter));
	}

	return result;
}

char Enigma::set_positions_and_encrypt_letter(char letter, uint8_t pos1, uint8_t pos2, uint8_t pos3)
{
	rotors[0].set_curr_pos(pos1);
	rotors[1].set_curr_pos(pos2);
	rotors[2].set_curr_pos(pos3);

	return encrypt_letter(letter);
}

std::string Enigma::set_positions_and_encrypt_text(const std::string& text, uint8_t pos1, uint8_t pos2, uint8_t pos3)
{
	rotors[0].set_curr_pos(pos1);
	rotors[1].set_curr_pos(pos2);
	rotors[2].set_curr_pos(pos3);

	return encrypt_text(text);
}

std::string Enigma::get_enigma_state_string()
{
	std::string result;

	if (enigma_state & no_reflector)
		result += "No_reflector\n";

	if (enigma_state & no_first_rotor)
		result += "No first rotor\n";

	if (enigma_state & no_second_rotor)
		result += "No second rotor\n";

	if (enigma_state & no_third_rotor)
		result += "No third rotor\n";

	return result;
}

bool Enigma::check_letter_correctness(const char letter)
{
	return letter >= 'A' && letter <= 'Z';
}

bool Enigma::check_text_correctness(const std::string& text)
{
	for (const char letter : text)
		if (!check_letter_correctness(letter))
			return false;
	return true;
}




