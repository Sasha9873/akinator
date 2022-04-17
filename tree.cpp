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

	new_tree->graph = fopen("graph.txt", "w");
	if(!new_tree->graph)
	{
		free(new_tree);
		return NULL;
	}

	new_tree->logs = fopen("logs.txt", "w");
	if(!new_tree->logs)
	{
		fclose(new_tree->graph);
		free(new_tree);
		return NULL;
	}

	new_tree->file_with_base = fopen("base_akin.txt", "r");
	if(!new_tree->file_with_base)
	{
		fclose(new_tree->graph);
		fclose(new_tree->logs);
		free(new_tree);
		return NULL;
	}

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

errors_t recursion_find(Node* root, char* value, Node** ans)
{
	if(!root)
		return BAD_PTR;

	Node* node = root;
	//if(!strcmp(node->data, value))
	if(node->data, value)
	{
		*ans = node;
		return ALL_OK;
	}

	if(node->left)
		return recursion_find(node->left, value, ans);
	if(node->right)
		return recursion_find(node->right, value, ans);

	return ALL_OK;
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


//Node* add_elem_after(Tree* info, Node* after, char* value, errors_t* error, int level)  //if after == NULL then it is a top elem
Node* add_elem_after(Tree* info, Node* after, int value, errors_t* error, int level)  //if after == NULL then it is a top elem
{
	if(!error || !info)
		return NULL;

	if(!after)
	{
		*error = AFTER_NULL_ELEM;
		return NULL;
	}

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

	//new_node->data = (char*)calloc(sizeof(char), strlen(value) + 1);
	new_node->data = value;
	if(!new_node->data)
	{
		free(new_node);
		*error = NO_MEMORY;
		return NULL;
	}
	//strcpy(new_node->data, value);

	new_node->level = level;
	new_node->left = NULL;
	new_node->right = NULL;

	/*if(!after)
	{
		info->root = new_node;
		new_node->parent = NULL;

		if(is_left)
			after->left = new_node;
		else
			after->right = new_node;
	}
	else*/
	new_node->parent = after;

	++info->size;

	return new_node;
}

void skip_spaces(int* position, char* buffer)
{
	while(buffer[*position] == ' ' || buffer[*position] == '\n')
		++*position;
}

void read_str(char* buffer, int* position, char* str)
{
	int index = 0;
	while(buffer[*position] != '}' && buffer[*position] != '{')
	{
		str[index] = buffer[*position];
		++*position;
		++index;
	}
	str[index] = '\0';
}

Node* make_tree_from_base(Tree* info, int level, Node* after, errors_t* error, char* buffer, int* position)
{
	if(*position >= strlen(buffer))
		return NULL;

	if(!error)
		return NULL;

	if(!info || !after || !buffer)
	{
		*error = BAD_PTR;
		return NULL;
	}

	skip_spaces(position, buffer);

	char c = buffer[*position];
	if(c == '{')
	{
		++*position;

		char* str = (char*)malloc(sizeof(char) * 100);
		if(!str)
		{
			*error = NO_MEMORY;
			return NULL;
		}

		read_str(buffer, position, str);

		/*new_node->data = atoi(str);
		new_node->level = level;
		new_node->parent = after;*/

		Node* new_node = add_elem_after(info, after, atoi(str), error, level);
		free(str);

		skip_spaces(position, buffer);

		if(buffer[*position] != '}')
		{
			new_node->left = make_tree_from_base(info, level + 1, new_node, error, buffer, position);
			new_node->right = make_tree_from_base(info, level + 1, new_node, error, buffer, position);
			skip_spaces(position, buffer);

			if(buffer[*position] == '}')
				++*position;
		}
		else
			++*position;

		return new_node;
	}/**/
	else
		++*position;

	return NULL;
}

//firstly after = NULL, save_tree != NULL, level == 1
int read_base(Tree* save_tree, int level, Node* after, errors_t* error)
{
	if(!save_tree || !save_tree->file_with_base)
		return BAD_PTR;


	fseek(save_tree->file_with_base, 0, SEEK_END);

	size_t size = ftell(save_tree->file_with_base);

	fseek(save_tree->file_with_base, 0, SEEK_SET);

	char* buffer = (char*)calloc(size + 1, sizeof(char));

	fread(buffer, sizeof(char), size, save_tree->file_with_base);

	if(!after)
	{
		Node* empty_elem = (Node*)calloc(1, sizeof(Node));
		if(!empty_elem)
		{
			*error = NO_MEMORY;
			return 1;
		}

		int position = 0;
		save_tree->root = make_tree_from_base(save_tree, level, empty_elem, error, buffer, &position);

		free(empty_elem);

		printf(" root = %p\n", save_tree->root);
	}
	else
	{
		int position = 0;
		after->left = make_tree_from_base(save_tree, level, after, error, buffer, &position);
	}

	//free(empty_elem);

	
	/*if(level == 1)
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

		save_tree->root->data = atoi((char*)malloc(sizeof(char)*(strlen(buffer) + 1)));*/
		/*if(!save_tree->root->data)
		{
			free(save_tree->root);
			free(save_tree);
			return NO_MEMORY;
		}
		strcpy(save_tree->root->data, buffer, strlen(buffer));*/
		/*++save_tree->size;
	}
	else
	{

	}*/
	return ALL_OK;
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

errors_t recursion_print_for_graph(Tree* tree, Node* node, int* index)
{
	if(!tree || !node || !index)
		return BAD_PTR;

    fprintf(tree->graph, " box%d[style=\"filled\", fillcolor=\"white\", label = \"%d\"];\n", *index, node->data);
    
    if(node->left)
    {
    	++*index;
    	recursion_print_for_graph(tree, node->left, index);
    }
    if(node->right)
    {
    	++*index;
    	recursion_print_for_graph(tree, node->right, index);
    }

    return ALL_OK;
}

errors_t connections(Tree* tree, Node* node, int* index)
{
	if(!tree || !node || !index)
		return BAD_PTR;

	int cur_index = *index;
    int left_index = *index + 1;

    if(node->left)
    {
    	++*index;
    	connections(tree, node->left, index);
    }

    int right_index = *index + 1;

    if(node->right)
    {
    	++*index;
    	connections(tree, node->right, index);
    }

    if(node->left)
    	fprintf(tree->graph, " box%d->box%d[label = \" Yes \" color = green fontcolor = green];\n", cur_index, left_index);

    if(node->right)
    	fprintf(tree->graph, " box%d->box%d[label = \" No \" color = red fontcolor = red];\n", cur_index, right_index);

    return ALL_OK;
}

int print_graph(Tree* tree)
{
    if(tree->graph == NULL)
        return NULL_FILE;

    fprintf(tree->graph, "digraph G{\n node[fontsize=11];\n node[margin=\"0.01\"];\n");

    /*fprintf(tree->graph, " {\n    node[shape=\"plaintext\",style=\"invisible\"];\n    edge [color=\"white\"];\n    ");

    fprintf(Lst->graph, "    \"1\"");
    for(int index = 2; index < Lst->capacity + 1; index++)
        fprintf(Lst->graph, "->\"%d\"", index);
    fprintf(Lst->graph, "\n }\n");*/

    fprintf(tree->graph, " edge [color=\"blue\"];\n");

    /*fprintf(Lst->graph, " {rank = same; \"0\";box0;}\n \"box0\"[shape=\"record\", label = \"index|data|next|prev\"];\n");*/
    
    int index = 0;
    recursion_print_for_graph(tree, tree->root, &index);

    index = 0;
    connections(tree, tree->root, &index);

    fprintf(tree->graph, "}");

    return ALL_OK;

}

// n - amount of ' '
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

int tree_dump(Tree* tree, errors_t reason)
{
	if(!tree)
		return NO_TREE;

    if(tree->logs == NULL)
        return NULL_FILE;

    if(reason != ALL_OK)
        fprintf(tree->logs, "Dump was called because %s(%d)\n", error_names[abs(reason)], reason);

    fprintf(tree->logs, "Tree\n{\n  size = %ld\n\n  Our tree:\n", tree->size);

    file_print_tree(tree->logs, tree->root, 3);

    fprintf(tree->logs, "\n  file_with_base = %p\n", tree->file_with_base);
    fprintf(tree->logs, "  logs = %p\n", tree->logs);
    fprintf(tree->logs, "  graph = %p\n", tree->graph);


    fprintf(tree->logs,"}\n\n");

    return ALL_OK;
}



int main()
{
	errors_t error = ALL_OK;
	Tree* new_tree = create_tree(&error);


	fseek(new_tree->file_with_base, 0, SEEK_END);

	size_t size = ftell(new_tree->file_with_base);
	printf("size1 = %ld\n", size);

	fseek(new_tree->file_with_base, 0, SEEK_SET);


	read_base(new_tree, 1, NULL, &error);
	/*add_elem(new_tree, 5, &error);	
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

	FILE* fp = fopen("1.txt", "r");*/
	file_print_tree(new_tree->file_with_base, new_tree->root, 0);
	print_tree(new_tree->root, 0);
	print_graph(new_tree);
	tree_dump(new_tree, ALL_OK);

	return 0;
}