/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dest_loc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 12:19:30 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/19 13:33:27 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_loc	dest_high(t_loc loc)
{
	if (loc == TOP_A)
		return (BOT_A);
	return (TOP_A);
}
t_loc	dest_mid(t_loc loc)
{
	if (loc == TOP_A || loc == BOT_A)
		return (TOP_B);
	return (BOT_A);
}
t_loc	dest_low(t_loc);
t_loc	normalize_loc(t_ctx *ctx, t_loc loc, int k);