/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 15:40:00 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/20 15:40:00 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*===================== ESTRATEGIA SIMPLE - O(n^2) (Turk) ====================*/

/*
** Insercao pelo menor custo ("Turk"):
**   1. passa 2 elementos para b (b passa a ter um maximo e um minimo)
**   2. enquanto a tem mais de 3: escolhe o elemento de a que custa menos
**      rotacoes a inserir no sitio certo de b (b fica em ordem
**      DECRESCENTE), roda as duas pilhas e faz pb
**   3. sort_three nos 3 que sobram em a
**   4. devolve cada topo de b para o sitio certo de a (pa)
**   5. roda a ate o menor ficar no topo
** Complexidade: n insercoes x n candidatos avaliados = O(n^2) avaliacoes;
** em operacoes, cada insercao custa no maximo n rotacoes -> O(n^2).
** Com pouca desordem, quase todos os elementos ja estao perto do sitio
** certo, por isso o custo de cada insercao e pequeno.
*/

/*
** cheapest: percorre a inteira e devolve as rotacoes (t_rot) do
** elemento mais barato de inserir em b.
*/
static t_rot	cheapest(t_ctx *ctx)
{
	t_node	*node;
	t_rot	best;
	t_rot	cur;
	int		i;

	node = ctx->a->top;
	best = best_rot(0, ctx->a->size,
			target_in_b(ctx->b, node->content), ctx->b->size);
	node = node->next;
	i = 1;
	while (i < ctx->a->size)
	{
		cur = best_rot(i, ctx->a->size,
				target_in_b(ctx->b, node->content), ctx->b->size);
		if (rot_cost(cur) < rot_cost(best))
			best = cur;
		node = node->next;
		i++;
	}
	return (best);
}

/*
** push_back: devolve os elementos de b, um a um, para a posicao certa
** de a (o menor elemento de a maior do que o topo de b).
*/
static void	push_back(t_ctx *ctx)
{
	while (ctx->b->size > 0)
	{
		bring_to_top_a(ctx, target_in_a(ctx->a, ctx->b->top->content));
		pa(ctx);
	}
}

void	sort_simple(t_ctx *ctx)
{
	if (ctx->a->size <= 5)
	{
		sort_small(ctx);
		return ;
	}
	while (ctx->a->size > 3 && ctx->b->size < 2)
		pb(ctx);
	while (ctx->a->size > 3)
	{
		apply_rot(ctx, cheapest(ctx));
		pb(ctx);
	}
	sort_three(ctx);
	push_back(ctx);
	bring_to_top_a(ctx, find_min_pos(ctx->a));
}
