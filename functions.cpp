#include "tree_header.h"
#include <locale.h>

errors_t add_new_elem_in_base(Node* node);

errors_t guess(Node* node)
{
	if(!node)
		return BAD_PTR;

	if(node->left && node->right)
	{
		printf("Is it %s Please enter yes or no:\n", node->data);
		char answer[10];
		scanf("%s", answer);

		if(strcmp(answer, "yes") == 0 || strcmp(answer, "Yes") == 0 || strcmp(answer, "YES") == 0)   //yes
		{
			guess(node->left);
		}
		else   //no
		{
			guess(node->right);
		}
	}
	else
	{
		printf("You meaned %s?\n", node->data);
		char answer[10];
		scanf("%s", answer);
		if(strcmp(answer, "yes") == 0 || strcmp(answer, "Yes") == 0 || strcmp(answer, "YES") == 0)   //yes
		{
			printf("Ha! Ha! Ha! I have won again:)\n");
		}
		else   //no
			add_new_elem_in_base(node);
	}
	return ALL_OK;
}

char* get_str(int* len)
{
	int index = 0;
	char c;
	char* str = (char*)malloc(sizeof(char) * (MAX_STR_LEN + 1));
	//printf("%p\n", str);
	if(!str)
		return NULL;

	while((c = getchar()) == '\n' || c == ' ')
		;

	str[index] = c;
	++index;
	
	while(index < MAX_STR_LEN && (c = getchar()) != '\n')
	{
		str[index] = c;
		++index;
	}
	str[index] = '\0';

	str = (char*)realloc(str, (index + 2) * sizeof(char));
	*len = index;
	//printf("%p\n", str);

	return str;
}

errors_t add_new_elem_in_base(Node* node)
{
	printf("Oh, I have missed. Please enter you object\n");

	int len;
	char* new_object = get_str(&len);
	if(!new_object)
		return NO_MEMORY;

	printf("What thing %s is different from %s, it...?\n", new_object, node->data);

	//char* difference = (char*)malloc(sizeof(char) * (MAX_STR_LEN + 2));
	
	len = 0;
	char* difference = get_str(&len);
	if(!difference)
		return NO_MEMORY;

	//printf("len = %d", len);
	difference[len] = '?';
	difference[len + 1] = '\0';

	difference = (char*)realloc(difference, len + 2);
	if(!difference)
		return NO_MEMORY;

	Node* new_difference = (Node*)malloc(sizeof(Node));
	if(!new_difference)
	{
		free(difference);
		return NO_MEMORY;
	}

	new_difference->data = difference;
	new_difference->level = node->level;
	if(node->parent)
	{
		if(node->parent->left == node)
			node->parent->left = new_difference;
		else
			node->parent->right = new_difference;
	}

	new_difference->right = node;
	node->parent = new_difference;
	++node->level;


	Node* new_node = (Node*)malloc(sizeof(Node));
	if(!new_node)
		return NO_MEMORY;

	new_difference->left = new_node;

	new_node->parent = new_difference;
	new_node->data = new_object;
	new_node->level = node->level;
	new_node->left = NULL;
	new_node->right = NULL;

	return ALL_OK;
}

void fill_stack(Stack* stk, Node* node)
{
	if(node)
	{
		stack_push(stk, node);
		fill_stack(stk, node->parent);
	}

	return;

}

Stack* make_define_stack(Node* object)
{
	errors_t error;

	Stack* stk = stack_new(sizeof(Node));
	if(!stk)
		return NULL;

	fill_stack(stk, object);

	return stk;
}

errors_t print_definition(Stack* stk)
{
	if(!stk)
		return BAD_PTR;
	
	Node* new_node = (Node*)malloc(sizeof(Node));
	if(!new_node)
		return NO_MEMORY;

	Node* next_node = (Node*)malloc(sizeof(Node));
	if(!next_node)
		return NO_MEMORY;
	
	printf("It is ");

	while(stk->current_size > 1)
	{
		stack_pop(stk, new_node);
		if(new_node)
		{
			char* str = (char*)malloc(sizeof(char) * (strlen(new_node->data) + 1));
			if(!str)
				return NO_MEMORY;

			memcpy(str, new_node->data, strlen(new_node->data) + 1);

			str[strlen(str) - 1] = '\0';    // delete '?'

			

			stack_top(stk, next_node);  // check next node without delete

			if(!next_node->data || !new_node->right)
				return BAD_PTR;

			if(strcmp(next_node->data, new_node->right->data) == 0)
				printf("not ");

			if(stk->current_size == 2)
				printf("%s and ", str);

			else if(stk->current_size > 1)
				printf("%s, ", str);

			else
				printf("%s.\n", str);

			free(str);
		}
	}

	free(new_node);
	free(next_node);

	return ALL_OK;
}

errors_t define_object(Node* root)
{
	int len;
	char* value = get_str(&len);
	errors_t error;
	//printf("111 %d %s\n", len, value);

	Node* object = find(root, value, &error);
	if(!object)
		printf("Do not have such object\n");
	else
	{
		Stack* stk = make_define_stack(object);
		print_definition(stk);
		stk = stack_delete(stk);
	}

	free(value);

	return error;
}

errors_t print_compare(Stack* stk)
{
	if(!stk)
		return BAD_PTR;
	
	Node* new_node = (Node*)malloc(sizeof(Node));
	if(!new_node)
		return NO_MEMORY;

	Node* next_node = (Node*)malloc(sizeof(Node));
	if(!next_node)
		return NO_MEMORY;
	

	while(stk->current_size > 2)
	{
		stack_pop(stk, new_node);
		if(new_node)
		{
			char* str = (char*)malloc(sizeof(char) * (strlen(new_node->data) + 1));
			if(!str)
				return NO_MEMORY;

			memcpy(str, new_node->data, strlen(new_node->data) + 1);

			str[strlen(str) - 1] = '\0';    // delete '?'


			stack_top(stk, next_node);  // check next node without delete

			if(!next_node->data || !new_node->right)
				return BAD_PTR;

			if(strcmp(next_node->data, new_node->right->data) == 0)
				printf("not ");

			if(stk->current_size == 3)
				printf("%s and ", str);

			else if(stk->current_size > 1)
				printf("%s, ", str);

			else
				printf("%s.\n", str);

			free(str);
		}
	}

	printf("but ");

	stack_pop(stk, new_node);

	stack_top(stk, next_node);  // check next node without delete


	char* str = (char*)malloc(sizeof(char) * (strlen(new_node->data) + 1));
	if(!str)
		return NO_MEMORY;

	memcpy(str, new_node->data, strlen(new_node->data) + 1);

	str[strlen(str) - 1] = '\0';    // delete '?'


	if(!next_node->data || !new_node->right)
		return BAD_PTR;

	if(strcmp(next_node->data, new_node->right->data) == 0)
		printf("%s is not %s although %s is %s.\n", next_node->data, str, new_node->left->data, str);
	else
		printf("%s is %s although %s is not %s.\n", next_node->data, str, new_node->right->data, str);


	free(str);
	free(new_node);
	free(next_node);

	return ALL_OK;
}

errors_t compare_objects(Node* root)
{
	int len;
	char* value = get_str(&len);
	errors_t error;

	Node* object = find(root, value, &error);
	if(!object)
		printf("Do not have such object\n");
	else
	{
		Stack* stk = make_define_stack(object);
		if(stk->current_size > 2)
		{
			if(!object || !object->parent || !object->parent->left)
			{
				//printf("awful0\n");
				return BAD_PTR;
			}
			
			if(object == object->parent->left)
			{
				if(!object->data || !object->parent->right || !object->parent->right->data)
				{
					//printf("awful1\n");
					return BAD_PTR;
				}

				printf("%s and %s both are ", object->data, object->parent->right->data);
			}
			else
			{
				if(!object->data || !object->parent->left->data)
				{
					//printf("awful2\n");
					return BAD_PTR;
				}

				printf("%s and %s both are ", object->data, object->parent->left->data);
			}

			print_compare(stk);
		}
		else
		{
			Node* node_difference = (Node*)malloc(sizeof(Node));
			if(!node_difference)
				return NO_MEMORY;

			if(!node_difference->data)
				return BAD_PTR;

			stack_pop(stk, node_difference);

			if(object == object->parent->left)
			{
				if(!object || !object->data || !object->parent || !object->right || !object->right->data)
					return BAD_PTR;

				printf("%s is %s, but %s is not %s.\n", object->data, node_difference->data, object->parent->right->data, node_difference->data);
			}
			else
			{
				if(!object || !object->data || !object->parent || !object->left || !object->left->data)
					return BAD_PTR;

				printf("%s is not %s, but %s is %s.\n", object->data, node_difference->data, object->parent->left->data, node_difference->data);
			}

			free(node_difference);
		}

		stk = stack_delete(stk);
	}

	free(value);

	return error;
}