/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:16:11 by cmariot           #+#    #+#             */
/*   Updated: 2021/11/26 22:19:29 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// Wait the end of all the threads to continue,
// The main program will not stop until all the threads are closed
void	wait_threads(pthread_t *thread_id, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_join(thread_id[i], NULL);
		i++;
	}
	return ;
}

// Create a thread for each philosopher and launch the routine() in the threads
int	create_threads(t_rules *rules)
{
	pthread_t	*thread_id;
	int			i;

	thread_id = malloc(sizeof(pthread_t) * rules->nb_philo);
	if (!thread_id)
		return (print_error("Error, malloc in create_threads() failed\n"));
	rules->init_time = get_time();
	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_create(&thread_id[i], NULL, &routine, &rules->philo[i]))
			return (print_error("Error, pthread_create() failed\n"));
		rules->philo[i].last_meal = get_time();
		i++;
	}
	usleep(100);
	check_end(rules);
	wait_threads(thread_id, rules);
	clean_exit(rules, thread_id);
	return (0);
}