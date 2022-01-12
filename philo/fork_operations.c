/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:39:59 by marvin            #+#    #+#             */
/*   Updated: 2022/01/12 17:25:35 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

void	take_first(t_philosopher *this)
{
	pthread_mutex_lock(this->first);
	this->is_first_locked_by_me = true;
	printf("%lld %zu has taken a fork\n", current_timestamp(), this->num);
}

void	take_second(t_philosopher *this)
{
	pthread_mutex_lock(this->second);
	this->is_second_locked_by_me = true;
	printf("%lld %zu has taken a fork\n", current_timestamp(), this->num);
}

void	drop_second(t_philosopher *this)
{
	this->is_second_locked_by_me = false;
	pthread_mutex_unlock(this->second);
	printf("%lld %zu dropped a fork\n", current_timestamp(), this->num);
}

void	drop_first(t_philosopher *this)
{
	this->is_first_locked_by_me = false;
	pthread_mutex_unlock(this->first);
	printf("%lld %zu dropped a fork\n", current_timestamp(), this->num);
}
