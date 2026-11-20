/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_rot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 15:40:00 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/20 15:40:00 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*===================== TURK: CUSTO E EXECUCAO DAS ROTACOES ==================*/

/*
** t_rot guarda quantas rotacoes fazer em cada pilha:
**   > 0 -> ra / rb  esse numero de vezes
**   < 0 -> rra / rrb  (-valor) vezes
** Quando a e b rodam no MESMO sentido, as rotacoes partilhadas viram
** rr / rrr: o custo e o maior dos dois, nao a soma.
*/

/*
** rot_cost: numero de operacoes que um t_rot vai gerar.
*/
int	rot_cost(t_rot r)
{
	int	x;
	int	y;

	x = r.a;
	y = r.b;
	if (x < 0)
		x = -x;
	if (y < 0)
		y = -y;
	if ((r.a >= 0 && r.b >= 0) || (r.a <= 0 && r.b <= 0))
	{
		if (x > y)
			return (x);
		return (y);
	}
	return (x + y);
}

/*
** best_rot: para o elemento na posicao pos_a de a e o alvo pos_b em b,
** testa as 4 combinacoes (cima/baixo em cada pilha) e devolve a mais
** barata.
*/
t_rot	best_rot(int pos_a, int size_a, int pos_b, int size_b)
{
	t_rot	opt[4];
	t_rot	best;
	int		i;

	opt[0].a = pos_a;
	opt[0].b = pos_b;
	opt[1].a = pos_a - size_a;
	opt[1].b = pos_b - size_b;
	opt[2].a = pos_a;
	opt[2].b = pos_b - size_b;
	opt[3].a = pos_a - size_a;
	opt[3].b = pos_b;
	best = opt[0];
	i = 1;
	while (i < 4)
	{
		if (rot_cost(opt[i]) < rot_cost(best))
			best = opt[i];
		i++;
	}
	return (best);
}

static void	rot_both(t_ctx *ctx, t_rot *r)
{
	while (r->a > 0 && r->b > 0)
	{
		rr(ctx);
		r->a--;
		r->b--;
	}
	while (r->a < 0 && r->b < 0)
	{
		rrr(ctx);
		r->a++;
		r->b++;
	}
}

/*
** apply_rot: executa as rotacoes (primeiro as partilhadas, depois o resto).
*/
void	apply_rot(t_ctx *ctx, t_rot r)
{
	rot_both(ctx, &r);
	while (r.a > 0)
	{
		ra(ctx);
		r.a--;
	}
	while (r.a < 0)
	{
		rra(ctx);
		r.a++;
	}
	while (r.b > 0)
	{
		rb(ctx);
		r.b--;
	}
	while (r.b < 0)
	{
		rrb(ctx);
		r.b++;
	}
}
