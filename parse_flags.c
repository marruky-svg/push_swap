/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 18:26:11 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/11 19:50:47 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** is_flag: verifica se o argumento comeca com "--".
** Qualquer coisa que nao comece com "--" e tratada como numero
** (ex.: "-5" e numero, "--simple" e flag).
*/
static int	is_flag(char *str)
{
	size_t	i;

	i = 0;
	while (i < 2)
	{
		if (str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

/*
** put_flag: aplica uma flag ao t_cfg.
**   --bench   -> liga o modo benchmark (pode ser combinado com
**                qualquer estrategia)
**   --simple / --medium / --complex / --adaptive
**             -> escolhe a estrategia; so e permitida UMA flag
**                de estrategia (flag_count controla isso)
**   qualquer outra coisa com "--" -> erro
** O tamanho passado ao ft_strncmp inclui o '\0', entao a
** comparacao e exata ("--simplex" nao e aceito).
** Retorna 1 se ok, -1 se erro.
*/
static int	put_flag(char *arg, t_cfg *cfg, int *flag_count)
{
	if (!ft_strncmp(arg, "--bench", 8))
		cfg->bench = 1;
	else
	{
		if (*flag_count > 0)
			return (-1);
		if (!ft_strncmp(arg, "--simple", 9))
			cfg->strat = STRAT_SIMPLE;
		else if (!ft_strncmp(arg, "--medium", 9))
			cfg->strat = STRAT_MEDIUM;
		else if (!ft_strncmp(arg, "--complex", 10))
			cfg->strat = STRAT_COMPLEX;
		else if (!ft_strncmp(arg, "--adaptive", 11))
			cfg->strat = STRAT_ADAPTIVE;
		else
			return (-1);
		(*flag_count)++;
	}
	return (1);
}

/*
** parse_flags: le todas as flags do inicio do argv.
** As flags precisam vir ANTES dos numeros; o laco para no
** primeiro argumento que nao e flag.
** Retorna o indice do primeiro numero no argv, ou -1 em erro.
*/
int	parse_flags(char **argv, t_cfg *cfg)
{
	int	i;
	int	flag_count;

	i = 1;
	flag_count = 0;
	while (argv[i] && is_flag(argv[i]))
	{
		if (put_flag(argv[i], cfg, &flag_count) == -1)
			return (-1);
		i++;
	}
	return (i);
}
