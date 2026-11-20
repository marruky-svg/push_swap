/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 18:44:38 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/20 10:30:00 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** free_ctx: liberta as duas pilhas e o buffer de operacoes.
*/
void	free_ctx(t_ctx *ctx)
{
	free_stack(ctx->a);
	free_stack(ctx->b);
	free(ctx->buf);
	ctx->buf = NULL;
	ctx->len = 0;
	ctx->cap = 0;
}

/*
** error_exit: saida padrao de erro do programa.
** Liberta tudo (evita leaks), escreve "Error\n" no stderr (fd 2),
** como pede o subject, e sai com codigo 1.
*/
void	error_exit(t_ctx *ctx)
{
	free_ctx(ctx);
	ft_putendl_fd("Error", 2);
	exit(1);
}
