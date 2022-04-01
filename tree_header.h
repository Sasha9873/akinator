#include <cstdio>
#include <cstdlib>

typedef struct node
{
	size_t level = 0;
	int data = 0;
	struct node* parent = NULL;
	struct node* left = NULL;
	struct node* right = NULL;

} Node;

typedef struct tree{
	Node* root = NULL;
	//size_t k_levels = 0;
	size_t size = 0;

} Tree;

typedef enum errors{
    ALL_OK           =  0,
    NO_MEMORY        = -1,
    AFTER_EMPTY_ELEM = -2,
    DELETE_ZERO_ELEM = -3,
    NULL_FILE        = -4,
    NO_TREE			 = -5,
    BAD_PTR			 = -6,
}errors_t;