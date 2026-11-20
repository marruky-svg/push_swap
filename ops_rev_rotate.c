/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_rev_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 00:33:37 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/20 10:30:00 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*================ OPERACOES REVERSE ROTATE (rra / rrb / rrr) ================*/

/* rra: desloca a para baixo; o ultimo elemento vira o primeiro. */
void	rra(t_ctx *ctx)
{
	if (ctx->a->size < 2)
		return ;
	rev_rotate(ctx->a);
	record_op(ctx, OP_RRA);
}

/* rrb: desloca b para baixo; o ultimo elemento vira o primeiro. */
void	rrb(t_ctx *ctx)
{
	if (ctx->b->size < 2)
		return ;
	rev_rotate(ctx->b);
	record_op(ctx, OP_RRB);
}

/*
** rrr: rra e rrb ao mesmo tempo. Imprime apenas "rrr"
** (conta como UMA operacao).
*/
void	rrr(t_ctx *ctx)
{
	rev_rotate(ctx->a);
	rev_rotate(ctx->b);
	record_op(ctx, OP_RRR);
}
