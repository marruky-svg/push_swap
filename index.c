/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilherme <guilherme@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:00:00 by gbaccell          #+#    #+#             */
/*   Updated: 2026/11/19 19:25:42 by guilherme        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*================= NORMALIZACAO (valores -> indices 0..n-1) =================*/

/*
** Por que normalizar?
** O radix (complex) e os chunks (medium) ficam MUITO mais simples se os
** numeros forem 0, 1, 2, ..., n-1 em vez de valores quaisquer
** (negativos, gigantes, espacados). A ordem relativa nao muda, entao
** o resultado (as operacoes) e o mesmo.
** Ex.: [ 42, -7, 1000, 3 ]  ->  [ 2, 0, 3, 1 ]
** O disorder pode ser calculado antes ou depois: da o mesmo valor.
*/

/*
** stack_to_array: copia os valores da pilha (do topo ao fundo) para um
** array novo com malloc. Retorna NULL se o malloc falhar.
*/
int	*stack_to_array(t_stack *a)
{
	int		*arr;
	t_node	*node;
	int		i;

	arr = malloc(sizeof(int) * a->size);
	if (!arr)
		return (NULL);
	node = a->top;
	i = 0;
	while (i < a->size)
	{
		arr[i] = node->content;
		node = node->next;
		i++;
	}
	return (arr);
}

/*
** sort_array: ordena o array em ordem crescente.
** Pode ser um bubble/insertion sort simples: isso NAO conta como
** operacao do push_swap, e so preparacao interna.
*/
void	sort_array(int *arr, int size)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

/*
** normalize: troca o content de cada no pela sua POSICAO no array
** ordenado.
**   1. arr = stack_to_array(a); se NULL -> retorna 0
**   2. sort_array(arr, a->size);
**   3. para cada no da pilha (percorrer exatamente a->size nos):
**        procurar node->content em arr; o indice encontrado vira o
**        novo content
**   4. free(arr); retorna 1
*/
static int	find_index(int *arr, int size, int value)
{
	int	k;

	k = 0;
	while (k < size)
	{
		if (arr[k] == value)
			return (k);
		k++;
	}
	return (-1);
}

int	normalize(t_stack *a)
{
	int		*arr;
	t_node	*node;
	int		i;

	arr = stack_to_array(a);
	if (!arr)
		return (0);
	sort_array(arr, a->size);
	node = a->top;
	i = 0;
	while (i < a->size)
	{
		node->content = find_index(arr, a->size, node->content);
		node = node->next;
		i++;
	}
	free(arr);
	return (1);
}
