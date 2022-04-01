#include "tree_header.h"

Tree* create_tree(errors_t* error)
{
	Tree* new_tree = (Tree*)malloc(sizeof(Tree));
	if(!new_tree)
	{
		*error = NO_MEMORY;
		return NULL;
	}
	new_tree->root = NULL;
	/*new_tree->root = (Node*)malloc(sizeof(Node));
	if(!new_tree->root)
	{
		free(new_tree);
		new_tree = NULL;
		*error = NO_MEMORY;
		return NULL;
	}	*/
	new_tree->size = 0;

	return new_tree;
}

Node* find(Node* root, int value)
{
	Node* node = root;
	while(node)
	{
		if(node->data == value)
			return node;
		if(value > node->data)
			node = node->right;
		else
			node = node->left;
	}
	return NULL;
}

Node* add_elem(Tree* info, int value, errors_t* error)
{
	if(!info)
	{
		*error = NO_TREE;
		return NULL;
	}

	Node* root = info->root;

	if(!root)
	{
		printf("aaa\n");
		info->root = (Node*)malloc(sizeof(Node));
		printf("%p\n", info->root);
		if(!info->root)
		{
			*error = NO_MEMORY;
			return NULL;
		}
		info->root->level = 1;
		info->root->left = NULL;
		info->root->right = NULL;
		info->root->parent = NULL;
		info->root->data = value;

		printf("data = %d\n", info->root->data);

		++info->size;

		return root;
	}

	Node* node = root;

	while(node)
	{
		if(value > node->data)
		{
			if(node->right)
				node = node->right;
			else
			{
				node->right = (Node*)malloc(sizeof(Node));
				if(!node->right)
				{
					*error = NO_MEMORY;
					return NULL;
				}
				node->right->level = node->level + 1;
				node->right->left = NULL;
				node->right->right = NULL;
				node->right->parent = node;
				node->right->data = value;
				
				++info->size;

				return node->right;
			}
		}
		else
		{
			if(node->left)
				node = node->left;
			else
			{
				node->left = (Node*)malloc(sizeof(Node));
				if(!node->left)
				{
					*error = NO_MEMORY;
					return NULL;
				}
				node->left->level = node->level + 1;
				node->left->left = NULL;
				node->left->right = NULL;
				node->left->parent = node;
				node->left->data = value;

				++info->size;

				return node->left;
			}
		}
	}

	return NULL;
}

errors_t print_tree(Node* node, int n)
{
	if(!node)
	{
		printf("{}\n");
		return BAD_PTR;
	}

	printf("\n%*s", n, "{");

	printf("%d", node->data);
	if(node->left)
		print_tree(node->left, n + 3);
	if(node->right)
		print_tree(node->right, n + 3);

	if(node->right || node->left)
		printf("%*s\n", n, "}");
	else
		printf("%s\n", "}");

	return ALL_OK;
}

errors_t file_print_tree(FILE* fp, Node* node, int n)
{
	if(!node)
	{
		fprintf(fp, "{}\n");
		return BAD_PTR;
	}

	fprintf(fp, "\n%*s", n, "{");

	fprintf(fp, "%d", node->data);
	if(node->left)
		file_print_tree(fp, node->left, n + 3);
	if(node->right)
		file_print_tree(fp, node->right, n + 3);

	if(node->right || node->left)
		fprintf(fp, "%*s\n", n, "}");
	else
		fprintf(fp, "%s\n", "}");

	return ALL_OK;
}


int main()
{
	errors_t error = ALL_OK;
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
	print_tree(new_tree->root, 0);

	return 0;
}