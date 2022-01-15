/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 17:18:04 by erayl             #+#    #+#             */
/*   Updated: 2022/01/15 21:25:47 by erayl            ###   ########.fr       */
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

typedef long long	t_ms;
typedef struct s_fork
{
	pthread_mutex_t	mutex;
	size_t			priority;
	size_t			taken_by;
}	t_fork;
typedef struct s_cfg
{
	t_ms			time_to_die;
	t_ms			time_to_eat;
	t_ms			time_to_sleep;
	size_t			nums_to_eat;
	pthread_mutex_t	death_mutex;
	bool			is_someone_dead;
}	t_lifecfg;
typedef struct s_phil
{
	pthread_t		th;
	t_lifecfg		*lifecfg;
	size_t			num;
	t_fork			*left_fork;
	t_fork			*right_fork;
	size_t			eat_count;
	t_ms			last_time_eated;
}	t_phil;
typedef struct s_maincfg
{
	size_t		num_of_phils;
	t_lifecfg	lifecfg;
	t_phil		*philosophers;
	t_fork		*forks;
}	t_maincfg;
t_ms	ft_atoms(const char *s);
size_t	ft_atost(const char *s);
void	*philosopher(void *param);
void	take_forks(t_phil *self);
void	eat(t_phil *self);
void	drop_forks(t_phil *self);
void	sweet_sleep(t_phil	*self);
void	die(t_phil *self);
void	create_threads(t_maincfg *cfg);
void	wait_for_threads(t_maincfg *cfg);
t_ms	current_timestamp(void);
void	accurate_sleep(t_ms time_to_wait);
void	log_print(t_phil *self, void (*msg)(t_phil *));
void	fork_msg(t_phil *self);
void	eat_msg(t_phil *self);
void	sleep_msg(t_phil *self);
void	think_msg(t_phil *self);
#endif