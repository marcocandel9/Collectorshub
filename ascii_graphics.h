#ifndef ASCII_GRAPHICS_H
#define ASCII_GRAPHICS_H
#include <stdio.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_BOLD  "\e[1m"
#define BOLD_OFF   "\e[m"
#define SCREEN_LINES 2

//Stampa a schermo "Collectors Hub" in Ascii Art
void collectors_hub_header();

//Stampa a schermo "User Menu" in Ascii Art
void user_menu_header();

//Stampa a schermo "Collection Menu" in Ascii art
void collection_menu_header(); 

void products_menu_header();

void admin_menu_header();

void superuser_menu_header();

void division_break_lines(const char *central_text,int width);

#endif