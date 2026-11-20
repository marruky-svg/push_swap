/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 10:30:00 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/20 10:30:00 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

int	read_line(char *line, int max)
{
	int		len;
	char	c;
	int		got;

	len = 0;
	got = read(0, &c, 1);
	while (got == 1 && c != '\n')
	{
		if (len < max)
			line[len] = c;
		len++;
		got = read(0, &c, 1);
	}
	if (got < 0 || (got == 0 && len > 0) || len >= max)
		return (-1);
	line[len] = '\0';
	if (got == 0)
		return (0);
	return (1);
}

int	op_from_line(char *line)
{
	int	op;

	op = 0;
	while (op < OP_SIZE)
	{
		if (!ft_strncmp(line, op_name(op), ft_strlen(op_name(op)) + 1))
			return (op);
		op++;
	}
	return (-1);
}

static void	exec_swap_push(t_stack *a, t_stack *b, int op)
{
	if (op == OP_SA || op == OP_SS)
		swap(a);
	if (op == OP_SB || op == OP_SS)
		swap(b);
	if (op == OP_PA)
		push(b, a);
	if (op == OP_PB)
		push(a, b);
}

void	exec_op(t_stack *a, t_stack *b, int op)
{
	exec_swap_push(a, b, op);
	if (op == OP_RA || op == OP_RR)
		rotate(a);
	if (op == OP_RB || op == OP_RR)
		rotate(b);
	if (op == OP_RRA || op == OP_RRR)
		rev_rotate(a);
	if (op == OP_RRB || op == OP_RRR)
		rev_rotate(b);
}
