#include <iostream>
#include <array>
#include <fstream>
#include <chrono>
#include "Enigma.h"
#include "Get_data_from_files.h"


const std::array<Rotor, number_of_rotors> rotors = get_rotors_from_file("Rotors.txt");
const std::array<Reflector, number_of_reflectors> reflectors = get_reflectors_from_file("Reflectors.txt");

using namespace std;

int main()
{
	Enigma enigma(rotors[2], rotors[1], rotors[0], reflectors[0]);

	/*std::cout << enigma.get_enigma_state() << '\n';

	std::cout << enigma.set_positions_and_encrypt_text("Sspgf snnkg\n", 'A', 'J', 'F') << '\n';*/

	ifstream in;
	in.open("Code.txt");
	if (!in.is_open())
		exit(1);

	string enigma_input;
	enigma_input.reserve(1024 * 1024);
	getline(in, enigma_input, char(0));
	//std::cout << enigma_input;
	/*while (in.eof())
	{
		enigma_input.push_back(in.get());
	}*/

	std::cout << "End of file reading, start of encrypting\n";

	string enigma_output = enigma.set_positions_and_encrypt_text(enigma_input, 'A', 'D', 'T');

	ofstream out;
	out.open("Encode.txt");

	std::cout << "End of encrypting, start writing\n";

	out.write(enigma_output.c_str(), enigma_output.size());

	out.close();

	return 0;
}