/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 17:46:45 by erayl             #+#    #+#             */
/*   Updated: 2021/12/19 20:07:26 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

void	*philosopher(void *param)
{
	t_philosopher	*this;

	this = param;
	printf("Phil %zu was born\n", this->num);
	while (this->is_alive);
	return (NULL);
}