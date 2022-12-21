/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 21:47:13 by jaehpark          #+#    #+#             */
/*   Updated: 2021/11/07 11:02:17 by jaehpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define TRUE	0
# define FALSE	-1
# define FORK	1
# define EAT	2
# define SLEEP	3
# define THINK	4
# define DIE	5

typedef struct s_info
{
	int				num_of_philos;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				num_of_must_eat;
	unsigned long	start;
	int				all_alive;
	int				check_die;
	pthread_mutex_t	print;
	pthread_mutex_t	*fork;
}					t_info;

typedef struct s_philo
{
	int				num;
	unsigned long	eat;
	int				eat_num;
	int				l_fork;
	int				r_fork;
	pthread_t		thread;
	t_info			*info;
}					t_philo;

int				error_msg(char *msg);
int				ft_atoi(char *s);
unsigned long	ft_gettimeofday(void);
void			ft_usleep(unsigned long ms);
void			ft_free(t_info *info, t_philo *philo);
int				init_info(int argc, char **argv, t_info *info);
int				init_philo(t_info *info, t_philo **philo);
void			init_table(t_info *info, t_philo *philo);
void			*handle_loop(void *arg);
void			*handle_state(void *arg);

#endif
