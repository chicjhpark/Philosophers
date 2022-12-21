/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 21:46:51 by jaehpark          #+#    #+#             */
/*   Updated: 2021/11/22 02:33:50 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_print(t_info *info, t_philo *philo, int action)
{
	unsigned long	now;

	pthread_mutex_lock(&info->print);
	now = ft_gettimeofday() - info->start;
	if (info->all_alive == TRUE && action == FORK)
		printf("%lums %d has taken a fork\n", now, philo->num);
	else if (info->all_alive == TRUE && action == EAT)
		printf("%lums %d is eating\n", now, philo->num);
	else if (info->all_alive == TRUE && action == SLEEP)
		printf("%lums %d is sleeping\n", now, philo->num);
	else if (info->all_alive == TRUE && action == THINK)
		printf("%lums %d is thinking\n", now, philo->num);
	else if (action == DIE && info->check_die == TRUE)
	{
		printf("%lums %d died\n", now, philo->num);
		info->check_die = FALSE;
	}
	pthread_mutex_unlock(&info->print);
}

void	handle_action(t_info *info, t_philo *philo, int r_fork, int l_fork)
{
	if ((philo->num % 2 == 1 && pthread_mutex_lock(&info->fork[r_fork]) == 0)
		|| pthread_mutex_lock(&info->fork[l_fork]) == 0)
		handle_print(info, philo, FORK);
	if ((philo->num % 2 == 1 && pthread_mutex_lock(&info->fork[l_fork]) == 0)
		|| pthread_mutex_lock(&info->fork[r_fork]) == 0)
		handle_print(info, philo, FORK);
	handle_print(info, philo, EAT);
	philo->eat = ft_gettimeofday();
	ft_usleep(info->time_to_eat);
	pthread_mutex_unlock(&info->fork[r_fork]);
	pthread_mutex_unlock(&info->fork[l_fork]);
	philo->eat_num++;
	if (philo->eat_num == info->num_of_must_eat)
		return ;
	handle_print(info, philo, SLEEP);
	ft_usleep(info->time_to_sleep);
	handle_print(info, philo, THINK);
}

void	*handle_state(void *arg)
{
	t_philo	*philo;
	t_info	*info;
	int		i;

	philo = (t_philo *)arg;
	info = (t_info *)philo->info;
	while (1)
	{
		i = -1;
		while (++i < info->num_of_philos)
		{
			if (philo[i].eat_num == info->num_of_must_eat)
				return (NULL);
			if (ft_gettimeofday() - philo[i].eat > info->time_to_die)
			{
				info->all_alive = FALSE;
				if (i == 0)
					pthread_mutex_unlock(&info->fork[philo[i].r_fork]);
				handle_print(info, &philo[i], DIE);
				return (NULL);
			}
		}
		usleep(20);
	}
}

void	*handle_loop(void *arg)
{
	t_philo		*philo;
	t_info		*info;

	philo = (t_philo *)arg;
	info = (t_info *)philo->info;
	if (philo->num % 2 == 0)
		ft_usleep(info->time_to_eat - 1);
	while (1)
	{
		if (info->all_alive == FALSE)
			break ;
		handle_action(info, philo, philo->r_fork, philo->l_fork);
		if (info->num_of_must_eat == philo->eat_num)
			break ;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	*philo;

	if (argc != 5 && argc != 6)
		return (error_msg("Invalid format!"));
	if (init_info(argc, argv, &info) == FALSE)
		return (error_msg("Invalid number!"));
	if (init_philo(&info, &philo) == FALSE)
		return (error_msg("Failed malloc!"));
	init_table(&info, philo);
	ft_free(&info, philo);
	return (0);
}
