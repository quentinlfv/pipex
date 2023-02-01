/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:28:14 by qlefevre          #+#    #+#             */
/*   Updated: 2022/09/08 16:34:08 by qlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putnbr_upx(unsigned long nbr, int *len)
{
	char	*hex;

	hex = "0123456789ABCDEF";
	if (nbr < 16)
	{
		ft_putchar(hex[nbr], len);
	}
	else
	{
		ft_putnbr_upx(nbr / 16, len);
		ft_putnbr_upx(nbr % 16, len);
	}
}

int	ft_formats(char c, va_list args, int *len)
{
	if (c == 'c')
		ft_putchar(va_arg(args, int), len);
	else if (c == 's')
		ft_putstr(va_arg(args, char *), len);
	else if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(args, int), len);
	else if (c == 'p')
		ft_putnbr_p(args, len);
	else if (c == 'u')
		ft_putnbr_u(va_arg(args, unsigned int), len);
	else if (c == 'x')
		ft_putnbr_x(va_arg(args, unsigned int), len);
	else if (c == 'X')
		ft_putnbr_upx(va_arg(args, unsigned int), len);
	else if (c == '%')
		ft_putchar('%', len);
	return (1);
}

void	ft_putnbr(int nbr, int *len)
{
	if (nbr == -2147483648)
	{
		ft_putnbr(-2, len);
		ft_putnbr(147483648, len);
	}
	else if (nbr >= 0 && nbr < 10)
	{
		ft_putchar (nbr + 48, len);
	}
	else if (nbr < 0)
	{
		ft_putchar('-', len);
		ft_putnbr(nbr * (-1), len);
	}
	else
	{
		ft_putnbr(nbr / 10, len);
		ft_putnbr(nbr % 10, len);
	}
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		len;
	va_list	ptr;

	len = 0;
	i = 0;
	va_start(ptr, s);
	while (s[i])
	{
		if (s[i] == '%')
			i = i + ft_formats(s[i + 1], ptr, &len);
		else
		{
			ft_putchar(s[i], &len);
		}
		i++;
	}
	va_end(ptr);
	return (len);
}
