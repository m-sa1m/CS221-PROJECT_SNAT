#ifndef INPUT_H
#define INPUT_H
#pragma once

#include <string>
using namespace std;


string get_string_input(string prompt);

int get_int_input(string prompt, int min, int max);

bool get_bool_input(string prompt);


string get_ip_input(string prompt);


bool is_valid_ip(string ip);

bool is_valid_name(string name);

#endif
