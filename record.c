/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 11:59:17 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/09 21:51:00 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	*op_name(t_ops op)
{
	char	*names[OP_SIZE];

	if (op >= OP_SIZE)
		return (NULL);
	names[OP_PA] = "pa";
	names[OP_PB] = "pb";
	names[OP_RA] = "ra";
	names[OP_RB] = "rb";
	names[OP_RR] = "rr";
	names[OP_RRA] = "rra";
	names[OP_RRB] = "rrb";
	names[OP_RRR] = "rrr";
	names[OP_SA] = "sa";
	names[OP_SB] = "sb";
	names[OP_SS] = "ss";
	return (names[op]);
}

void	record_op(t_ctx *ctx, t_ops op)
{
	char	*operation;

	operation = op_name(op);
	if (!operation)
	{
		ft_putendl_fd("record_op: invalid op", 2);
		return ;
	}
	ctx->ops_count[op]++;
	ft_putendl_fd(operation, 1);
}
