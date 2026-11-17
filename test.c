#include "push_swap.h"
#include <stdio.h>

t_node	*new_node(int content)
{
	t_node *node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = node;
	node->previous = node;
	return (new_node);
}

void	add_top(t_stack *s, t_node *node)
{
	if (!node)
		return ;
	if (s->size < 1)
	{
		s->top = node;
		return ;
	}
	node->previous = s->top->previous;
	node->next = s->top;
	s->top->previous->next = node;
	s->top->previous = node;
	s->top = node;
}

void	print_stack(char *name, t_stack *s)
{
	t_node	*node;
	size_t	i;

	printf("%s", name);
	node = s->top;
	i = 0;
	while (i < s->size)
	{
		printf("%d ", node->content);
		node = node->next;
		i++;
	}
	printf("|");
	node = s->top->previous;
	
}

int main()
{
	t_node *n1 = new_node(10);

}