#include "header.h"

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

errors_t recursion_find(Node* root, char* value, Node** ans)
{
	if(!root)
		return BAD_PTR;

	Node* node = root;
	if(!strcmp(node->data, value))
	{
		*ans = node;
		return ALL_OK
	}

	if(node->left)
		return recursion_find(node->left, value, ans);
	if(node->right)
		return recursion_find(node->right, value, ans);
}

Node* find(Node* root, char* value, errors_t* error)
{
	Node** node = (Node**)malloc(sizeof(Node*));
	if(!node)
	{
		*error = NO_MEMORY;
		return NULL;
	}
	
	*node = NULL;

	if(*error = recursion_find(root, value, node))
	{
		return NULL;
	}
	
	return *node;
}


//is_left == 1 if it is left child and 0 if a right child
Node* add_elem_after(Tree* info, Node* after, char* value, errors_t* error, int level, int is_left)  //if after == NULL then it is a top elem
{
	if(!error || !info)
		return NULL;

	if(!value)
	{
		*error = NULL_ELEM;
		return NULL;
	}

	Node* new_node = (Node*)malloc(sizeof(Node));
	if(!new_node)
	{
		*error = NO_MEMORY;
		return NULL;
	}

	new_node->data = (char*)calloc(sizeof(char), strlen(value) + 1);
	if(!new_node->data)
	{
		free(new_node);
		*error = NO_MEMORY;
		return NULL;
	}
	strcpy(new_node->data, value);

	new_node->level = level;
	new_node->left = NULL;
	new_node->right = NULL;

	if(!after)
	{
		info->root = new_node;
		new_node->parent = NULL;
		if(is_left)
			after->left = new_node;
		else
			after->right = new_node;
	}
	else
		new_node->parent = after;

	++info->size;

	return new_node;
}

//firstly after = NULL, save_tree != NULL, level == 1
int read_base(Tree* save_tree, int level, Node* after, errors_t* error)
{
	if(!save_tree || !save_tree->file_with_base)
		return BAD_PTR;

	char c = fgetc(save_tree->file_with_base);
	if(c == '{')
	{
		char* buffer = (char*)malloc(sizeof(char) * 100);
		fscanf(save_tree->file_with_base,"%s", buffer);
		if(buffer[strlen(buffer) - 1] == '}')
		{
			add_elem_after(info, after, buffer, error, level, 0);
		}
		else
		{
			create_new_node();


		}
	}
	if(level == 1)
	{
		//create_tree
		save_tree = (Tree*)malloc(sizeof(Tree));
		if(!save_tree)
			return NO_MEMORY;
		save_tree->root = (Node*)malloc(sizeof(Node));
		if(!save_tree->root)
		{
			free(save_tree);
			return NO_MEMORY;
		}
		save_tree->root->parent = NULL;
		save_tree->root->left = NULL;
		save_tree->root->right = NULL;
		save_tree->root->level = 1;

		save_tree->root->data = (char*)malloc(sizeof(char)*(strlen(str) + 1));
		if(!save_tree->root->data)
		{
			free(save_tree->root);
			free(save_tree);
			return NO_MEMORY;
		}
		strcpy(save_tree->root->data, str, strlen(str));
		++save_tree->size;
	}
	else
	{

	}
}

Node* add_elem(Tree* info, char* value, errors_t* error)
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

		info->root->data = (char*)malloc(sizeof(char)*strlen(value));
		if(!info->root->data)
		{
			free(info->root);
			*error = NO_MEMORY;
			return NULL;
		}
		printf("data = %s\n", info->root->data);

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

	printf("%s", node->data);
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

	fprintf(fp, "%s", node->data);
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
