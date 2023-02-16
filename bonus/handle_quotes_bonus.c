/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:39:49 by ebezerra          #+#    #+#             */
/*   Updated: 2023/02/09 22:39:51 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	**splitted_result(const char *s, t_split *splt);
static void	splitted_result_loop(const char *s, t_split *splt);
static int	count_tokens(const char *s, t_split *splitted);

t_bool	check_for_quotes(char *cmd)
{
	char	*quotes;

	quotes = ft_strchr(cmd, '\'');
	if (quotes)
	{
		quotes = ft_strchr(quotes, '\'');
		if (quotes)
			return (true_);
	}
	return (false_);
}

char	**split_with_quotes(const char *s)
{
	t_split	splitted;

	splitted.count = count_tokens(s, &splitted);
	if (splitted.count == -1)
		return (NULL);
	splitted.res = ft_calloc((splitted.count + 2), sizeof(char *));
	splitted.res = splitted_result(s, &splitted);
	return (splitted.res);
}

static int	count_tokens(const char *s, t_split *splitted)
{
	int	i;
	int	quotes_num;

	i = 0;
	quotes_num = 0;
	splitted->count = 0;
	splitted->in_quote = false_;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			splitted->in_quote = !splitted->in_quote;
			i++;
			quotes_num++;
			continue ;
		}
		if (!splitted->in_quote && s[i] == ' ')
			splitted->count++;
		i++;
	}
	if (quotes_num % 2 != 0)
		return (-1);
	return (splitted->count);
}

static char	**splitted_result(const char *s, t_split *splt)
{
	splt->i = 0;
	splt->j = 0;
	splt->count = 0;
	while (s[splt->i])
		splitted_result_loop(s, splt);
	splt->len = splt->i - splt->j;
	if (s[splt->j] == '\"' || s[splt->j] == '\'')
	{
		splt->j++;
		splt->len--;
	}
	if (s[splt->i - 1] == '\"' || s[splt->i - 1] == '\'')
		splt->len--;
	splt->res[splt->count++] = ft_strndup(s + splt->j, splt->len);
	splt->res[splt->count] = NULL;
	return (splt->res);
}

static void	splitted_result_loop(const char *s, t_split *splt)
{
	if (s[splt->i] == '\"' || s[splt->i] == '\'')
	{
		splt->in_quote = !splt->in_quote;
		splt->i++;
		return ;
	}
	if (!splt->in_quote && s[splt->i] == ' ')
	{
		splt->len = splt->i - splt->j;
		if (s[splt->j] == '\"' || s[splt->j] == '\'')
		{
			splt->j++;
			splt->len--;
		}
		if (s[splt->i - 1] == '\"' || s[splt->i - 1] == '\'')
			splt->len--;
		splt->res[splt->count++] = ft_strndup(s + splt->j, splt->len);
		splt->j = splt->i + 1;
	}
	splt->i++;
}
