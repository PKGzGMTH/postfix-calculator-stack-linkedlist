#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct	s_stack
{
	int				data;
	struct s_stack	*next;
}	t_stack;

// create and add linked list to first of stack
bool	push(int num, t_stack **stack)
{
	t_stack	*dest;

	dest = NULL;
	dest = (t_stack*) calloc (sizeof(t_stack), 1);
	if (!dest)
		return (0);
	dest->data = num;
	dest->next = *stack;
	*stack = dest;
	return (1);
}

// pop first linked list of stack
bool	pop(int *top, t_stack **stack)
{
	t_stack	*temp;

	// if stack is not NULL then pop!
	if (*stack)
	{
		temp = *stack;
		*top = temp->data;
		*stack = (*stack)->next;
		free(temp);
		return (1);
	}
	else
		return (0);
}

// calculate n1 and n2 with operator
int	calculate(char *c, int n1, int n2)
{
	switch (*c)
	{
		case '+': return (n1 + n2); break;
		case '-': return (n1 - n2); break;
		case 'x': return (n1 * n2); break;
		case '/': return (n1 / n2); break;
	}
	return (0);
}

void print_result(t_stack *stack, int value)
{
	// if stack is empty
	if (!stack)
		printf("Empty Stack!\n");
	// if stack is remaining data more than one
	else if (stack->next)
	{
		printf("There is Remaining data in Stack!\n");
		// traverse in linked-list
		while (stack)
		{
			printf ("%d -> ", stack->data);
			stack = stack->next;
		}
		printf ("Null\n");
	}
	// if stack can pop the element
	else if (pop(&value, &stack))
		printf("Value is: %d\n", value);
}

// argc is argument count
// argv is array of argument
int	main(int argc, char **argv)
{
	int		i, n1, n2, value;
	t_stack	*stack;

	i = 1;
	stack = NULL;
	// if argc == 1 it's mean no argument entered except "./a.out"
	if (argc == 1)
		printf("Please Enter a argument!!!\nExample:\n./a.out 3 4 5 x +\n");
	else
	{
		while (i < argc)
		{
			if (!strchr("+-x/", argv[i][0]))
			{
				// check first of argument[i] is not + - x /
				// then use atoi to check if string is numeric
				if (!atoi(argv[i]) && strcmp(argv[i], "0"))
				{
					printf("Please Enter only Numeric and + - x / only!\n");
					return (-1);
				}
				else if (!push(atoi(argv[i]), &stack))
					return (-1);
			}
			else if (strlen(argv[i]) == 1 && pop(&n2, &stack) && pop(&n1, &stack))
			{
				// then use atoi to convert string to int and push to stack
				value = calculate(argv[i], n1, n2);
				if (!push(value, &stack))
					return (-1);
			}
			else
			{
				printf("Error! Please check your Input.\n");
				break;
			}
			i++;
		}
		print_result(stack, value);
	}
	return (0);
}
