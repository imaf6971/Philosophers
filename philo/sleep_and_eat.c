/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_and_eat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:44:03 by marvin            #+#    #+#             */
/*   Updated: 2022/01/14 20:02:15 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

static
void	log4death(t_philosopher *this)
{
	long long	time_of_death;

	this->lifecfg->is_someone_dead = true;
	time_of_death = this->last_time_eated + this->lifecfg->time_to_die;
	printf("%lld %zu died\n", time_of_death, this->num);
}

static
void	die(t_philosopher *this)
{
	pthread_mutex_lock(&this->lifecfg->death_mutex);
	log4death(this);
	pthread_mutex_unlock(&this->lifecfg->death_mutex);
}

static
bool	i_die_in_progress(t_philosopher *this, long long time_of_work)
{
	long long	time_after_work;
	long long	expected_death_time;

	time_after_work = current_timestamp() + time_of_work;
	expected_death_time = this->lifecfg->time_to_die + this->last_time_eated;
	if (time_after_work > expected_death_time)
	{
		die(this);
		return (true);
	}
	return (false);
}

void	eat(t_philosopher *this)
{
	if (this->last_time_eated == 0)
		this->last_time_eated = current_timestamp();
	if (i_die_in_progress(this, this->lifecfg->time_to_eat))
		return ;
	log_print(this, eat_msg);
	accurate_sleep(this->lifecfg->time_to_eat);
	this->last_time_eated = current_timestamp();
	this->eat_count++;
}

void	sweet_sleep(t_philosopher	*this)
{
	if (i_die_in_progress(this, this->lifecfg->time_to_sleep))
		return ;
	log_print(this, sleep_msg);
	accurate_sleep(this->lifecfg->time_to_eat);
}
