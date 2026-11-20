/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilherme <guilherme@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:00:00 by gbaccell          #+#    #+#             */
/*   Updated: 2026/11/19 19:24:41 by guilherme        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*=================== MODO --bench (saida no stderr, fd 2) ===================*/

/*
** Tudo aqui escreve no fd 2 (ft_putstr_fd / ft_putnbr_fd).
** printf nao e permitido (so um ft_printf feito por voces).
** Exemplo de saida (o formato exato e livre):
**   [bench] disorder: 49.93%
**   [bench] strategy: Adaptive / O(n log n)
**   [bench] total_ops: 6784
**   [bench] sa: 0 sb: 0 ss: 0 pa: 3392 pb: 3392
**   [bench] ra: 0 rb: 0 rr: 0 rra: 0 rrb: 0 rrr: 0
*/

/*
** strat_name: "Simple", "Medium", "Complex" ou "Adaptive".
*/
char	*strat_name(t_strat strat)
{
	if (strat == STRAT_SIMPLE)
		return ("Simple");
	if (strat == STRAT_MEDIUM)
		return ("Medium");
	if (strat == STRAT_COMPLEX)
		return ("Complex");
	return ("Adaptive");
}

/*
** strat_complexity: "O(n^2)", "O(n*sqrt(n))" ou "O(n log n)".
** Para a adaptive, usar a complexidade da estrategia REAL escolhida.
*/
char	*strat_complexity(t_strat strat)
{
	if (strat == STRAT_SIMPLE)
		return ("O(n^2)");
	if (strat == STRAT_MEDIUM)
		return ("O(n*sqrt(n))");
	return ("O(n log n)");
}

/*
** total_ops: soma ctx->ops_count[0] ate ctx->ops_count[OP_SIZE - 1].
*/
int	total_ops(t_ctx *ctx)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (i < OP_SIZE)
	{
		total += ctx->ops_count[i];
		i++;
	}
	return (total);
}

/*
** put_percent_fd: imprime dis (0..1) como porcentagem com 2 casas.
**   1. v = (int)(dis * 10000 + 0.5);   ex.: 0.49934 -> 4993
**   2. imprime v / 100       -> "49"
**   3. imprime '.'
**   4. se v % 100 < 10 imprime '0' antes (ex.: 5.07 e nao 5.7)
**   5. imprime v % 100 e depois '%'
*/
void	put_percent_fd(double dis, int fd)
{
	int	v;

	v = (int)(dis * 10000 + 0.5);
	ft_putnbr_fd(v / 100, fd);
	ft_putchar_fd('.', fd);
	if (v % 100 < 10)
		ft_putchar_fd('0', fd);
	ft_putnbr_fd(v % 100, fd);
	ft_putchar_fd('%', fd);
}

/*
** print_bench: monta as linhas do exemplo acima.
**   asked -> estrategia pedida (cfg->strat), para mostrar o nome
**   used  -> estrategia real (resolve_strat), para mostrar a classe
** Para cada operacao: op_name(op) + ": " + ctx->ops_count[op].
*/
void	print_bench(t_ctx *ctx, t_strat asked, t_strat used, double dis)
{
	int	op;

	ft_putstr_fd("[bench] disorder: ", 2);
	put_percent_fd(dis, 2);
	ft_putstr_fd("\n[bench] strategy: ", 2);
	ft_putstr_fd(strat_name(asked), 2);
	ft_putstr_fd(" / ", 2);
	ft_putstr_fd(strat_complexity(used), 2);
	ft_putstr_fd("\n[bench] total_ops: ", 2);
	ft_putnbr_fd(total_ops(ctx), 2);
	ft_putstr_fd("\n[bench]", 2);
	op = 0;
	while (op < OP_SIZE)
	{
		ft_putchar_fd(' ', 2);
		ft_putstr_fd(op_name(op), 2);
		ft_putstr_fd(": ", 2);
		ft_putnbr_fd(ctx->ops_count[op], 2);
		op++;
	}
	ft_putchar_fd('\n', 2);
}
