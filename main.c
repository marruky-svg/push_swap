/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 11:07:31 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/20 10:30:00 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** init_ctx: zera todas as estruturas (pilhas, contexto e config)
** e liga as pilhas a e b ao contexto. Depois disso:
**   - a e b estao vazias (top = NULL, size = 0)
**   - ops_count esta todo em 0
**   - cfg.strat = STRAT_ADAPTIVE (0) e cfg.bench = 0
*/
static void	init_ctx(t_ctx *ctx, t_stack *a, t_stack *b, t_cfg *cfg)
{
	ft_bzero(a, sizeof(t_stack));
	ft_bzero(b, sizeof(t_stack));
	ft_bzero(ctx, sizeof(t_ctx));
	ft_bzero(cfg, sizeof(t_cfg));
	ctx->a = a;
	ctx->b = b;
}

/*
** main: fluxo do programa
**   1. inicializa as estruturas
**   2. sem argumentos -> nao mostra nada e devolve o prompt
**   3. le as flags (--simple, --medium, ..., --bench);
**      flag invalida ou repetida -> "Error"
**   4. so flags e nenhum numero -> nao mostra nada
**   5. le os numeros para a pilha a;
**      numero invalido, fora de int ou duplicado -> "Error"
**   6. ordena e imprime (run_push_swap)
**   7. libera a memoria (pilhas e buffer) e termina
*/
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
	run_push_swap(&ctx, &cfg);
	free_ctx(&ctx);
	return (0);
}
