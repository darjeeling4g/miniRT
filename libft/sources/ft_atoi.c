/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yangsiseon <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:42:07 by yangsiseon        #+#    #+#             */
/*   Updated: 2022/09/02 13:22:44 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	handle_over_ll(unsigned long long result, int sign);

int	ft_atoi(const char *str)
{
	int					sign;
	unsigned long long	result;

	sign = 0;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		str++;
		sign = 1;
	}
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += *str - '0';
		str++;
	}
	result = handle_over_ll(result, sign);
	if (sign == 1)
		return (result * -1);
	return (result);
}

static int	handle_over_ll(unsigned long long result, int sign)
{
	if (result > 9223372036854775807)
	{
		if (sign == 1)
			return (0);
		return (-1);
	}
	return (result);
}
