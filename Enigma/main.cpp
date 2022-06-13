#include <iostream>
#include <array>
#include "Enigma.h"
#include "Get_data_from_files.h"


const std::array<Rotor, number_of_rotors> rotors = get_rotors_from_file("Rotors.txt");
const std::array<Reflector, number_of_reflectors> reflectors = get_reflectors_from_file("Reflectors.txt");


int main()
{
	Enigma enigma(rotors[2], rotors[1], rotors[0], reflectors[0]);
	
	std::cout << enigma.get_enigma_state() << '\n';

	std::cout << enigma.set_positions_and_encrypt_text("AKWZTUNS", 'A', 'J', 'F') << '\n';

	return 0;
}