#include "miniRT.h"

double	make_double(const char *str, int *len)
{
	double	result;
	int		i;

	*len = 0;
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += *str - '0';
		str++;
		(*len)++;
	}
	if (*str == '.')
		str++;
	i = 10;
	while (*str >= '0' && *str <= '9')
	{
		result += (double)(*str - '0') / i;
		i *= 10;
		str++;
		(*len)++;
	}
	return (result);
}

double	ft_atof(const char *str)
{
	int		sign;
	double	result;
	int		len;

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
	result = make_double(str, &len);
	if (sign == 1)
		return (result * -1);
	return (result);
}

