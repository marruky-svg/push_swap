/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dest_loc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 12:19:30 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/20 10:30:00 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*================ DESTINOS DOS TERCOS E NORMALIZACAO =======================*/

/*
** dest_high: terco superior -> topo de a (ou fundo de a, se ja la esta).
*/
t_loc	dest_high(t_loc loc)
{
	if (loc == TOP_A)
		return (BOT_A);
	return (TOP_A);
}

/*
** dest_mid: terco do meio -> topo de b (se veio de a) ou fundo de a.
*/
t_loc	dest_mid(t_loc loc)
{
	if (loc == TOP_A || loc == BOT_A)
		return (TOP_B);
	return (BOT_A);
}

/*
** dest_low: terco inferior -> fundo de b (ou topo de b, se ja la esta).
*/
t_loc	dest_low(t_loc loc)
{
	if (loc == BOT_B)
		return (TOP_B);
	return (BOT_B);
}

/*
** normalize_loc: um segmento num fundo que ocupa a pilha INTEIRA e
** tratado como estando no topo (poupa um rra/rrb por elemento).
*/
t_loc	normalize_loc(t_ctx *ctx, t_loc loc, int k)
{
	if (loc == BOT_A && ctx->a->size == k)
		return (TOP_A);
	if (loc == BOT_B && ctx->b->size == k)
		return (TOP_B);
	return (loc);
}
