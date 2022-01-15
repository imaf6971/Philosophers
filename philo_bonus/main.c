/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 22:38:18 by erayl             #+#    #+#             */
/*   Updated: 2022/01/16 01:52:21 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bphils.h"
#include <string.h>

static
void	configure(t_maincfg *cfg, int argc, char **argv)
{
	cfg->num_of_phils = ft_atost(argv[1]);
	cfg->lifecfg.time_to_die = ft_atoms(argv[2]);
	cfg->lifecfg.time_to_eat = ft_atoms(argv[3]);
	cfg->lifecfg.time_to_sleep = ft_atoms(argv[4]);
	if (argc == 6)
		cfg->lifecfg.nums_to_eat = ft_atost(argv[5]);
	else
		cfg->lifecfg.nums_to_eat = 0;
	if (!cfg->num_of_phils || !cfg->lifecfg.time_to_die
		|| !cfg->lifecfg.time_to_eat || !cfg->lifecfg.time_to_sleep)
		exit(1);
	create_table(cfg);
}

int main(int argc, char const *argv[])
{
	
	return 0;
}

