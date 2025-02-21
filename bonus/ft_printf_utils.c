/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:14:37 by qlefevre          #+#    #+#             */
/*   Updated: 2022/09/08 16:20:12 by qlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putchar(char c, int *len)
{
	*len += write(2, &c, 1);
}

void	ft_putstr(char const *s, int *len)
{
	int	i;

	i = 0;
	if (s == NULL)
		ft_putstr("(null)", len);
	else
	{
		while (s[i])
		{
			ft_putchar(s[i], len);
			i++;
		}
	}
}

void	ft_putnbr_u(unsigned int nbr, int *len)
{
	if (nbr < 10)
		ft_putchar(nbr + 48, len);
	else
	{
		ft_putnbr_u(nbr / 10, len);
		ft_putnbr_u(nbr % 10, len);
	}
}

void	ft_putnbr_p(va_list arg, int *len)
{
	unsigned long	ptr;

	ptr = va_arg(arg, unsigned long);
	if ((void *)ptr == NULL)
		ft_putstr("(nil)", len);
	else
	{
		ft_putstr("0x", len);
		ft_putnbr_x(ptr, len);
	}
}

void	ft_putnbr_x(unsigned long nbr, int *len)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (nbr < 16)
	{
		ft_putchar(hex[nbr], len);
	}
	else
	{
		ft_putnbr_x(nbr / 16, len);
		ft_putnbr_x(nbr % 16, len);
	}
}
