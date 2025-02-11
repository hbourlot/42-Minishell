/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:51:20 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/11 14:29:11 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	number_base(long nbr, char *fmt)
{
	int	len;

	len = ft_strlen(fmt);
	if (nbr < 0)
	{
		ft_putchar('-');
		return (number_base(-nbr, fmt));
	}
	if (nbr >= len)
	{
		number_base(nbr / len, fmt);
		return (number_base(nbr % len, fmt));
	}
	else
		return (ft_putchar_fd(fmt[nbr], 2));
}

static void	base_p_negative(unsigned long nbr, char *fmt)
{
	int	len;

	len = ft_strlen(fmt);
	if (nbr >= 16)
	{
		base_p_negative(nbr / len, fmt);
		return (base_p_negative(nbr % len, fmt));
	}
	else
		return (ft_putchar_fd("0123456789abcdef"[nbr], 2));
}

static void	handle_flags(long nbr, char fmt, char *base)
{
	if (fmt == 'p' && nbr <= 0)
	{
		if (nbr == 0)
			return (ft_putstr_fd("(nil)", 2));
		return (ft_putstr_fd("Ox", 2), base_p_negative(nbr, base));
	}
	else if (fmt == 'p')
		return (ft_putstr_fd("Ox", 2), base_p_negative(nbr, base));
	else if (fmt == 'x' || fmt == 'X')
		return (number_base(nbr, base));
	else
		return (number_base(nbr, base));
}

static void	ft_format(const char *fmt, va_list *ap)
{
	if (fmt[0] == 'c')
		ft_putchar_fd(va_arg(*ap, int), 2);
	else if (fmt[0] == 's')
		ft_putstr_fd(va_arg(*ap, char *), 2);
	else if (fmt[0] == 'p')
		handle_flags((long)va_arg(*ap, unsigned long), 'p', "0123456789abcdef");
	else if (fmt[0] == 'd' || fmt[0] == 'i')
		handle_flags(va_arg(*ap, int), 'i', "0123456789");
	else if (fmt[0] == 'u')
		handle_flags(va_arg(*ap, unsigned int), 'u', "0123456789");
	else if (fmt[0] == 'X')
		handle_flags(va_arg(*ap, unsigned int), 'X', "0123456789ABCDEF");
	else if (fmt[0] == 'x')
		handle_flags(va_arg(*ap, unsigned int), 'x', "0123456789abcdef");
	else if (fmt[0] == '%')
		ft_putchar_fd('%', 2);
}

void	ft_printf_error(const char *fmt, ...)
{
	va_list	ap;
	int		i;
	int		j;

	i = 0;
	if (fmt == NULL)
		return ;
	va_start(ap, fmt);
	while (fmt[i])
	{
		if (fmt[i] == '%')
			ft_format(&fmt[++i], &ap);
		else
		{
			j = 0;
			while (fmt[i + j] && fmt[i + j] != '%')
				j++;
			write(2, fmt + i, j);
			i += j - 1;
		}
		i++;
	}
	va_end(ap);
}
