#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "collection.h"

#ifndef COLLECTIONS_H
#define COLLECTIONS_H

struct collections{
    collection collection_list_head;
    struct collections* next;
};

typedef collections* collections;

int create_collections_list(collections* collection_list_head);

int insert_collection(collections* collection_list_head, char new_name[MAX_STR_LEN], char new_type[MAX_STR_LEN]);

int exist_sorted(collections collection_list_head, char key_name[MAX_STR_LEN]);

int search_and_modify_collection(collections* collection_list_head, char key_name[MAX_STR_LEN], char new_name[MAX_STR_LEN], char new_type[MAX_STR_LEN]);

int remove_collection(collections* collection_list_head, char key_name[MAX_STR_LEN]);

int search_and_print_collection(collections collection_list_head, char key_name[MAX_STR_LEN]);

int print_collections(collections collection_list_head);

#endif