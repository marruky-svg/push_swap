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

/*
** count_mistake: laco INTERNO do pseudocodigo do subject.
** Recebe o no da posicao i e compara com todos os nos seguintes
** (posicoes j = i + 1 ate size - 1):
**   - n  -> no fixo (a[i])
**   - nt -> no que avanca (a[j])
** Cada par visitado soma 1 em total_pairs; cada par onde
** a[i] > a[j] (par invertido) conta como um erro (mistake).
** Retorna o numero de erros encontrados para esse i.
*/
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

/*
** disorder: calcula o quanto a pilha a esta fora de ordem.
** Retorna um valor entre 0 e 1:
**   0   -> ja ordenada
**   1   -> totalmente invertida
**   0.x -> parcialmente ordenada
** Formula: pares_invertidos / total_de_pares.
** Laco EXTERNO: percorre i de 0 ate size - 2 e chama count_mistake.
** Pilha com menos de 2 elementos e considerada ordenada (0).
** IMPORTANTE: deve ser chamada ANTES de qualquer movimento.
*/
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
