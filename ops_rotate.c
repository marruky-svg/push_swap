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

/*===================== OPERACOES ROTATE (ra / rb / rr) ======================*/

/* ra: desloca a para cima; o primeiro elemento vira o ultimo. */
void	ra(t_ctx *ctx)
{
	if (ctx->a->size < 2)
		return ;
	rotate(ctx->a);
	record_op(ctx, OP_RA);
}

/* rb: desloca b para cima; o primeiro elemento vira o ultimo. */
void	rb(t_ctx *ctx)
{
	if (ctx->b->size < 2)
		return ;
	rotate(ctx->b);
	record_op(ctx, OP_RB);
}

/*
** rr: ra e rb ao mesmo tempo. Imprime apenas "rr"
** (conta como UMA operacao).
*/
void	rr(t_ctx *ctx)
{
	rotate(ctx->a);
	rotate(ctx->b);
	record_op(ctx, OP_RR);
}
