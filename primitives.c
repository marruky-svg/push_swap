/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 08:47:49 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/20 11:58:51 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_node	*pop_top(t_stack *stack)
{
	t_node	*node;

	if (!stack || stack->size < 1)
		return (NULL);
	node = stack->top;
	if (stack->size < 2)
		stack->top = NULL;
	else
	{
		node->previous->next = node->next;
		node->next->previous = node->previous;
		stack->top = node->next;
	}
	stack->size--;
	return (node);
}

void	swap(t_stack *stack)
{
	t_node	*new_top;
	t_node	*top;

	if (!stack || stack->size < 2)
		return ;
	top = stack->top;
	new_top = top->next;
	if (stack->size > 2)
	{
		top->previous->next = new_top;
		new_top->next->previous = top;
		new_top->previous = top->previous;
		top->previous = new_top;
		top->next = new_top->next;
		new_top->next = top;
		stack->top = new_top;
	}
	stack->top = new_top;
}

void	push(t_stack *src, t_stack *dst)
{
	t_node	*src_top;

	if (!src || !dst || src->size < 1)
		return ;
	src_top = pop_top(src);
	if (dst->size < 1)
	{
		src_top->next = src_top;
		src_top->previous = src_top;
	}
	else
	{
		src_top->next = dst->top;
		src_top->previous = dst->top->previous;
		dst->top->previous->next = src_top;
		dst->top->previous = src_top;
	}
	dst->top = src_top;
	dst->size++;
}

void	rotate(t_stack *stack)
{
	if (!stack || stack->size < 2)
		return ;
	stack->top = stack->top->next;
}

void	rev_rotate(t_stack *stack)
{
	if (!stack || stack->size < 2)
		return ;
	stack->top = stack->top->previous;
}
