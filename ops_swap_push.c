/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_swap_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 12:31:38 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/10 19:10:16 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_ctx *ctx)
{
	if (ctx->a->size < 2)
		return ;
	swap(ctx->a);
	record_op(ctx, OP_SA);
}

void	sb(t_ctx *ctx)
{
	if (ctx->b->size < 2)
		return ;
	swap(ctx->b);
	record_op(ctx, OP_SB);
}

void	ss(t_ctx *ctx)
{
	swap(ctx->a);
	swap(ctx->b);
	record_op(ctx, OP_SS);
}

void	pa(t_ctx *ctx)
{
	if (ctx->b->size < 1)
		return ;
	push(ctx->b, ctx->a);
	record_op(ctx, OP_PA);
}

void	pb(t_ctx *ctx)
{
	if (ctx->a->size < 1)
		return ;
	push(ctx->a, ctx->b);
	record_op(ctx, OP_PB);
}
