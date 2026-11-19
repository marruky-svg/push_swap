/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_loc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 06:18:54 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/19 07:08:06 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_loc	to_top(t_ctx *ctx, t_loc src)
{
	if (src == BOT_A)
	{
		rra(ctx);
		return (TOP_A);
	}
	if (src == BOT_B)
	{
		rrb(ctx);
		return (TOP_B);
	}
	return (src);
}

static void	from_top(t_ctx *ctx, t_loc top, t_loc dst)
{
	if (top == TOP_A)
	{
		if (dst == BOT_A)
			ra(ctx);
		else if (dst == TOP_B)
			pb(ctx);
		else if (dst == BOT_B)
		{
			pb(ctx);
			rb(ctx);
		}
	}
	else if (top == TOP_B)
	{
		if (dst == BOT_B)
			rb(ctx);
		else if (dst == TOP_A)
			pa(ctx);
		else if (dst == BOT_A)
		{
			pa(ctx);
			ra(ctx);
		}
	}
}

void	move(t_ctx *ctx, t_loc src, t_loc dst)
{
	t_loc	top;

	if (src == dst)
		return ;
	top = to_top(ctx, src);
	from_top(ctx, top, dst);
}

int	local_rank(t_ctx *ctx, t_loc loc)
{
	if (loc == TOP_A)
		return (ctx->a->top->rank);
	if (loc == BOT_A)
		return (ctx->a->top->previous->rank);
	if (loc == TOP_B)
		return (ctx->b->top->rank);
	return (ctx->b->top->previous->rank);
}
