#ifndef MENU_H
#define MENU_H
#pragma once

#include "structure.h"

// Display Functions


void display_main_menu();
void display_sort_menu();
void display_search_menu();
void display_analysis_menu();


// Menu Handlers

void handle_add_system(SystemList& list);
void handle_delete_system(SystemList& list);
void handle_search_system(SystemList& list);
void handle_scan_system(SystemList& list);
void handle_sort_systems(SystemList& list);
void handle_display_options(SystemList& list);
void handle_analysis(SystemList& list);
void handle_file_operations(SystemList& list);

// Utility Functions


void pause_screen();
void clear_screen();
void print_header(string title);



#endif