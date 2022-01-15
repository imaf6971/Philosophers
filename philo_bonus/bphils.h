/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bphils.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 22:36:30 by erayl             #+#    #+#             */
/*   Updated: 2022/01/16 01:51:21 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BPHILS_H
# define BPHILS_H
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>
typedef long long	t_ms;
typedef struct s_cfg
{
	t_ms			time_to_die;
	t_ms			time_to_eat;
	t_ms			time_to_sleep;
	size_t			nums_to_eat;
}	t_lifecfg;
typedef struct s_maincfg
{
	size_t		num_of_phils;
	t_lifecfg	lifecfg;
}	t_maincfg;
void	philosopher(void *);
#endif