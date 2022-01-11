/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 17:29:24 by erayl             #+#    #+#             */
/*   Updated: 2021/12/19 19:16:15 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

static
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

size_t	ft_atost(const char *s)
{
	size_t	result;

	result = 0;
	while (*s && ft_isdigit(*s))
	{
		result *= 10ul;
		result += *s - '0';
		s++;
	}
	return (result);
}

long long ft_atolld(const char *s)
{
	long long	result;

	result = 0;
	while (*s && ft_isdigit(*s))
	{
		result *= 10ll;
		result += *s - '0';
		s++;
	}
	return (result);
}
