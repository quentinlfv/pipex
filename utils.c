/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:27:14 by qlefevre          #+#    #+#             */
/*   Updated: 2023/02/01 14:27:33 by qlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	close_doc(int fd)
{
	if (close(fd) < 0)
	{
		printf("failed to close\n");
		return (-1);
	}
	return (1);
}

int	strcmmp(const char *s1, const char *s2, int i)
{
	int	j;

	j = 0;
	while (s2[j] == s1[i] && s2[j] && s1[j])
	{
		i++;
		j++;
	}
	if (s2[j] != 0)
		return (s1[i] - s2[j]);
	return (s1[i -1] - s2[j - 1]);
}

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	char			*ptr;
	unsigned int	i;
	int				a;

	ptr = (char *)s1;
	i = 0;
	a = 0;
	if (s2[i] == '\0')
		return ((char *)s1);
	while (s1[i] && i < n)
	{
		if (s1[i] == s2[0])
		{
			a = strcmmp(s1, s2, i);
			if (ft_strlen(s2) + i > n)
				a = 1;
			if (a == 0)
				return (ptr + i);
		}
		i++;
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	int				srclen;

	i = 0;
	srclen = ft_strlen(src);
	if (!dst || !src)
		return (0);
	if (size == 0)
		return (srclen);
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (srclen);
}
