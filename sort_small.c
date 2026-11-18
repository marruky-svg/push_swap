/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42.fr>              +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 11:11:10 by marvin            #+#    #+#             */
/*   Updated: 2026/11/17 11:11:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_min_pos(t_stack *stack)
{
	t_node	*node;
	int		min_val;
	int		min_pos;
	int		i;

	if (!stack || !stack->top || stack->size <= 0)
		return (-1);
	node = stack->top;
	min_val = node->content;
	min_pos = 0;
	i = 0;
	while (i < stack->size)
	{
		if (node->content < min_val)
		{
			min_val = node->content;
			min_pos = i;
		}
		node = node->next;
		i++;
	}
	return (min_pos);
}

static void	sort_two(t_ctx *ctx)
{
	if (ctx->a->top->content > ctx->a->top->next->content)
		sa(ctx);
}

static void	sort_three(t_ctx *ctx)
{
	t_stack	*a;

	a = ctx->a;
	if (a->top->content > a->top->next->content && a->top->content > a->top->previous->content)
		ra(ctx);
	else if (a->top->next->content > a->top->previous->content && a->top->next->content > a->top->content)
		rra(ctx);
	if (a->top->content > a->top->next->content)
		sa(ctx);
}

static void	bring_to_top(t_ctx *ctx, int pos)
{
	int	i;

	i = 0;
	if (pos <= ctx->a->size / 2)
	{
		while (i++ < pos)
			ra(ctx);
	}
	else
	{
		while (i++ < ctx->a->size - pos)
			rra(ctx);
	}
}

void	sort_small(t_ctx *ctx)
{
	t_stack	*a;
	int		min_pos;
	
	a = ctx->a;
	while (a->size > 3)
	{
		min_pos = find_min_pos(a);
		bring_to_top(ctx, min_pos);
		pb(ctx);
	}
	if (a->size == 2)
		sort_two(ctx);
	else
		sort_three(ctx);
	while (ctx->b->size)
		pa(ctx);
}
