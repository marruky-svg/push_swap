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

/*====================== OPERACOES SWAP (sa / sb / ss) =======================*/

/* sa: troca os 2 primeiros de a. Nao faz nada se a < 2 elementos. */
void	sa(t_ctx *ctx)
{
	if (ctx->a->size < 2)
		return ;
	swap(ctx->a);
	record_op(ctx, OP_SA);
}

/* sb: troca os 2 primeiros de b. Nao faz nada se b < 2 elementos. */
void	sb(t_ctx *ctx)
{
	if (ctx->b->size < 2)
		return ;
	swap(ctx->b);
	record_op(ctx, OP_SB);
}

/*
** ss: sa e sb ao mesmo tempo. Imprime apenas "ss"
** (conta como UMA operacao).
*/
void	ss(t_ctx *ctx)
{
	swap(ctx->a);
	swap(ctx->b);
	record_op(ctx, OP_SS);
}

/*========================= OPERACOES PUSH (pa / pb) =========================*/

/* pa: tira o topo de b e coloca no topo de a. Nada se b vazia. */
void	pa(t_ctx *ctx)
{
	if (ctx->b->size < 1)
		return ;
	push(ctx->b, ctx->a);
	record_op(ctx, OP_PA);
}

/* pb: tira o topo de a e coloca no topo de b. Nada se a vazia. */
void	pb(t_ctx *ctx)
{
	if (ctx->a->size < 1)
		return ;
	push(ctx->a, ctx->b);
	record_op(ctx, OP_PB);
}
