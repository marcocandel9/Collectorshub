#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "collection.h"

#ifndef COLLECTIONS_H
#define COLLECTIONS_H

struct collections{
    collection collection_elem;
    struct collections* next;
};

typedef struct collections* collections;

int create_collections_list(collections* collections_list_head);

int insert_collection(collections* collections_list_head, char new_name[MAX_STR_LEN], char new_type[MAX_STR_LEN]);

int remove_collection(collections* collections_list_head, char key_name[MAX_STR_LEN]);

int search_and_modify_collection(collections* collections_list_head, char key_name[MAX_STR_LEN], char new_name[MAX_STR_LEN], char new_type[MAX_STR_LEN]);

int print_collections(collections collections_list_head);

#endif