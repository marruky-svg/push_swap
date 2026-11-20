/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_target.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 15:40:00 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/20 15:40:00 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*==================== TURK: ONDE INSERIR (posicoes alvo) ====================*/

/*
** Todas assumem valores normalizados (0 .. n-1, sem repetidos).
*/

/*
** find_value_pos: posicao (0 = topo) do valor v na pilha, ou -1.
*/
static int	find_value_pos(t_stack *s, int v)
{
	t_node	*node;
	int		i;

	node = s->top;
	i = 0;
	while (i < s->size)
	{
		if (node->content == v)
			return (i);
		node = node->next;
		i++;
	}
	return (-1);
}

/*
** target_in_b: b esta em ordem decrescente. O valor v deve ficar logo
** acima do MAIOR valor de b que seja menor do que v. Se nao houver
** nenhum menor, v e o novo minimo: fica acima do maximo de b (que e
** onde a ordem decrescente "da a volta").
** Devolve a posicao que tem de chegar ao topo de b antes do pb.
*/
int	target_in_b(t_stack *b, int v)
{
	t_node	*node;
	int		best;
	int		i;

	node = b->top;
	best = -1;
	i = 0;
	while (i < b->size)
	{
		if (node->content < v && node->content > best)
			best = node->content;
		node = node->next;
		i++;
	}
	if (best == -1)
		return (find_max_pos(b));
	return (find_value_pos(b, best));
}

/*
** target_in_a: a esta em ordem crescente (rodada). O valor v deve
** ficar logo acima do MENOR valor de a que seja maior do que v. Se nao
** houver nenhum maior, v e o novo maximo: fica acima do minimo de a.
*/
int	target_in_a(t_stack *a, int v)
{
	t_node	*node;
	int		best;
	int		i;

	node = a->top;
	best = INT_MAX;
	i = 0;
	while (i < a->size)
	{
		if (node->content > v && node->content < best)
			best = node->content;
		node = node->next;
		i++;
	}
	if (best == INT_MAX)
		return (find_min_pos(a));
	return (find_value_pos(a, best));
}
