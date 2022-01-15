/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 17:46:45 by erayl             #+#    #+#             */
/*   Updated: 2022/01/15 21:26:36 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

static
void	think(t_phil *self)
{
	log_print(self, think_msg);
}

static
bool	i_have_eaten_enough(t_phil *self)
{
	if (self->lifecfg->nums_to_eat)
		return (self->eat_count >= self->lifecfg->nums_to_eat);
	return (false);
}

static
bool	try_to(t_phil *self, void (*action)(t_phil *))
{
	if (i_have_eaten_enough(self) || self->lifecfg->is_someone_dead)
	{
		drop_forks(self);
		return (false);
	}
	action(self);
	return (true);
}

void	*philosopher(void *param)
{
	t_phil	*self;
	size_t	i;
	void	(*life[7])(t_phil *);

	self = param;
	life[0] = &take_forks;
	life[1] = &eat;
	life[2] = &drop_forks;
	life[3] = &sweet_sleep;
	life[4] = &think;
	self->last_time_eated = 0;
	while (true)
	{
		i = 0;
		while (i < 5)
		{
			if (!try_to(self, life[i]))
				return (NULL);
			i++;
		}
	}
}
