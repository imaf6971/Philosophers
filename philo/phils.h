/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 17:18:04 by erayl             #+#    #+#             */
/*   Updated: 2022/01/11 19:15:46 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILS_H
# define PHILS_H
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
typedef struct s_fork
{
	pthread_mutex_t	mutex;
	size_t			priority;
}	t_fork;
typedef struct s_phil
{
	pthread_t		th;
	struct s_cfg	*cfg;
	size_t			num;
	t_fork			*first;
	bool			is_first_locked_by_me;
	t_fork			*second;
	bool			is_second_locked_by_me;
	long long		last_time_eated;
}	t_philosopher;
typedef struct s_cfg
{
	size_t			number_of_philosophers;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	size_t			nums_to_eat;
	t_philosopher	*philosophers;
	t_fork			*forks;
	bool			is_someone_dead;
}	t_philconfig;
long long	ft_atolld(const char *s);
size_t		ft_atost(const char *s);
void		*philosopher(void *param);
void	take_forks(t_philosopher *this);
void	eat(t_philosopher *this);
void	drop_forks(t_philosopher *this);
void	sweet_sleep(t_philosopher	*this);
void	end_job(t_philosopher *this);
void	free_mutexes(t_philosopher *this);
void	death(t_philosopher *this);
long long	current_timestamp(void);
#endif