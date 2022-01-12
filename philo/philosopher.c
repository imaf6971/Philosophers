/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 17:46:45 by erayl             #+#    #+#             */
/*   Updated: 2022/01/12 17:47:41 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

void	think(t_philosopher *this)
{
	printf("%lld %zu is thinking\n", current_timestamp(), this->num);
}

void	free_mutexes(t_philosopher *this)
{
	if (this->is_first_locked_by_me)
	{
		this->is_first_locked_by_me = false;
		pthread_mutex_unlock(this->first);
	}
	if (this->is_second_locked_by_me)
	{
		this->is_second_locked_by_me = false;
		pthread_mutex_unlock(this->second);
	}
}

bool	try_to(t_philosopher *this, void (*action)(t_philosopher *this))
{
	if (!this->lifecfg->is_someone_dead)
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
	void			(*life[7])(t_philosopher *this);

	this = param;
	life[0] = &take_first;
	life[1] = &take_second;
	life[2] = &eat;
	life[3] = &drop_second;
	life[4] = &drop_first;
	life[5] = &sweet_sleep;
	life[6] = &think;
	this->last_time_eated = current_timestamp();
	printf("DEBUG: %lld Phil %zu was born\n", this->last_time_eated, this->num);
	while (true)
	{
		i = 0;
		while (i < 7)
		{
			if (!try_to(this, life[i]))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}