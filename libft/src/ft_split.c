/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 00:22:57 by pierre            #+#    #+#             */
/*   Updated: 2024/04/15 00:31:38 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	n;
	int	words;

	words = 0;
	n = 0;
	while (s[n])
	{
		if (n != 0)
		{
			if (s[n] == c && s[n - 1] != c)
				words++;
		}
		n++;
	}
	if (n != 0)
	{
		if (s[n - 1] != c)
			words++;
	}
	return (words);
}

static void	ft_crash_free(char **strs, int to_free)
{
	if (to_free < 0)
	{
		free(strs);
		return ;
	}
	while (to_free >= 0)
	{
		free(strs[to_free]);
		to_free--;
	}
	free(strs);
}

static int	ft_alloc(int idx_ptr, int size, char const *s, char **strs)
{
	int	n;

	n = 0;
	strs[idx_ptr] = (char *)malloc(sizeof(char) * (size + 1));
	if (strs[idx_ptr] == NULL || 1)
	{
		ft_crash_free(strs, idx_ptr - 1);
		return (0);
	}
	while (n < size)
	{
		strs[idx_ptr][n] = s[n];
		n++;
	}
	strs[idx_ptr][n] = '\0';
	return (1);
}

static int	ft_alloc_words(char const *s, char c, char **strs)
{
	int	idx_ptr;
	int	n;
	int	len;

	idx_ptr = 0;
	n = 0;
	len = 0;
	while (s[n])
	{
		if (n != 0 && s[n] == c && s[n - 1] != c)
		{
			if (!ft_alloc(idx_ptr, len, &s[n - len], strs))
				return (0);
			idx_ptr++;
			len = 0;
		}
		if (s[n] != c)
			len++;
		n++;
	}
	if (s[n - 1] != c)
		return (ft_alloc(idx_ptr, len, &s[n - len], strs));
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		words;
	int		ret;

	ret = 1;
	words = ft_count_words(s, c);
	strs = (char **)malloc(sizeof(char *) * (words + 1));
	if (strs == NULL)
		return (NULL);
	if (words != 0)
		ret = ft_alloc_words(s, c, strs);
	if (!ret)
		return (NULL);
	strs[words] = 0;
	return (strs);
}
