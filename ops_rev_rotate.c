/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_rev_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 00:33:37 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/11 11:20:30 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_ctx *ctx)
{
	if (ctx->a->size < 2)
		return ;
	rev_rotate(ctx->a);
	record_op(ctx, OP_RRA);
}

void	rrb(t_ctx *ctx)
{
	if (ctx->b->size < 2)
		return ;
	rev_rotate(ctx->b);
	record_op(ctx, OP_RRB);
}

void	rrr(t_ctx *ctx)
{
	rev_rotate(ctx->a);
	rev_rotate(ctx-> b);
	record_op(ctx, OP_RRR);
}
