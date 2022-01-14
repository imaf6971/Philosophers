/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 17:18:04 by erayl             #+#    #+#             */
/*   Updated: 2022/01/14 20:02:15 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILS_H
# define PHILS_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	size_t			priority;
}	t_fork;
typedef struct s_cfg
{
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	size_t			nums_to_eat;
	pthread_mutex_t	death_mutex;
	bool			is_someone_dead;
}	t_lifecfg;
typedef struct s_phil
{
	pthread_t		th;
	t_lifecfg		*lifecfg;
	size_t			num;
	pthread_mutex_t	*first;
	bool			is_first_locked_by_me;
	pthread_mutex_t	*second;
	bool			is_second_locked_by_me;
	size_t			eat_count;
	long long		last_time_eated;
}	t_philosopher;
typedef struct s_maincfg
{
	size_t			number_of_philosophers;
	t_lifecfg		lifecfg;
	t_philosopher	*philosophers;
	t_fork			*forks;
}	t_maincfg;
long long	ft_atolld(const char *s);
size_t		ft_atost(const char *s);
void		*philosopher(void *param);
void		take_first(t_philosopher *this);
void		take_second(t_philosopher *this);
void		eat(t_philosopher *this);
void		drop_second(t_philosopher *this);
void		drop_first(t_philosopher *this);
void		sweet_sleep(t_philosopher	*this);
void		create_threads(t_maincfg *cfg);
void		wait_for_threads(t_maincfg *cfg);
long long	current_timestamp(void);
void		accurate_sleep(long long time_to_wait);
long long	time_from_start(long long start_time);
void		log_print(t_philosopher *this, void (*msg)(t_philosopher *));
void		fork_msg(t_philosopher *this);
void		eat_msg(t_philosopher *this);
void		sleep_msg(t_philosopher *this);
void		think_msg(t_philosopher *this);
#endif