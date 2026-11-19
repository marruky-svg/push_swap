/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 03:17:49 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/19 03:17:49 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_algo	choose_algo(t_cfg *cfg, double d, int size)
{
	if (cfg->strat == STRAT_SIMPLE)
		return (ALGO_TURK);
	if (cfg->strat == STRAT_MEDIUM)
		return (ALGO_CHUNKS);
	if (cfg->strat == STRAT_COMPLEX)
		return (ALGO_QUICK);
	if (size <= 5)
		return (ALGO_SMALL);
	if (d < 0.2)
		return (ALGO_TURK);
	return (ALGO_QUICK);
}

static void	run_algo(t_ctx *ctx, t_algo algo)
{
	if (algo == ALGO_SMALL)
		sort_small(ctx);
	else if (algo == ALGO_TURK)
		sort_turk(ctx);
	else if (algo == ALGO_CHUNKS)
		sort_chunks(ctx);
	else
		sort_quick(ctx);
}

void	dispatch(t_ctx *ctx, t_cfg *cfg)
{
	double	d;

	d = disorder(ctx->a);
	if (d > 0.0)
		run_algo(ctx, choose_algo(cfg, d, ctx->a->size));
	if (cfg->bench)
		print_bench(ctx, cfg, d);
}
