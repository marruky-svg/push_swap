/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 20:05:10 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/16 17:58:13 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** read_sign: le um sinal opcional ('+' ou '-') no inicio de str.
** Avanca o indice i se houver sinal.
** Retorna -1 para '-' e 1 para '+' ou sem sinal.
*/
static int	read_sign(char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

/*
** free_split: libera o array de strings gerado pelo ft_split
** (cada palavra e depois o proprio array).
*/
static void	free_split(char **word)
{
	int	i;

	i = 0;
	while (word[i])
		free(word[i++]);
	free(word);
}

/*
** parse_arg: trata UM argumento do argv.
** Um argumento pode conter varios numeros separados por espaco
** (ex.: ./push_swap "3 2 1"), por isso usa ft_split(arg, ' ').
**   - argumento vazio ou so espacos (words[0] == NULL) -> erro
**   - para cada palavra: valida o numero (parse_number),
**     verifica duplicado (has_value) e coloca no FUNDO da
**     pilha a (add_bottom), mantendo a ordem: 1o arg = topo
**   - para no primeiro erro (is_ok = 0)
** Sempre libera o split antes de retornar.
** Retorna 1 se tudo ok, 0 se houve erro.
*/
static int	parse_arg(char *arg, t_stack *a)
{
	char	**words;
	int		is_ok;
	int		i;
	int		n;

	n = 0;
	words = ft_split(arg, ' ');
	if (!words)
		return (0);
	is_ok = (words[0] != NULL);
	i = 0;
	while (words[i] && is_ok)
		is_ok = (parse_number(words[i++], &n) && !has_value(a, n)
				&& add_bottom(a, n));
	free_split(words);
	return (is_ok);
}

/*
** parse_number: converte str em int com validacao completa.
**   - aceita um sinal opcional no inicio
**   - exige pelo menos um digito (rejeita "", "-", "+")
**   - rejeita qualquer caractere que nao seja digito ("12a")
**   - usa long para detectar overflow durante a conversao:
**       positivo: limite INT_MAX     ( 2147483647)
**       negativo: limite INT_MAX + 1 (-2147483648 = INT_MIN)
** Se valido, grava o valor em *out e retorna 1; senao retorna 0.
*/
int	parse_number(char *str, int *out)
{
	int		i;
	int		sign;
	long	result;
	long	limit;

	i = 0;
	result = 0;
	sign = read_sign(str, &i);
	limit = INT_MAX;
	if (sign == -1)
		limit = INT_MAX + 1L;
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		if (result > limit)
			return (0);
		i++;
	}
	if (str[i])
		return (0);
	*out = (int)(result * sign);
	return (1);
}

/*
** parse_args: percorre o argv a partir de 'start' (primeiro
** argumento que nao e flag) e preenche a pilha a.
** Retorna 1 se todos os argumentos forem validos, 0 no primeiro erro.
*/
int	parse_args(char **argv, int start, t_stack *a)
{
	int	i;
	int	n;

	i = start;
	while (argv[i])
	{
		n = parse_arg(argv[i++], a);
		if (!n)
			return (0);
	}
	return (1);
}
