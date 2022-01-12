/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erayl <erayl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 16:36:03 by erayl             #+#    #+#             */
/*   Updated: 2022/01/12 17:25:22 by erayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

static
long long	system_time(void)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (milliseconds);
}

long long	current_timestamp(void)
{
	static long long	start_time;

	if (start_time == 0)
		start_time = system_time();
	return (system_time() - start_time);
}

void	wwwait(long long time_to_wait)
{
	long long	initial_time;

	initial_time = current_timestamp();
	while (current_timestamp() - initial_time < time_to_wait)
		usleep(500);
}
