#include <gtest/gtest.h>
#include <string>
#include "../Enigma/Enigma.h"
#include "../Enigma/Get_data_from_files.h"

const std::array<Rotor, number_of_rotors> rotors = get_rotors_from_file("../Enigma/Rotors.txt");
const std::array<Reflector, number_of_reflectors> reflectors = get_reflectors_from_file("../Enigma/Reflectors.txt");

TEST(Test_enigma_states, enigma_is_not_ready_to_work)
{
	std::string expect = "No reflector\nNo first rotor\nNo second rotor\nNo third rotor\n";

	Enigma enigma{};
	std::string actual = enigma.get_enigma_state();

	EXPECT_EQ(expect, actual);
}

TEST(Test_enigma_states, test_set_reflector)
{
	std::string expect = "No first rotor\nNo second rotor\nNo third rotor\n";

	Enigma enigma{};
	enigma.set_reflector(reflectors[0]);
	std::string actual = enigma.get_enigma_state();

	EXPECT_EQ(expect, actual);
}

TEST(Test_enigma_states, test_set_rotors)
{
	std::string expect = "No reflector\nNo second rotor\nNo third rotor\n";

	Enigma enigma{};
	enigma.set_rotor(rotors[0], 0);
	std::string actual = enigma.get_enigma_state();

	EXPECT_EQ(expect, actual);

	expect = "No reflector\nNo third rotor\n";

	enigma.set_rotor(rotors[1], 1);
	actual = enigma.get_enigma_state();

	EXPECT_EQ(expect, actual);

	expect = "No reflector\n";

	enigma.set_rotor(rotors[2], 2);
	actual = enigma.get_enigma_state();

	EXPECT_EQ(expect, actual);

}

TEST(Test_enigma_states, test_erase_reflector)
{
	std::string expect = "No reflector\n";

	Enigma enigma(rotors[0], rotors[1], rotors[2], reflectors[0]);
	enigma.erase_reflector();
	std::string actual = enigma.get_enigma_state();

	EXPECT_EQ(expect, actual);
}

TEST(Test_enigma_states, test_erase_rotors)
{
	std::string expect = "No first rotor\n";

	Enigma enigma(rotors[0], rotors[1], rotors[2], reflectors[0]);
	enigma.erase_rotor(0);
	std::string actual = enigma.get_enigma_state();

	EXPECT_EQ(expect, actual);

	expect = "No first rotor\nNo second rotor\n";

	enigma.erase_rotor(1);
	actual = enigma.get_enigma_state();

	EXPECT_EQ(expect, actual);

	expect = "No first rotor\nNo second rotor\nNo third rotor\n";

	enigma.erase_rotor(2);
	actual = enigma.get_enigma_state();

	EXPECT_EQ(expect, actual);

}

TEST(Test_enigma_states, enigma_ready_to_work) 
{
	std::string expect = "Enigma is ready to encrypt letters\n";
	
	Enigma enigma(rotors[0], rotors[1], rotors[2], reflectors[0]);
	std::string actual = enigma.get_enigma_state();

	EXPECT_EQ(expect, actual);
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
								for (char input_letter = First_letter_of_alphabet; input_letter < First_letter_of_alphabet + alphabet_cardinality; input_letter++)
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