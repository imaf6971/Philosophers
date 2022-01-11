/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 16:02:30 by erayl             #+#    #+#             */
/*   Updated: 2021/12/19 20:07:02 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

void	philosopher_init(t_philosopher *philosopher, size_t num, t_fork	*right, t_fork *left)
{
	philosopher->num = num;
	if (right->priority < left->priority)
	{
		philosopher->first = right;
		philosopher->second = left;
	}
	else
	{
		philosopher->first = left;
		philosopher->second = right;
	}
	philosopher->is_first_locked_by_me = false;
	philosopher->is_second_locked_by_me = false;
}

void	create_table(t_philconfig *cfg)
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
	philosophers = malloc(sizeof(t_philosopher) * cfg->number_of_philosophers);
	i = 0;
	while (i < cfg->number_of_philosophers)
	{
		philosophers[i].cfg = cfg;
		if (i + 1 != cfg->number_of_philosophers)
			philosopher_init(philosophers + i, i + 1, forks + i, forks + i + 1);
		else
			philosopher_init(philosophers + i, i + 1, forks + i, forks);
		i++;
	}
	cfg->philosophers = philosophers;
	cfg->forks = forks;
}

void	configure(t_philconfig *cfg, int argc, char **argv)
{
	cfg->number_of_philosophers = ft_atost(argv[1]);
	cfg->time_to_die = ft_atolld(argv[2]);
	cfg->time_to_eat = ft_atolld(argv[3]);
	cfg->time_to_sleep = ft_atolld(argv[4]);
	cfg->is_someone_dead = false;
	cfg->finally.priority = 0;
	pthread_mutex_init(&cfg->finally.mutex, NULL);
	pthread_mutex_init(&cfg->death_mutex, NULL);
	if (argc == 6)
		cfg->nums_to_eat = ft_atost(argv[5]);
	create_table(cfg);
}

int	main(int argc, char **argv)
{
	t_philconfig	cfg;
	size_t			i;

	if (argc == 5 || argc == 6)
	{
		configure(&cfg, argc, argv);
		i = 0;
		while (i < cfg.number_of_philosophers)
		{
			pthread_create(&cfg.philosophers[i].th, NULL, &philosopher, &cfg.philosophers[i]);
			i++;
		}
		i = 0;
		while (i < cfg.number_of_philosophers)
		{
			pthread_join(cfg.philosophers[i].th, NULL);
			i++;
		}
	}
}