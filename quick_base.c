/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 10:30:00 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/20 10:30:00 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*================= CASO BASE DO QUICKSORT (ate 3 elementos) ================*/

/*
** sort_top_three: ordena os 3 do topo de a SEM mexer no resto da pilha.
** E um bubble sort de 3: troca 1-2, troca 2-3 (pb sa pa), troca 1-2.
** No maximo 5 operacoes; sequencias otimas (pesquisa exaustiva).
*/
static void	sort_top_three(t_ctx *ctx)
{
	if (ctx->a->top->content > ctx->a->top->next->content)
		sa(ctx);
	if (ctx->a->top->next->content > ctx->a->top->next->next->content)
	{
		pb(ctx);
		sa(ctx);
		pa(ctx);
	}
	if (ctx->a->top->content > ctx->a->top->next->content)
		sa(ctx);
}

/*
** quick_base: traz os k elementos (k <= 3) ao topo de a e ordena-os.
** Se a pilha a tem so esses 3, usa o sort_three (no maximo 2 ops).
*/
void	quick_base(t_ctx *ctx, t_loc loc, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		move(ctx, loc, TOP_A);
		i++;
	}
	if (k == 2 && ctx->a->top->content > ctx->a->top->next->content)
		sa(ctx);
	else if (k == 3 && ctx->a->size == 3)
		sort_three(ctx);
	else if (k == 3)
		sort_top_three(ctx);
}
