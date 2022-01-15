/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 16:02:30 by erayl             #+#    #+#             */
/*   Updated: 2022/01/15 21:24:46 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

static
void	destroy_table(t_maincfg	*cfg)
{
	size_t	i;
	t_fork	*fork;

	i = 0;
	while (i < cfg->num_of_phils)
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
void	philosopher_init(t_phil *philosopher,
size_t num, t_maincfg *cfg)
{
	philosopher->right_fork = &cfg->forks[num % cfg->num_of_phils];
	philosopher->left_fork = &cfg->forks[(num + 1) % cfg->num_of_phils];
	philosopher->eat_count = 0;
	philosopher->num = num + 1;
	philosopher->lifecfg = &cfg->lifecfg;
}

static
void	create_table(t_maincfg *cfg)
{
	size_t	i;
	t_fork	*forks;
	t_phil	*philosophers;

	forks = malloc(sizeof(t_fork) * cfg->num_of_phils);
	i = 0;
	while (i < cfg->num_of_phils)
	{
		pthread_mutex_init(&forks[i].mutex, NULL);
		forks[i].priority = i;
		i++;
	}
	cfg->forks = forks;
	philosophers = malloc(sizeof(t_phil) * cfg->num_of_phils);
	i = 0;
	while (i < cfg->num_of_phils)
	{
		philosopher_init(philosophers + i, i, cfg);
		i++;
	}
	cfg->philosophers = philosophers;
}

static
void	configure(t_maincfg *cfg, int argc, char **argv)
{
	cfg->num_of_phils = ft_atost(argv[1]);
	cfg->lifecfg.time_to_die = ft_atoms(argv[2]);
	cfg->lifecfg.time_to_eat = ft_atoms(argv[3]);
	cfg->lifecfg.time_to_sleep = ft_atoms(argv[4]);
	cfg->lifecfg.is_someone_dead = false;
	pthread_mutex_init(&cfg->lifecfg.death_mutex, NULL);
	if (argc == 6)
		cfg->lifecfg.nums_to_eat = ft_atost(argv[5]);
	else
		cfg->lifecfg.nums_to_eat = 0;
	if (!cfg->num_of_phils || !cfg->lifecfg.time_to_die
		|| !cfg->lifecfg.time_to_eat || !cfg->lifecfg.time_to_sleep)
		cfg->lifecfg.is_someone_dead = true;
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
