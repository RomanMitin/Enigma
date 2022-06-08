#pragma once
#include <array>
#include <fstream>
#include <string>
#include "Rotor.h"
#include "Reflector.h"

constexpr size_t number_of_rotors = 5;
constexpr size_t number_of_reflectors = 2;

std::array<Rotor, number_of_rotors> get_rotors_from_file(const std::string& file_name);

std::array<Reflector, number_of_reflectors> get_reflectors_from_file(const std::string& file_name);