/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 22:35:53 by erayl             #+#    #+#             */
/*   Updated: 2022/01/15 22:36:26 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bphils.h"

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
