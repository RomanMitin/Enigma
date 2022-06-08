#pragma once
#include <cstdint>
#include <cstddef>
#include <string>
#include "Reflector.h"
#include "Rotor.h"


struct Rotors_pos
{
	uint8_t first_rotor_pos = 0;
	uint8_t second_rotor_pos = 0;
	uint8_t third_rotor_pos = 0;

	Rotors_pos(uint8_t pos1, uint8_t pos2, uint8_t pos3) :first_rotor_pos(pos1), second_rotor_pos(pos2), third_rotor_pos(pos3) {}
};

class Enigma
{
public:
	Enigma() = default;
	Enigma(const Enigma&) = default;

	Enigma(const Rotor& first_rotor, const Rotor& second_rotor = Rotor(), \
		const Rotor& third_rotor = Rotor(), const Reflector& reflector = Reflector());

	enum class Enigma_states_base : uint8_t
	{
		no_reflector = 1, no_first_rotor, no_second_rotor, no_third_rotor, max_states_for_enigma = no_third_rotor
	};

	enum Enigma_states : uint8_t
	{
		no_reflector = (1 << static_cast<uint8_t>(Enigma_states_base::no_reflector)), 
		no_first_rotor = (1 << static_cast<uint8_t>(Enigma_states_base::no_first_rotor)),
		no_second_rotor = (1 << static_cast<uint8_t>(Enigma_states_base::no_second_rotor)),
		no_third_rotor = (1 << static_cast<uint8_t>(Enigma_states_base::no_third_rotor)),
		max_states_for_enigma = (1 << (static_cast<uint8_t>(Enigma_states_base::max_states_for_enigma) + 1))
	};

	void set_reflector(const Reflector& reflector);
	Reflector erase_reflector();

	void set_rotor(const Rotor& new_rotor, uint8_t place_for_new_rotor);
	Rotor erase_rotor(uint8_t rotor_number);

	void set_rotors_pos(uint8_t pos1, uint8_t pos2, uint8_t pos3);
	void set_rotors_pos(char pos1, char pos2, char pos3);
	void set_rotors_pos(Rotors_pos pos);

	Rotors_pos get_rotors_pos();

	char encrypt_letter(char letter);
	std::string encrypt_text(const std::string& text);

	char set_positions_and_encrypt_letter(char letter, uint8_t pos1, uint8_t pos2, uint8_t pos3);
	char set_positions_and_encrypt_letter(char letter, char pos1, char pos2, char pos3);

	std::string set_positions_and_encrypt_text(const std::string& text, uint8_t pos1, uint8_t pos2, uint8_t pos3);
	std::string set_positions_and_encrypt_text(const std::string& text, char pos1, char pos2, char pos3);

	/*char decrypt_letter(char letter);
	std::string decrypt_text(const std::string& text);*/

	//std::array<Enigma_states, static_cast<size_t>(Enigma_states_base::max_states_for_enigma)> get_enigma_state();
	std::string get_enigma_state_string();

	~Enigma() = default;

private:
	uint8_t enigma_state;

	std::array<Rotor, 3> rotors;
	Reflector reflector;

	bool check_letter_correctness(const char letter);
	bool check_text_correctness(const std::string& text);
};