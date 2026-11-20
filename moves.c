/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaccell <gbaccell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:00:00 by gbaccell          #+#    #+#             */
/*   Updated: 2026/11/18 13:16:43 by gbaccell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*========================== MOVIMENTOS AUXILIARES ===========================*/

/*
** bring_to_top_a: leva o elemento da posicao pos para o topo de a pelo
** caminho mais curto.
**   - pos <= a->size / 2 -> ra   'pos' vezes
**   - senao              -> rra  'a->size - pos' vezes
** Custo: no maximo size / 2 operacoes.
*/
void	bring_to_top_a(t_ctx *ctx, int pos)
{
	if (pos <= ctx->a->size / 2)
	{
		while (pos > 0)
		{
			ra(ctx);
			pos--;
		}
	}
	else
	{
		pos = ctx->a->size - pos;
		while (pos > 0)
		{
			rra(ctx);
			pos--;
		}
	}
}

/*
** bring_to_top_b: igual ao de cima, mas na pilha b (rb / rrb).
*/
void	bring_to_top_b(t_ctx *ctx, int pos)
{
	if (pos <= ctx->b->size / 2)
	{
		while (pos > 0)
		{
			rb(ctx);
			pos--;
		}
	}
	else
	{
		pos = ctx->b->size - pos;
		while (pos > 0)
		{
			rrb(ctx);
			pos--;
		}
	}
}
