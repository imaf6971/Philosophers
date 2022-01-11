/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 17:46:45 by erayl             #+#    #+#             */
/*   Updated: 2022/01/11 19:29:02 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

long long	current_timestamp(void)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
    milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;    
    return (milliseconds);
}

/*
void	death(t_philosopher *this)
{
	size_t	i;

	printf("%lld %zu is dead %lld\n", current_timestamp(), this->num, this->last_time_eated);
	while (true)
	{
		pthread_mutex_lock(&this->cfg->finally.mutex);
		if (this->cfg->finally.priority == this->cfg->number_of_philosophers)
		{
			i = 0;
			while (i < this->cfg->number_of_philosophers)
			{
				pthread_mutex_destroy(&this->cfg->forks[i].mutex);
				i++;
			}
			pthread_mutex_unlock(&this->cfg->finally.mutex);
			break;
		}
		pthread_mutex_unlock(&this->cfg->finally.mutex);
	}
	pthread_mutex_destroy(&this->cfg->finally.mutex);
	pthread_mutex_destroy(&this->cfg->death_mutex);
	free(this->cfg->philosophers);
	free(this->cfg->forks);
	exit(0);
}
*/

void	think(t_philosopher *this)
{
	printf("%lld %zu is thinking\n", current_timestamp(), this->num);
}

void	free_mutexes(t_philosopher *this)
{
	if (this->is_first_locked_by_me)
	{
		this->is_first_locked_by_me = false;
		pthread_mutex_unlock(&this->first->mutex);
	}
	if (this->is_second_locked_by_me)
	{
		this->is_second_locked_by_me = false;
		pthread_mutex_unlock(&this->second->mutex);
	}
}

bool	try_to(t_philosopher *this, void (*action)(t_philosopher *this))
{
	if (!this->cfg->is_someone_dead)
	{
		action(this);
		return (true);
	}
	else
	{
		free_mutexes(this);
		return (false);
	}
}

void	*philosopher(void *param)
{
	t_philosopher	*this;
	size_t			i;
	void			(*life[5])(t_philosopher *this);

	this = param;
	life[0] = &take_forks;
	life[1] = &eat;
	life[2] = &drop_forks;
	life[3] = &sweet_sleep;
	life[4] = &think;
	this->last_time_eated = current_timestamp();
	printf("DEBUG: %lld Phil %zu was born\n", this->last_time_eated, this->num);
	while (true)
	{
		i = 0;
		while (i < 5)
		{
			if (!try_to(this, life[i]))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}