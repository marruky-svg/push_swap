/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilherme <guilherme@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:00:00 by gbaccell          #+#    #+#             */
/*   Updated: 2026/11/19 19:25:01 by guilherme        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*==================== ESTRATEGIA MEDIUM - O(n * sqrt(n)) ====================*/

/*
** Ideia (chunk sort): divide os indices 0..n-1 em ~sqrt(n) faixas
** (chunks). Manda para b um chunk de cada vez, depois devolve para a
** sempre o MAIOR de b. Precisa da pilha NORMALIZADA (index.c).
*/

/*
** chunk_size: retorna o tamanho de cada chunk, ~sqrt(n).
** Nao pode usar sqrt() da math.h (funcao externa nao permitida):
** calcule com um laco: r = 1; while ((r + 1) * (r + 1) <= n) r++;
** Ajustar com um fator (ex.: r * 2) para gastar menos operacoes,
** sem deixar de ser proporcional a sqrt(n).
*/
int	chunk_size(int n)
{
	int	r;

	r = 1;
	while ((r + 1) * (r + 1) <= n)
		r++;
	return (r * 2);
}

/*
** push_chunks: fase 1, manda tudo de a para b por faixas.
**   i = 0 (quantos ja foram para b), range = chunk_size(n)
**   enquanto a nao vazia:
**     top = ctx->a->top->content
**     - top <= i           -> pb; rb; i++   (pequeno: vai para o fundo de b)
**     - top <= i + range   -> pb; i++       (fica no topo de b)
**     - senao              -> ra            (ainda nao e a vez dele)
** Resultado: b fica "quase ordenada", com os maiores perto do topo.
*/
void	push_chunks(t_ctx *ctx, int range)
{
	int	i;
	int	top;

	i = 0;
	while (ctx->a->size > 0)
	{
		top = ctx->a->top->content;
		if (top <= i)
		{
			pb(ctx);
			rb(ctx);
			i++;
		}
		else if (top <= i + range)
		{
			pb(ctx);
			i++;
		}
		else
			ra(ctx);
	}
}

/*
** push_back_max: fase 2, devolve tudo para a.
**   enquanto b nao vazia:
**     bring_to_top_b(ctx, find_max_pos(ctx->b)); pa(ctx);
** Sempre devolvendo o maior, a termina ordenada.
*/
void	push_back_max(t_ctx *ctx)
{
	while (ctx->b->size > 0)
	{
		bring_to_top_b(ctx, find_max_pos(ctx->b));
		pa(ctx);
	}
}

/*
** sort_medium: push_chunks(ctx, chunk_size(ctx->a->size));
**              push_back_max(ctx);
**
** Complexidade (em operacoes):
**   fase 1: cada elemento custa no maximo ~range rotacoes -> O(n*sqrt(n))
**   fase 2: o maior de b esta a no maximo ~range do topo  -> O(n*sqrt(n))
**   Espaco: O(1) extra.
*/
void	sort_medium(t_ctx *ctx)
{
	push_chunks(ctx, chunk_size(ctx->a->size));
	push_back_max(ctx);
}
