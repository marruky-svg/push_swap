/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaccell <gbaccell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:00:00 by gbaccell          #+#    #+#             */
/*   Updated: 2026/11/18 14:42:58 by gbaccell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*===================== CASOS PEQUENOS (2 a 5 elementos) =====================*/

/*
** Notacao: [x y z] = topo, segundo, terceiro (valores ja normalizados).
*/

/*
** sort_two: se o topo > segundo -> sa. (no maximo 1 operacao)
*/
void	sort_two(t_ctx *ctx)
{
	if (ctx->a->top->content > ctx->a->top->next->content)
		sa(ctx);
}

/*
** sort_three: ordena 3 elementos com no maximo 2 operacoes.
**   1. se o MAIOR esta no topo    -> ra
**      se o MAIOR esta no meio    -> rra
**      (agora o maior esta no fundo)
**   2. se topo > segundo          -> sa
** Os 6 casos possiveis:
**   [0 1 2] nada    [0 2 1] rra sa   [1 0 2] sa
**   [1 2 0] rra     [2 0 1] ra       [2 1 0] ra sa
*/
void	sort_three(t_ctx *ctx)
{
	int	max;

	max = find_max_pos(ctx->a);
	if (max == 0)
		ra(ctx);
	else if (max == 1)
		rra(ctx);
	if (ctx->a->top->content > ctx->a->top->next->content)
		sa(ctx);
}

/*
** sort_five: ordena 4 ou 5 elementos.
**   1. enquanto a->size > 3:
**        bring_to_top_a(ctx, find_min_pos(ctx->a)); pb(ctx);
**   2. sort_three(ctx);
**   3. enquanto b nao estiver vazia -> pa(ctx);
** Como os menores foram para b em ordem, voltam na ordem certa.
*/
void	sort_five(t_ctx *ctx)
{
	while (ctx->a->size > 3)
	{
		bring_to_top_a(ctx, find_min_pos(ctx->a));
		pb(ctx);
	}
	sort_three(ctx);
	while (ctx->b->size > 0)
		pa(ctx);
}

/*
** sort_small: escolhe pelo tamanho:
**   size 2 -> sort_two | size 3 -> sort_three | size 4 ou 5 -> sort_five
*/
void	sort_small(t_ctx *ctx)
{
	if (ctx->a->size == 2)
		sort_two(ctx);
	else if (ctx->a->size == 3)
		sort_three(ctx);
	else
		sort_five(ctx);
}
