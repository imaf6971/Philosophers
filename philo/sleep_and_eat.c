/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_and_eat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:44:03 by marvin            #+#    #+#             */
/*   Updated: 2022/01/12 17:51:27 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

static
bool	i_die_in_progress(t_philosopher	*this, long long ts, long long time_of_work)
{
	long long	time_after_work;
	long long	death_time;

	time_after_work = ts + time_of_work;
	death_time = this->lifecfg->time_to_die + this->last_time_eated;
	printf("phil %zu\nlte %lld\nts: %lld\ntaw: %lld\ndt: %lld\n", this->num, this->last_time_eated, ts, time_after_work, death_time);
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

	this->lifecfg->is_someone_dead = true;
	time_of_death = this->last_time_eated + this->lifecfg->time_to_die;
	printf("%lld dead %zu\n", time_of_death, this->num);
}

void	eat(t_philosopher *this)
{
	long long	ts;

	ts = current_timestamp();
	if (i_die_in_progress(this, ts, this->lifecfg->time_to_eat))
	{
		wait_for_death(this);
		return ;
	}
	else
	{
		this->last_time_eated = ts;
		printf("%lld %zu is eating\n", this->last_time_eated, this->num);
		wwwait(this->lifecfg->time_to_eat);
	}
}

void	sweet_sleep(t_philosopher	*this)
{
	long long	ts;

	ts = current_timestamp();
	if (i_die_in_progress(this, ts, this->lifecfg->time_to_sleep))
	{
		wait_for_death(this);
		return ;
	}
	else
	{
		printf("%lld %zu is sleeping\n", ts, this->num);
		wwwait(this->lifecfg->time_to_eat);
	}
}