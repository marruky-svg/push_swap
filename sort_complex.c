/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:00:00 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/20 10:30:00 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*============ ESTRATEGIA COMPLEX - O(n log n): QUICKSORT DE 3 VIAS =========*/

/*
** Um segmento = valores consecutivos (lo .. lo + k - 1), juntos numa das
** quatro pontas (topo/fundo de a/b). Como a pilha esta NORMALIZADA, os
** limites dos tercos saem de contas, sem procurar: o pivo e sempre exato.
*/

/*
** partition: manda cada elemento do segmento para a ponta do seu terco.
**   p1 = lo + k / 3        p2 = lo + 2 * k / 3
**   valor >= p2 -> dest_high | >= p1 -> dest_mid | senao -> dest_low
** Le sempre a mesma ponta (loc): cada move tira o elemento de la.
*/
static void	partition(t_ctx *ctx, t_loc loc, int lo, int k)
{
	int	p1;
	int	p2;
	int	r;
	int	i;

	p1 = lo + k / 3;
	p2 = lo + 2 * k / 3;
	i = 0;
	while (i < k)
	{
		r = local_rank(ctx, loc);
		if (r >= p2)
			move(ctx, loc, dest_high(loc));
		else if (r >= p1)
			move(ctx, loc, dest_mid(loc));
		else
			move(ctx, loc, dest_low(loc));
		i++;
	}
}

/*
** quick_rec: ordena o segmento (loc, lo, k), terminando no topo de a.
** Ordem das chamadas: superior, meio, inferior -> cada terco fica
** ordenado POR CIMA do anterior.
** Complexidade: cada nivel move cada elemento uma vez (<= 3 ops) e
** divide o tamanho por 3 -> cerca de log3(n) niveis -> O(n log n).
*/
static void	quick_rec(t_ctx *ctx, t_loc loc, int lo, int k)
{
	int	p1;
	int	p2;

	if (k <= 0)
		return ;
	loc = normalize_loc(ctx, loc, k);
	if (k <= 3)
	{
		quick_base(ctx, loc, k);
		return ;
	}
	partition(ctx, loc, lo, k);
	p1 = lo + k / 3;
	p2 = lo + 2 * k / 3;
	quick_rec(ctx, dest_high(loc), p2, lo + k - p2);
	quick_rec(ctx, dest_mid(loc), p1, p2 - p1);
	quick_rec(ctx, dest_low(loc), lo, p1 - lo);
}

/*
** sort_complex: o segmento inicial e a pilha a inteira (0 .. n - 1).
*/
void	sort_complex(t_ctx *ctx)
{
	quick_rec(ctx, TOP_A, 0, ctx->a->size);
}
