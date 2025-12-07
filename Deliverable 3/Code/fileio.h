#ifndef FILEIO_H
#define FILEIO_H
#pragma once

#include "structure.h"
#include <string>
using namespace std;


// Save all systems to file
bool save_systems_to_file(SystemList& list, string filename);

// Load systems from file
bool load_systems_from_file(SystemList& list, string filename);

// Generate detailed report
void generate_report(SystemList& list, string filename);

#endif