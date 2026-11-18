/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:48:44 by marvin            #+#    #+#             */
/*   Updated: 2026/11/17 15:48:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_algo	choose_algo(t_cfg *cfg, double d, int size)
{
	if (cfg->strat == STRAT_SIMPLE)
		return (ALGO_TURK);
	else if (cfg->strat == STRAT_MEDIUM)
		return (ALGO_CHUNKS);
	else if (cfg->strat == STRAT_COMPLEX)
		return (ALGO_QUICK);
	if (size <= 5)
		return (ALGO_SMALL);
	if (d < 0.2)
		return (ALGO_TURK);
	return (ALGO_QUICK);
}

static void		run_algo(t_ctx *ctx, t_algo algo);

void	dispatch(t_ctx *ctx, t_cfg *cfg)
{
	double	d;

	d = disorder(ctx->a);
	if (d > 0.0)
	{
		
	}
}