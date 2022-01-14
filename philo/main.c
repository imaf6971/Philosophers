/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 16:02:30 by erayl             #+#    #+#             */
/*   Updated: 2022/01/14 20:03:38 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

static
void	destroy_table(t_maincfg	*cfg)
{
	size_t	i;
	t_fork	*fork;

	i = 0;
	while (i < cfg->number_of_philosophers)
	{
		fork = cfg->forks + i;
		pthread_mutex_destroy(&fork->mutex);
		i++;
	}
	pthread_mutex_destroy(&cfg->lifecfg.death_mutex);
	free(cfg->philosophers);
	free(cfg->forks);
}

static
void	philosopher_init(t_philosopher *philosopher,
size_t num, t_maincfg *cfg)
{
	t_fork	*right_fork;
	t_fork	*left_fork;

	right_fork = cfg->forks + (num % cfg->number_of_philosophers);
	left_fork = cfg->forks + ((num + 1) % cfg->number_of_philosophers);
	if (left_fork->priority > right_fork->priority)
	{
		philosopher->first = &right_fork->mutex;
		philosopher->second = &left_fork->mutex;
	}
	else
	{
		philosopher->first = &left_fork->mutex;
		philosopher->second = &right_fork->mutex;
	}
	philosopher->eat_count = 0;
	philosopher->num = num + 1;
	philosopher->lifecfg = &cfg->lifecfg;
	philosopher->is_first_locked_by_me = false;
	philosopher->is_second_locked_by_me = false;
}

static
void	create_table(t_maincfg *cfg)
{
	size_t			i;
	t_fork			*forks;
	t_philosopher	*philosophers;

	forks = malloc(sizeof(t_fork) * cfg->number_of_philosophers);
	i = 0;
	while (i < cfg->number_of_philosophers)
	{
		pthread_mutex_init(&forks[i].mutex, NULL);
		forks[i].priority = i;
		i++;
	}
	cfg->forks = forks;
	philosophers = malloc(sizeof(t_philosopher) * cfg->number_of_philosophers);
	i = 0;
	while (i < cfg->number_of_philosophers)
	{
		philosopher_init(philosophers + i, i, cfg);
		i++;
	}
	cfg->philosophers = philosophers;
}

static
void	configure(t_maincfg *cfg, int argc, char **argv)
{
	cfg->number_of_philosophers = ft_atost(argv[1]);
	cfg->lifecfg.time_to_die = ft_atolld(argv[2]);
	cfg->lifecfg.time_to_eat = ft_atolld(argv[3]);
	cfg->lifecfg.time_to_sleep = ft_atolld(argv[4]);
	cfg->lifecfg.is_someone_dead = false;
	pthread_mutex_init(&cfg->lifecfg.death_mutex, NULL);
	if (argc == 6)
		cfg->lifecfg.nums_to_eat = ft_atost(argv[5]);
	else
		cfg->lifecfg.nums_to_eat = 0;
	create_table(cfg);
}

int	main(int argc, char **argv)
{
	t_maincfg	cfg;

	if (argc == 5 || argc == 6)
	{
		configure(&cfg, argc, argv);
		create_threads(&cfg);
		wait_for_threads(&cfg);
		destroy_table(&cfg);
	}
	return (0);
}
