/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:39:59 by marvin            #+#    #+#             */
/*   Updated: 2021/12/22 22:39:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

void	take_forks(t_philosopher *this)
{
	pthread_mutex_lock(&this->first->mutex);
	this->is_first_locked_by_me = true;
	printf("%lld %zu has taken first %zu fork\n", current_timestamp(), this->num, this->first->priority);
	pthread_mutex_lock(&this->second->mutex);
	this->is_second_locked_by_me = true;
	printf("%lld %zu has taken second %zu fork\n", current_timestamp(), this->num, this->second->priority);
}

void	drop_forks(t_philosopher *this)
{
	this->is_second_locked_by_me = false;
	pthread_mutex_unlock(&this->second->mutex);
	printf("%lld %zu dropped second %zu fork\n", current_timestamp(), this->num, this->second->priority);
	this->is_first_locked_by_me = false;
	pthread_mutex_unlock(&this->first->mutex);
	printf("%lld %zu dropped first %zu fork\n", current_timestamp(), this->num, this->first->priority);
}
