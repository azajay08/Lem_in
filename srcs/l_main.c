/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:19:09 by ajones            #+#    #+#             */
/*   Updated: 2022/12/16 17:47:27 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	print_usage(t_data *data)
{
	ft_putstr("\nUsage: ./lem-in -[flag] < [map]\n");
	ft_putstr("\nFlags:\n");
	ft_putstr("\t-h\thelp - shows usage and flag options\n");
	ft_putstr("\t-p\tpaths - prints path route(s)\n");
	ft_putstr("\t-q\tquiet mode - does not print map\n");
	ft_putstr("\t-t\tturns - prints the number of turns\n");
	ft_putstr("\nVisualizer usage: ./lem-in < [map] | ");
	ft_putstr("python3 visualizer/lem_in_vis.py\n\n");
	free(data);
	exit(0);
}

void	activate_modes(t_data *data, char flag)
{
	if (flag == 'h')
		print_usage(data);
	else if (flag == 'q')
		data->q_mode = ON;
	else if (flag == 'p')
		data->p_mode = ON;
	else if (flag == 't')
		data->t_mode = ON;
	else
		print_usage(data);
}

void	read_flags(t_data *data, int ac, char **argv)
{
	int	i;

	i = 0;
	if (ac == 2 && argv[1][i++] == '-')
	{
		if (argv[1][i] && ft_strchr("qpht", argv[1][i]))
		{
			while (argv[1][i])
			{
				activate_modes(data, argv[1][i]);
				i++;
			}
		}
		else
			print_usage(data);
	}
	else
		print_usage(data);
}

int	main(int ac, char **argv)
{
	t_data	*data;
	t_opt	*option;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		error_exit(DATA_FAIL);
	init_data(data);
	if (ac > 1)
		read_flags(data, ac, argv);
	read_input(data);
	//system("leaks lem-in");
	option = solver(data);
	system("leaks lem-in");
	print_output(data, option);
	//system("leaks lem-in");
	free_all(data, SUCCESS);
	//system("leaks lem-in");
	return (0);
}
