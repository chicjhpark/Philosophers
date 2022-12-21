/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:38:34 by jaehpark          #+#    #+#             */
/*   Updated: 2021/11/07 16:11:15 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_info(int argc, char **argv, t_info *info)
{
	int			i;
	long long	temp;

	memset(info, 0, sizeof(t_info));
	info->num_of_must_eat = -1;
	i = 0;
	while (++i < argc)
	{
		temp = ft_atoi(argv[i]);
		if (temp == FALSE)
			return (FALSE);
		else if (i == 1)
			info->num_of_philos = temp;
		else if (i == 2)
			info->time_to_die = (unsigned long)temp;
		else if (i == 3)
			info->time_to_eat = (unsigned long)temp;
		else if (i == 4)
			info->time_to_sleep = (unsigned long)temp;
		else if (i == 5)
			info->num_of_must_eat = temp;
	}
	pthread_mutex_init(&info->print, NULL);
	info->start = ft_gettimeofday();
	return (TRUE);
}

int	init_philo(t_info *info, t_philo **philo)
{
	int	i;

	*philo = (t_philo *)malloc(sizeof(t_philo) * info->num_of_philos);
	if (*philo == 0)
		return (FALSE);
	info->fork = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * info->num_of_philos);
	if (info->fork == 0)
	{
		free(*philo);
		return (FALSE);
	}
	memset(*philo, 0, sizeof(t_philo) * info->num_of_philos);
	i = -1;
	while (++i < info->num_of_philos)
	{
		pthread_mutex_init(&info->fork[i], NULL);
		(*philo)[i].info = info;
		(*philo)[i].num = i + 1;
		(*philo)[i].r_fork = i;
		(*philo)[i].l_fork = i + 1;
		(*philo)[i].eat = ft_gettimeofday();
	}
	(*philo)[info->num_of_philos - 1].l_fork = 0;
	return (TRUE);
}

void	init_table(t_info *info, t_philo *philo)
{
	pthread_t	state;
	int			i;

	pthread_create(&state, NULL, handle_state, philo);
	i = -1;
	while (++i < info->num_of_philos)
		pthread_create(&philo[i].thread, NULL, handle_loop, &philo[i]);
	pthread_join(state, NULL);
	i = -1;
	while (++i < info->num_of_philos)
		pthread_join(philo[i].thread, NULL);
}
