/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quelefev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:05:08 by quelefev          #+#    #+#             */
/*   Updated: 2025/04/09 15:48:11 by quelefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex_bonus.h"

int	ft_strncmp(const char *string1, const char *string2, size_t count)
{
	unsigned int	i;

	i = 0;
	if (count == 0)
		return (0);
	while ((string1[i] == string2[i]) && (i < count - 1) && (string1[i] != 0))
		i++;
	return (((unsigned char)string1[i]) - ((unsigned char)string2[i]));
}
