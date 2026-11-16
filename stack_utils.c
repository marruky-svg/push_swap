/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 13:10:47 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/16 11:35:33 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*new_node(int value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->content = value;
	node->next = node;
	node->previous = node;
	return (node);
}

int	add_bottom(t_stack *stack, int value)
{
	t_node	*node;
	t_node	*last;
	t_node	*top;

	node = new_node(value);
	if (!node)
		return (0);
	if (stack->size == 0)
		stack->top = node;
	else
	{
		top = stack->top;
		last = stack->top->previous;
		last->next = node;
		node->previous = last;
		node->next = top;
		top->previous = node;
	}
	stack->size++;
	return (1);
}

int	has_value(t_stack *stack, int value)
{
	int	size;
	t_node	*node;

	node = stack->top;
	size = 0;
	while (size < stack->size)
	{
		if (value == node->content)
			return (1);
		node = node->next;
		size++;
	}
	return (0);
}

void	free_stack(t_stack *stack)
{
	int	size;
	t_node	*node;
	t_node	*next;

	size = 0;
	node = stack->top;
	while (size < stack->size)
	{
		next = node->next;
		free(node);
		node = next;
		size++;
	}
	stack->top = NULL;
	stack->size = 0;
}
