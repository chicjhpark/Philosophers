/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:22:54 by jaehpark          #+#    #+#             */
/*   Updated: 2021/11/22 02:25:12 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_msg(char *msg)
{
	printf("ERROR : %s\n", msg);
	return (FALSE);
}

int	ft_atoi(char *s)
{
	long long	n;
	int			i;

	i = 0;
	n = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		n = n * 10 + (s[i] - '0');
		i++;
	}
	if (s[i] || n > 2147483647)
		return (FALSE);
	return ((int)n);
}

unsigned long	ft_gettimeofday(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((unsigned long)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

void	ft_usleep(unsigned long ms)
{
	unsigned long	clear;

	clear = ms + ft_gettimeofday();
	while (clear > ft_gettimeofday())
		usleep (200);
}

void	ft_free(t_info *info, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < info->num_of_philos)
		pthread_mutex_destroy(&info->fork[i]);
	pthread_mutex_destroy(&info->print);
	free(info->fork);
	free(philo);
}
