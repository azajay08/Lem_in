/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:19:09 by ajones            #+#    #+#             */
/*   Updated: 2022/11/23 19:44:03 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	print_usage(t_data *data)
{
	ft_putstr("\nUsage: ./lem-in -[flag] < [map]\n");
	ft_putstr("\nFlags:\n");
	ft_putstr("\t-h\thelp - shows usage and flag options\n");
	ft_putstr("\t-q\tquiet mode - only prints moves\n");
	ft_putstr("\t-p\tpaths - prints path route(s)\n\n");
	ft_putstr("\nVisualizer usage: ./lem-in < [map] | ");
	ft_putstr("python3 visualizer/lem_in_vis.py\n\n");
	free(data);
	exit(0);
}

void	read_flags(t_data *data, int ac, char **argv)
{
	if (ac == 2)
	{
		if (ft_strequ(argv[1], "-q"))
			data->q_mode = ON;
		else if (ft_strequ(argv[1], "-p"))
			data->p_mode = ON;
		else
			print_usage(data);
	}
	else
		print_usage(data);
}

int	main(int ac, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		error_exit(DATA_FAIL);
	init_data(data);
	if (ac > 1)
		read_flags(data, ac, argv);
	read_input(data);
	// DO WE NEED TO PARSE SOMETHING ELSE,
	// so that we could send that to the solver?
	// That way we could make another struct here

	// check error inputs and exit properly
	// can also take the check to another fucntion
	// read input if all is okay
	solver(data);
	//print the solution here?
	free_all(data);
	return (0);
}
