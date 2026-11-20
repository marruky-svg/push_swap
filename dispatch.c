/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:00:00 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/20 15:40:00 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*======================= FLUXO PRINCIPAL DA ORDENACAO =======================*/

/*
** resolve_strat: converte a estrategia PEDIDA na estrategia REAL usada.
**   - strat != STRAT_ADAPTIVE -> retorna strat (flag forcada pelo usuario)
**   - strat == STRAT_ADAPTIVE -> decide pelo disorder (limites do subject):
**       disorder <  0.2          -> STRAT_SIMPLE   O(n^2)
**       0.2 <= disorder < 0.5    -> STRAT_MEDIUM   O(n * sqrt(n))
**       disorder >= 0.5          -> STRAT_COMPLEX  O(n log n)
** Obs.: o simple e o Turk (insercao pelo menor custo). Com pouca
** desordem cada elemento ja esta perto do sitio certo, por isso cada
** insercao custa poucas rotacoes. (A extracao do minimo NAO tinha esta
** propriedade: chegava a 21000 operacoes com 500 numeros e 15%.)
*/
t_strat	resolve_strat(t_strat strat, double dis)
{
	if (strat != STRAT_ADAPTIVE)
		return (strat);
	if (dis < 0.2)
		return (STRAT_SIMPLE);
	if (dis < 0.5)
		return (STRAT_MEDIUM);
	return (STRAT_COMPLEX);
}

/*
** sort_with: chama o algoritmo correspondente a estrategia REAL.
**   - a->size <= 5 -> sort_small(ctx)   (casos pequenos, poucas operacoes)
**   - STRAT_SIMPLE  -> sort_simple(ctx)
**   - STRAT_MEDIUM  -> sort_medium(ctx)
**   - STRAT_COMPLEX -> sort_complex(ctx)
** Norm: switch e proibido, usar if / else if.
** Decidam (e expliquem no README) se o sort_small vale para todas as
** estrategias ou so para a adaptive.
*/
void	sort_with(t_ctx *ctx, t_strat strat)
{
	if (ctx->a->size <= 5)
		sort_small(ctx);
	else if (strat == STRAT_SIMPLE)
		sort_simple(ctx);
	else if (strat == STRAT_MEDIUM)
		sort_medium(ctx);
	else
		sort_complex(ctx);
}

/*
** run_push_swap: tudo o que acontece DEPOIS do parsing.
** Chamada pelo main logo depois do parse_args (assim o main nao passa
** do limite de 5 variaveis da Norm).
**   1. dis = disorder(ctx->a);          ANTES de qualquer movimento
**   2. used = resolve_strat(cfg->strat, dis);
**   3. se a pilha nao esta ordenada (is_sorted):
**        a. normalize(ctx->a); se falhar (malloc) -> error_exit(ctx)
**        b. sort_with(ctx, used);
**        c. flush_ops(ctx): otimiza, imprime e conta as operacoes
**      se ja esta ordenada nao imprime NENHUMA operacao
**   4. se cfg->bench -> print_bench(ctx, cfg->strat, used, dis);
**      (o bench aparece mesmo com a pilha ja ordenada: 0 operacoes)
*/
void	run_push_swap(t_ctx *ctx, t_cfg *cfg)
{
	double	dis;
	t_strat	used;

	dis = disorder(ctx->a);
	used = resolve_strat(cfg->strat, dis);
	if (!is_sorted(ctx->a))
	{
		if (!normalize(ctx->a))
			error_exit(ctx);
		sort_with(ctx, used);
		if (ctx->alloc_failed)
			error_exit(ctx);
		flush_ops(ctx);
	}
	if (cfg->bench)
		print_bench(ctx, cfg->strat, used, dis);
}
