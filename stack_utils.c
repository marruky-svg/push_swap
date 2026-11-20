/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaccell <gbaccell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 13:10:47 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/17 16:11:41 by gbaccell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** new_node: aloca um novo no com o valor dado.
** O no nasce apontando para si mesmo (lista circular de 1).
** Retorna NULL se o malloc falhar.
*/
t_node	*new_node(int value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->content = value;
	node->next = node;
	node->previous = node;
	return (node);
}

/*
** add_bottom: cria um no e coloca no FUNDO da pilha.
** Usada no parsing para manter a ordem dos argumentos:
** o primeiro numero digitado fica no topo da pilha a.
**   - pilha vazia -> o no vira o topo
**   - senao       -> insere entre o ultimo (top->previous) e o topo
** Retorna 1 se ok, 0 se o malloc falhar.
*/
int	add_bottom(t_stack *stack, int value)
{
	t_node	*node;
	t_node	*last;
	t_node	*top;

	node = new_node(value);
	if (!node)
		return (0);
	if (stack->size == 0)
		stack->top = node;
	else
	{
		top = stack->top;
		last = stack->top->previous;
		last->next = node;
		node->previous = last;
		node->next = top;
		top->previous = node;
	}
	stack->size++;
	return (1);
}

/*
** has_value: procura value na pilha.
** Percorre exatamente size nos (a lista e circular, nao tem NULL).
** Retorna 1 se encontrou (numero duplicado), 0 caso contrario.
*/
int	has_value(t_stack *stack, int value)
{
	int		size;
	t_node	*node;

	node = stack->top;
	size = 0;
	while (size < stack->size)
	{
		if (value == node->content)
			return (1);
		node = node->next;
		size++;
	}
	return (0);
}

/*
** free_stack: libera todos os nos da pilha e a deixa vazia
** (top = NULL, size = 0). Seguro de chamar em pilha vazia.
*/
void	free_stack(t_stack *stack)
{
	int		size;
	t_node	*node;
	t_node	*next;

	size = 0;
	node = stack->top;
	while (size < stack->size)
	{
		next = node->next;
		free(node);
		node = next;
		size++;
	}
	stack->top = NULL;
	stack->size = 0;
}
