/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:39:59 by marvin            #+#    #+#             */
/*   Updated: 2022/01/15 21:27:27 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

static
void	take_fork(t_phil *self, t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->taken_by = self->num;
	log_print(self, fork_msg);
}

static
void	drop_fork(t_phil *self, t_fork *fork)
{
	if (fork->taken_by == self->num)
	{
		fork->taken_by = 0;
		pthread_mutex_unlock(&fork->mutex);
	}
}

void	take_forks(t_phil *self)
{
	if (self->right_fork == self->left_fork)
	{
		die(self);
		return ;
	}
	if (self->left_fork->priority > self->right_fork->priority)
	{
		take_fork(self, self->left_fork);
		take_fork(self, self->right_fork);
	}
	else
	{
		take_fork(self, self->right_fork);
		take_fork(self, self->left_fork);
	}
}

void	drop_forks(t_phil *self)
{
	if (self->left_fork->priority > self->right_fork->priority)
	{
		drop_fork(self, self->right_fork);
		drop_fork(self, self->left_fork);
	}
	else
	{
		drop_fork(self, self->left_fork);
		drop_fork(self, self->right_fork);
	}
}
