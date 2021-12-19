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

t_philosopher	*phil_list(t_philconfig *cfg)
{
	size_t i;
	t_philosopher	*start;
	t_philosopher	*phil;

	start = malloc(sizeof(t_philosopher));
	phil = start;
	i = 0;
	while(i < cfg->number_of_philosophers)
	{
		phil->num = i + 1;
		phil->cfg = cfg;
		phil->is_alive = true;
		if (i + 1 != cfg->number_of_philosophers)
		{
			phil->next = malloc(sizeof(t_philosopher));
			phil = phil->next;
		}
		else
			phil->next = NULL;
		i++;
	}
	return (start);
}

void	configure(t_philconfig *cfg, int argc, char **argv)
{
	cfg->number_of_philosophers = ft_atoul(argv[1]);
	cfg->time_to_die = ft_atoul(argv[2]);
	cfg->time_to_eat = ft_atoul(argv[3]);
	cfg->time_to_sleep = ft_atoul(argv[4]);
	if (argc == 6)
		cfg->nums_to_eat = ft_atoul(argv[5]);
	cfg->phil_list = phil_list(cfg);
}

int	main(int argc, char **argv)
{
	t_philconfig	cfg;
	t_philosopher	*pi;

	if (argc == 5 || argc == 6)
	{
		configure(&cfg, argc, argv);
		pi = cfg.phil_list;
		while (pi)
		{
			pthread_create(&pi->pt, NULL, &philosopher, pi);
			pi = pi->next;
		}
		pi = cfg.phil_list;
		while (pi)
		{
			pthread_join(pi->pt, NULL);
			pi = pi->next;
		}
	}
}