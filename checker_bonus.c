/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 10:30:00 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/20 10:30:00 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static void	init_ctx(t_ctx *ctx, t_stack *a, t_stack *b)
{
	ft_bzero(a, sizeof(t_stack));
	ft_bzero(b, sizeof(t_stack));
	ft_bzero(ctx, sizeof(t_ctx));
	ctx->a = a;
	ctx->b = b;
}

static void	run_ops(t_ctx *ctx)
{
	char	line[8];
	int		status;
	int		op;

	status = read_line(line, 8);
	while (status == 1)
	{
		op = op_from_line(line);
		if (op < 0)
			error_exit(ctx);
		exec_op(ctx->a, ctx->b, op);
		status = read_line(line, 8);
	}
	if (status < 0)
		error_exit(ctx);
}

int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack	b;
	t_ctx	ctx;

	init_ctx(&ctx, &a, &b);
	if (argc < 2)
		return (0);
	if (!parse_args(argv, 1, &a))
		error_exit(&ctx);
	run_ops(&ctx);
	if (b.size == 0 && is_sorted(&a))
		ft_putendl_fd("OK", 1);
	else
		ft_putendl_fd("KO", 1);
	free_ctx(&ctx);
	return (0);
}
