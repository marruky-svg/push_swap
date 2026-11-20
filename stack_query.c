/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_query.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaccell <gbaccell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:00:00 by gbaccell          #+#    #+#             */
/*   Updated: 2026/11/18 14:43:25 by gbaccell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*=================== CONSULTAS NA PILHA (nao movem nada) ====================*/

/*
** Todas percorrem a lista circular com um contador ate s->size
** (nunca esperar NULL: a lista e circular).
** "pos" = distancia do topo: 0 e o topo, s->size - 1 e o fundo.
*/

/*
** is_sorted: retorna 1 se a pilha esta em ordem crescente do topo ao
** fundo (cada content < content do proximo), 0 caso contrario.
** Pilha vazia ou com 1 elemento esta ordenada.
*/
int	is_sorted(t_stack *s)
{
	t_node	*node;
	int		i;

	node = s->top;
	i = 0;
	while (i < s->size - 1)
	{
		if (node->content > node->next->content)
			return (0);
		node = node->next;
		i++;
	}
	return (1);
}
/*
** find_min_pos: retorna a pos do MENOR valor da pilha.
*/

int	find_min_pos(t_stack *s)
{
	t_node	*node;
	int		i;
	int		min;
	int		pos;

	node = s->top;
	i = 0;
	min = node->content;
	pos = i;
	while (i < s->size)
	{
		if (node->content < min)
		{
			min = node->content;
			pos = i;
		}
		node = node->next;
		i++;
	}
	return (pos);
}

/*
** find_max_pos: retorna a pos do MAIOR valor da pilha.
*/
int	find_max_pos(t_stack *s)
{
	t_node	*node;
	int		i;
	int		max;
	int		pos;

	node = s->top;
	i = 0;
	max = node->content;
	pos = i;
	while (i < s->size)
	{
		if (node->content > max)
		{
			max = node->content;
			pos = i;
		}
		node = node->next;
		i++;
	}
	return (pos);
}

/*
** get_max: retorna o MAIOR valor (content) da pilha.
** Util no radix para saber quantos bits sao necessarios.
*/
int	get_max(t_stack *s)
{
	t_node	*node;
	int		i;
	int		max;

	node = s->top;
	i = 0;
	max = node->content;
	while (i < s->size)
	{
		if (node->content > max)
			max = node->content;
		node = node->next;
		i++;
	}
	return (max);
}
