/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:32:46 by qlefevre          #+#    #+#             */
/*   Updated: 2025/04/14 17:58:57 by quelefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex_bonus.h"

int	strnbr(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			while (s[i] && s[i] != c)
				i++;
			count++;
		}
		while (s[i] && s[i] == c)
			i++;
	}
	return (count);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*str;
	unsigned int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s) - start)
		str = malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else if (start > ft_strlen(s))
	{
		str = malloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
		str[0] = 0;
		return (str);
	}
	else
		str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (i < len && s[start])
		str[i++] = s[start++];
	str[i] = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	str = malloc(sizeof(char *) * (strnbr(s, c) + 1));
	if (!str)
		return (NULL);
	while (i < strnbr(s, c))
	{
		while (s[j] == c && s[j])
			j++;
		while (s[j] != c && s[j])
		{
			k++;
			j++;
		}
		str[i++] = ft_substr(s, (j - k), k);
		k = 0;
	}
	str[i] = NULL;
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*str;

	len1 = 0;
	len2 = 0;
	if (s1 != NULL)
		len1 = ft_strlen(s1);
	if (s2 != NULL)
		len2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (str == NULL)
		return (NULL);
	if (s1 != NULL)
		ft_strlcpy(str, s1, len1 + 1);
	ft_strlcpy(str + len1, s2, len2 + 1);
	return (str);
}
