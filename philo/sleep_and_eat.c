/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_and_eat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:44:03 by marvin            #+#    #+#             */
/*   Updated: 2022/01/11 19:36:33 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

static
bool	i_die_in_progress(t_philosopher	*this, long long ts, long long time_of_work)
{
	long long	time_after_work;
	long long	death_time;

	time_after_work = ts + time_of_work;
	death_time = this->cfg->time_to_die + this->last_time_eated;
	printf("ts: %lld\ntaw: %lld\ndt: %lld\n", ts, time_after_work, death_time);
	if (time_after_work > death_time)
	{
		return (true);
	}
	else
		return (false);
}

void	wait_for_death(t_philosopher *this)
{
	long long	time_of_death;

	this->cfg->is_someone_dead = true;
	time_of_death = this->last_time_eated + this->cfg->time_to_die;
	usleep((time_of_death - current_timestamp()) * 1000);
	free_mutexes(this);
	death(this);
}

void	eat(t_philosopher *this)
{
	long long	ts;

	ts = current_timestamp();
	this->last_time_eated = ts;
	if (i_die_in_progress(this, ts, this->cfg->time_to_eat))
		wait_for_death(this);
	else
	{
		printf("%lld %zu is eating\n", this->last_time_eated, this->num);
		usleep(this->cfg->time_to_eat * 1000);
	}
}

void	sweet_sleep(t_philosopher	*this)
{
	long long	ts;

	ts = current_timestamp();
	if (i_die_in_progress(this, ts, this->cfg->time_to_sleep))
		wait_for_death(this);
	else
	{
		printf("%lld %zu is sleeping\n", ts, this->num);
		usleep(this->cfg->time_to_sleep * 1000);
	}
}