/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 16:59:40 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/11 17:53:31 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	count_mistake(t_node *node, double *total_pairs,
	int start, int size)
{
	t_node	*n;
	t_node	*nt;
	int		mistake;

	mistake = 0;
	n = node;
	nt = node->next;
	while (start < size)
	{
		if (n->content > nt->content)
			mistake++;
		start++;
		nt = nt->next;
		(*total_pairs)++;
	}
	return (mistake);
}

double	disorder(t_stack *a)
{
	double		mistakes;
	double		total_pairs;
	int			i;
	t_node		*node;

	if (a->size < 2)
		return (0);
	i = 0;
	mistakes = 0;
	total_pairs = 0;
	node = a->top;
	while (i < a->size - 1)
	{
		mistakes += count_mistake(node, &total_pairs, i + 1, a->size);
		i++;
		node = node->next;
	}
	return (mistakes / total_pairs);
}
