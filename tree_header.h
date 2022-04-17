#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef struct node
{
	size_t level = 0;
	char* data = 0;
	struct node* parent = NULL;
	struct node* left = NULL;
	struct node* right = NULL;

} Node;

typedef struct tree{
	Node* root = NULL;
	//size_t k_levels = 0;
	size_t size = 0;
	FILE* file_with_base = NULL;
	FILE* logs = NULL;
	FILE* graph = NULL;

} Tree;

static const int MAX_STR_LEN = 100;

static const char *error_names[] = {
    "All is ok",
    "Not enough memory",
    "Push after an empty element",
    "Pop zero element",
    "Pointer to file is NULL",
    "You have no tree",
    "You send bad pointer",
    "You want to add NULL element",
    "Adding after NULL element"
};

typedef enum errors{
    ALL_OK           =  0,
    NO_MEMORY        = -1,
    AFTER_EMPTY_ELEM = -2,
    DELETE_ZERO_ELEM = -3,
    NULL_FILE        = -4,
    NO_TREE			 = -5,
    BAD_PTR			 = -6,
    NULL_ELEM 		 = -7,
    AFTER_NULL_ELEM	 = -8,
}errors_t;