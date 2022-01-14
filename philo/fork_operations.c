/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:39:59 by marvin            #+#    #+#             */
/*   Updated: 2022/01/14 20:02:15 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

void	take_first(t_philosopher *this)
{
	pthread_mutex_lock(this->first);
	this->is_first_locked_by_me = true;
	log_print(this, fork_msg);
}

void	take_second(t_philosopher *this)
{
	pthread_mutex_lock(this->second);
	this->is_second_locked_by_me = true;
	log_print(this, fork_msg);
}

void	drop_second(t_philosopher *this)
{
	this->is_second_locked_by_me = false;
	pthread_mutex_unlock(this->second);
}

void	drop_first(t_philosopher *this)
{
	this->is_first_locked_by_me = false;
	pthread_mutex_unlock(this->first);
}
