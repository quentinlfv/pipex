/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quelefev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:13:04 by quelefev          #+#    #+#             */
/*   Updated: 2025/04/09 16:18:59 by quelefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include "pipex_bonus.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (i < n)
	{
		((char *)s)[i] = '\0';
		i++;
	}
}

char	*ft_strchr(char *s, int c)
{
	int		i;
	char	*pt;

	i = 0;
	if (!s)
		return (NULL);
	if (c > 256)
		c %= 256;
	while (s[i])
	{
		if (s[i] == c)
		{
			pt = &s[i];
			return (pt);
		}
		i++;
	}
	if (s[i] == c)
	{
		pt = &s[i];
		return (pt);
	}
	return (0);
}

char	*ft_string_join(char *mem_line, char *buf)
{
	size_t	len1;
	size_t	len2;
	char	*str;

	len1 = 0;
	len2 = 0;
	if (mem_line != NULL)
		len1 = ft_strlen(mem_line);
	if (buf != NULL)
		len2 = ft_strlen(buf);
	str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (str == NULL)
		return (NULL);
	if (mem_line != NULL)
		ft_strlcpy(str, mem_line, len1 + 1);
	ft_strlcpy(str + len1, buf, len2 + 1);
	ft_bzero(buf, len2);
	free(mem_line);
	return (str);
}
