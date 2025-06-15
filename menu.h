#ifndef MENU_H
#define MENU_H
#include "ascii_graphics.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_BOLD "\e[1m"
#define BOLD_OFF "\e[m"
#define SCREEN_LINES 2


void clear_screen();

int get_valid_input(int min, int max);

//Definizione della funzione per il menù principale
int login_menu();

int user_menu();

int collection_menu();

int products_menu();

int admin_menu();







#endif
