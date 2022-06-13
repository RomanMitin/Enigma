#include "Get_data_from_files.h"

std::array<Rotor, number_of_rotors> get_rotors_from_file(const std::string& file_name)
{
	std::ifstream input_file(file_name);
	std::array<Rotor, number_of_rotors> result;

	char c = 0;
	for (int j = 0; j < number_of_rotors; j++)
	{
		alphabet_mapping mapping_array;

		for (char i = 0; i < alphabet_cardinality; i++)
		{
			input_file >> c;
			mapping_array[i] = c - First_letter_of_alphabet;
			input_file.ignore();
		}
		input_file >> c;
		uint8_t pos_to_kick1 = c - First_letter_of_alphabet;
		//input_file >> c;
		if (false)
		{
			//handle pos_to_kick2
			/*input_file >> c;
			result[j] = Rotor{ mapping_array, pos_to_kick1, 0, c };
			input_file.ignore();*/
		}
		else
		{
			result[j] = Rotor( mapping_array, pos_to_kick1 );
			//input_file.ignore();
		}
	}

	return result;
}

std::array<Reflector, number_of_reflectors> get_reflectors_from_file(const std::string& file_name)
{
	std::ifstream input_file(file_name);
	std::array<Reflector, number_of_reflectors> result;

	char c1;
	char c2;
	for (int j = 0; j < number_of_reflectors; j++)
	{
		alphabet_mapping mapping_array;

		for (int i = 0; i < alphabet_cardinality / 2; i++)
		{
			input_file >> c1;
			input_file >> c2;

			c1 -= First_letter_of_alphabet;
			c2 -= First_letter_of_alphabet;

			mapping_array[c1] = c2;
			mapping_array[c2] = c1;
			input_file.ignore(3);
		}
		result[j] = Reflector(mapping_array);
	}

	return result;
}