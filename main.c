/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 11:07:31 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/16 18:43:54 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	init_ctx(t_ctx *ctx, t_stack *a, t_stack *b, t_cfg *cfg)
{
	ft_bzero(a, sizeof(t_stack));
	ft_bzero(b, sizeof(t_stack));
	ft_bzero(ctx, sizeof(t_ctx));
	ft_bzero(cfg, sizeof(t_cfg));
	ctx->a = a;
	ctx->b = b;
}

int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack	b;
	t_ctx	ctx;
	t_cfg	cfg;
	int		start;

	init_ctx(&ctx, &a, &b, &cfg);
	if (argc < 2)
		return (0);
	start = parse_flags(argv, &cfg);
	if (start == -1)
		error_exit(&ctx);
	if (!argv[start])
		return (0);
	if (!parse_args(argv, start, &a))
		error_exit(&ctx);
	free_stack(&a);
	free_stack(&b);
	return (0);
}