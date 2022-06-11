#include <gtest/gtest.h>
#include "../Enigma/Enigma.h"
#include "../Enigma/Get_data_from_files.h"

const std::array<Rotor, number_of_rotors> rotors = get_rotors_from_file("../Enigma/Rotors.txt");
const std::array<Reflector, number_of_reflectors> reflectors = get_reflectors_from_file("../Enigma/Reflectors.txt");

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  //EXPECT_TRUE(false);
}

TEST(Test_letters, all_letters_reflect_in_each_other)
{
	for (int rotor_first_index = 0; rotor_first_index < number_of_rotors; rotor_first_index++)
	{
		for (int rotor_second_index = 0; rotor_second_index < number_of_rotors; rotor_second_index++)
		{
			if (rotor_second_index == rotor_first_index)
				continue;

			for (int rotor_third_index = 0; rotor_third_index < number_of_rotors; rotor_third_index++)
			{
				if (rotor_third_index == rotor_first_index || rotor_third_index == rotor_second_index)
					continue;

				for (int reflector_index = 0; reflector_index < number_of_reflectors; reflector_index++)
				{
					Enigma enigma(rotors[rotor_first_index], rotors[rotor_second_index], rotors[rotor_third_index], reflectors[reflector_index]);
					for (uint8_t first_pos = 0; first_pos < alphabet_cardinality; first_pos++)
					{
						for (uint8_t second_pos = 0; second_pos < alphabet_cardinality; second_pos++)
						{
							for (uint8_t third_pos = 0; third_pos < alphabet_cardinality; third_pos++)
							{
								for (char input_letter = 'A'; input_letter < 'A' + alphabet_cardinality; input_letter++)
								{
									char output_letter = enigma.set_positions_and_encrypt_letter(input_letter, first_pos, second_pos, third_pos);
									EXPECT_NE(input_letter, output_letter);
									output_letter = enigma.set_positions_and_encrypt_letter(output_letter, first_pos, second_pos, third_pos);
									EXPECT_EQ(output_letter, input_letter);
								}
							}
						}
					}
				}
			}
		}
	}
}