/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saylital <saylital@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:39:02 by saylital          #+#    #+#             */
/*   Updated: 2024/10/31 15:06:10 by saylital         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//argv[1] = number of philos
//argv[2] = time it will take them to die
//argv[3] = time it will take them to eat
//argv[4] = time it will take them to sleep
//argv[5] = (optional) If all philosophers have eaten at least 
			//number_of_times_each_philosopher_must_eat times, 
			//the simulation stops. If not specified, the simulation stops
			//when a philosopher dies.
#include "philo.h"

int	check_input(char *argv[])
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		if (argv[i][j] == '-' || argv[i][j] == '0')
		{
			printf("first\n");
			return (1);
		}
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("{%c}\n", argv[i][j]);
				printf("second\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	if (argc < 2 || argc > 6)
	{
		printf("Incorrect amount of arguments.\n");
		return (1);
	}
	if (check_input(&argv[1]) == 1)
	{
		printf("Incorrect input\n");
		return (1);
	}
	return (0);
}