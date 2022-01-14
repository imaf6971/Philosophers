/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 17:46:45 by erayl             #+#    #+#             */
/*   Updated: 2022/01/14 20:36:03 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

static
void	think(t_philosopher *this)
{
	log_print(this, think_msg);
}

static
void	free_mutexes(t_philosopher *this)
{
	if (this->is_first_locked_by_me)
		drop_first(this);
	if (this->is_second_locked_by_me)
		drop_second(this);
}

static
bool	i_have_eaten_enough(t_philosopher *this)
{
	if (this->lifecfg->nums_to_eat)
		return (!(this->eat_count < this->lifecfg->nums_to_eat));
	return (false);
}

static
bool	try_to(t_philosopher *this, void (*action)(t_philosopher *))
{
	if (i_have_eaten_enough(this) || this->lifecfg->is_someone_dead)
	{
		free_mutexes(this);
		return (false);
	}
	action(this);
	return (true);
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
