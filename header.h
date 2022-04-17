#pragma once

// guess object
errors_t guess(Node* node);

// add new elem in base if he was not in base in this pkace yet
errors_t add_new_elem_in_base(Node* node);

errors_t delete_tree(Tree** tree);
int tree_dump(Tree* tree, errors_t reason);
errors_t file_print_tree(FILE* fp, Node* node, int n);

// make graph.txt file to we can make png file next with our tree
int print_graph(Tree* tree);
errors_t print_tree(Node* node, int n);

/*	reads akin_base 
	firstly after == NULL, save_tree != NULL(already is created), level == 1*/
void read_base(Tree* save_tree, int level, Node* after, errors_t* error);

Node* add_elem_after(Tree* info, Node* after, char* value, errors_t* error, int level);
Node* find(Node* root, char* value, errors_t* error);

Tree* create_tree(errors_t* error);

errors_t define_object(Node* root);