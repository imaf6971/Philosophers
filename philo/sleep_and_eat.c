/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_and_eat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:44:03 by marvin            #+#    #+#             */
/*   Updated: 2022/01/15 21:29:19 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

static
void	log4death(t_phil *self)
{
	t_ms	time_of_death;

	self->lifecfg->is_someone_dead = true;
	time_of_death = self->last_time_eated + self->lifecfg->time_to_die;
	printf("%lld %zu died\n", time_of_death, self->num);
}

void	die(t_phil *self)
{
	pthread_mutex_lock(&self->lifecfg->death_mutex);
	log4death(self);
	pthread_mutex_unlock(&self->lifecfg->death_mutex);
}

static
bool	i_die_in_progress(t_phil *self, t_ms time_of_work)
{
	t_ms	time_after_work;
	t_ms	expected_death_time;

	time_after_work = current_timestamp() + time_of_work;
	expected_death_time = self->lifecfg->time_to_die + self->last_time_eated;
	if (time_after_work > expected_death_time)
	{
		die(self);
		return (true);
	}
	return (false);
}

void	eat(t_phil *self)
{
	if (self->last_time_eated == 0)
		self->last_time_eated = current_timestamp();
	if (i_die_in_progress(self, self->lifecfg->time_to_eat))
		return ;
	log_print(self, eat_msg);
	accurate_sleep(self->lifecfg->time_to_eat);
	self->last_time_eated = current_timestamp();
	self->eat_count++;
}

void	sweet_sleep(t_phil	*self)
{
	if (i_die_in_progress(self, self->lifecfg->time_to_sleep))
		return ;
	log_print(self, sleep_msg);
	accurate_sleep(self->lifecfg->time_to_eat);
}
