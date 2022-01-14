/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:28:44 by erayl             #+#    #+#             */
/*   Updated: 2022/01/14 20:02:15 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

void	log_print(t_philosopher *this, void (*msg)(t_philosopher *))
{
	pthread_mutex_lock(&this->lifecfg->death_mutex);
	if (!this->lifecfg->is_someone_dead)
		msg(this);
	pthread_mutex_unlock(&this->lifecfg->death_mutex);
}

void	fork_msg(t_philosopher *this)
{
	printf("%lld %zu has taken a fork\n", current_timestamp(), this->num);
}

void	eat_msg(t_philosopher *this)
{
	printf("%lld %zu is eating\n", current_timestamp(), this->num);
}

void	sleep_msg(t_philosopher *this)
{
	printf("%lld %zu is sleeping\n", current_timestamp(), this->num);
}

void	think_msg(t_philosopher *this)
{
	printf("%lld %zu is thinking\n", current_timestamp(), this->num);
}
