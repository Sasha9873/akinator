#pragma once

#include <stdio.h>
#include <cstdlib>
#include <cstring>

typedef struct node
{
	size_t level = 0;
	char* data;
	struct node* parent = NULL;
	struct node* left = NULL;
	struct node* right = NULL;

} Node;

typedef struct tree{
	Node* root = NULL;
	//size_t k_levels = 0;
	size_t size = 0;
	//size_t max_data_size = 100;
	FILE* file_with_base;

} Tree;

typedef enum errors{
    ALL_OK           =  0,
    NO_MEMORY        = -1,
    AFTER_NULL_ELEM  = -2,
    NULL_ELEM 	     = -3,
    NULL_FILE        = -4,
    NO_TREE			 = -5,
    BAD_PTR			 = -6,
}errors_t;