/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:03:00 by hbourlot          #+#    #+#             */
/*   Updated: 2025/03/08 15:25:37 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief Converts a string representation of a number to an LL.
/// @param nptr Pointer to the string to be converted.
/// @return The converted LL integer.
long long	ft_atoll(const char *nptr)
{
	int			tot;
	long long	sign;
	long long	number;

	number = 0;
	sign = 1;
	tot = 0;
	while ((nptr[tot] >= 9 && nptr[tot] <= 13) || nptr[tot] == ' ')
		tot++;
	if (nptr[tot] == '+' || nptr[tot] == '-')
	{
		if (nptr[tot] == '-')
			sign = -1;
		tot++;
	}
	while (nptr[tot] >= '0' && nptr[tot] <= '9')
	{
		number = (number * 10) + nptr[tot] - '0';
		tot++;
	}
	return (number * sign);
}
