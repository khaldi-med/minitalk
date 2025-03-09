#include "minitalk.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned	n;
	int			sing;
	char		*s;

	n = 0;
	sing = 1;
	s = (char *)str;
	while ((*s >= 9 && *s <= 13) || *s == ' ')
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sing *= -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		n = (n * 10) + (*s - '0');
		s++;
	}
	return (sing * n);
}
