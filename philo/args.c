/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 17:29:24 by erayl             #+#    #+#             */
/*   Updated: 2022/01/15 21:27:14 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

static
bool	ft_isdigit(int c)
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
	if (*s)
		return (0ul);
	return (result);
}

t_ms	ft_atoms(const char *s)
{
	t_ms	result;

	result = 0;
	while (*s && ft_isdigit(*s))
	{
		result *= 10ll;
		result += *s - '0';
		s++;
	}
	if (*s)
		return (0ll);
	return (result);
}
