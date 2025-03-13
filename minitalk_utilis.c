/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utilis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:45:39 by mohkhald          #+#    #+#             */
/*   Updated: 2025/03/10 00:44:16 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(const char *str)
{
	unsigned int	n;
	int				sing;
	char			*s;

	s = (char *)str;
	n = 0;
	sing = 1;
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

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
