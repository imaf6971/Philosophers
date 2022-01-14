/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 19:59:53 by erayl             #+#    #+#             */
/*   Updated: 2022/01/14 20:03:14 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

void	create_threads(t_maincfg *cfg)
{
	size_t	i;

	i = 0;
	while (i < cfg->number_of_philosophers)
	{
		pthread_create(&cfg->philosophers[i].th, NULL,
			&philosopher, &cfg->philosophers[i]);
		i++;
	}
}

void	wait_for_threads(t_maincfg *cfg)
{
	size_t	i;

	i = 0;
	while (i < cfg->number_of_philosophers)
	{
		pthread_join(cfg->philosophers[i].th, NULL);
		i++;
	}
}
