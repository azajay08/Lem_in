/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:19:09 by ajones            #+#    #+#             */
/*   Updated: 2022/12/13 02:33:27 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include <stdio.h>

void	print_usage(t_data *data)
{
	ft_putstr("\nUsage: ./lem-in -[flag] < [map]\n");
	ft_putstr("\nFlags:\n");
	ft_putstr("\t-h\thelp - shows usage and flag options\n");
	ft_putstr("\t-q\tquiet mode - only prints moves\n");
	ft_putstr("\t-p\tpaths - prints path route(s)\n\n");
	ft_putstr("\t-t\tturns - prints the number of turns\n\n");	
	ft_putstr("\nVisualizer usage: ./lem-in < [map] | ");
	ft_putstr("python3 visualizer/lem_in_vis.py\n\n");
	free(data);
	exit(0);
}

void	read_flags(t_data *data, int ac, char **argv)
{
	int	i;

	i = 1;
	if (ac == 2)
	{
		while (argv[1][i] && ft_strchr("qpht", argv[1][i]))
		{
			if (argv[1][i] ==  'h')
				print_usage(data);
			if (argv[1][i] ==  'q')
				data->q_mode = ON;
			if (argv[1][i] ==  'p')
				data->p_mode = ON;
			if (argv[1][i] ==  't')
				data->t_mode = ON;
			i++;
		}
	}
	else
		print_usage(data);
}

int	main(int ac, char **argv)
{
	t_data		*data;
	t_option	*option;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		error_exit(DATA_FAIL);
	init_data(data);
	if (ac > 1)
		read_flags(data, ac, argv);
	read_input(data);

	// check error inputs and exit properly
	// can also take the check to another fucntion
	// read input if all is okay
	option = solver(data);
	//print the solution here?
	printf("\ntesting %i\n", option->path->index);
	free_all(data, SUCCESS);
	return (0);
}
