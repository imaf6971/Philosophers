/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 17:18:04 by erayl             #+#    #+#             */
/*   Updated: 2021/12/19 20:06:48 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILS_H
# define PHILS_H
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <printf.h>
#include <stdbool.h>
typedef struct s_phil
{
	pthread_t		pt;
	struct s_cfg	*cfg;
	unsigned long	num;
	struct s_phil	*next;
	bool			is_alive;
}	t_philosopher;
typedef struct s_cfg
{
	size_t	number_of_philosophers;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	nums_to_eat;
	t_philosopher	*phil_list;
}	t_philconfig;



unsigned long	ft_atoul(const char *s);
void	*philosopher(void *param);
#endif