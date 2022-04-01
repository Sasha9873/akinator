#include "header.h"

int main()
{
	char str[100];
	scanf("%s", str);
	printf("%c %c", str[strlen(str)], str[strlen(str) - 1]);
	/*errors_t error = ALL_OK;
	Tree* new_tree = create_tree(&error);
	add_elem(new_tree, 5, &error);	
	print_tree(new_tree->root, 0);

	add_elem(new_tree, 9, &error);
	add_elem(new_tree, 1, &error);
	print_tree(new_tree->root, 0);

	add_elem(new_tree, 10, &error);
	add_elem(new_tree, 7, &error);
	add_elem(new_tree, 6, &error);
	add_elem(new_tree, 8, &error);


	Node* ptr = find(new_tree->root, 10);
	printf("%p %d\n", ptr, ptr->data);

	FILE* fp = fopen("base_akin.txt", "w+");
	file_print_tree(fp, new_tree->root, 0);
	print_tree(new_tree->root, 0);*/

	return 0;
}