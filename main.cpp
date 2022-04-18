#include "tree_header.h"
#include "header.h"

int main()
{
	errors_t error = ALL_OK;
	Tree* new_tree = create_tree(&error);


	fseek(new_tree->file_with_base, 0, SEEK_END);

	size_t size = ftell(new_tree->file_with_base);
	//printf("size1 = %ld\n", size);

	fseek(new_tree->file_with_base, 0, SEEK_SET);

	read_base(new_tree, 1, NULL, &error);

	int enter;
	scanf("%d", &enter);

	while(enter)
	{
		if(enter == 1)
			guess(new_tree->root);
		else if(enter == 2)
			define_object(new_tree->root);
		else if(enter == 3)
			compare_objects(new_tree->root);

		scanf("%d", &enter);
	}

    //change old bas to new one
	fclose(new_tree->file_with_base);
	new_tree->file_with_base = fopen("base_akin.txt", "w");

	file_print_tree(new_tree->file_with_base, new_tree->root, 0);


	print_tree(new_tree->root, 0);
	print_graph(new_tree);
	DUMP(ALL_OK);
	delete_tree(&new_tree);
	tree_dump(new_tree, ALL_OK);

	return 0;
}