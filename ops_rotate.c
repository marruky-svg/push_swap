/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 23:42:17 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/11 17:55:23 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_ctx *ctx)
{
	if (ctx->a->size < 2)
		return ;
	rotate(ctx->a);
	record_op(ctx, OP_RA);
}

void	rb(t_ctx *ctx)
{
	if (ctx->b->size < 2)
		return ;
	rotate(ctx->b);
	record_op(ctx, OP_RB);
}

void	rr(t_ctx *ctx)
{
	rotate(ctx->a);
	rotate(ctx->b);
	record_op(ctx, OP_RR);
}
