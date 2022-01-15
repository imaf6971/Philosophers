/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 16:36:03 by erayl             #+#    #+#             */
/*   Updated: 2022/01/15 19:55:59 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

static
t_ms	system_time(void)
{
	struct timeval	te;
	t_ms			ms;

	gettimeofday(&te, NULL);
	ms = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (ms);
}

t_ms	current_timestamp(void)
{
	static t_ms	start_time;

	if (start_time == 0)
		start_time = system_time();
	return (system_time() - start_time);
}

void	accurate_sleep(t_ms	time_to_wait)
{
	t_ms	initial_time;

	initial_time = current_timestamp();
	while (current_timestamp() - initial_time < time_to_wait)
		usleep(500);
}
