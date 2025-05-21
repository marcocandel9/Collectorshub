#ifndef ASCII_GRAPHICS_H
#define ASCII_GRAPHICS_H

#include <stdio.h>



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