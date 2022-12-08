/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_printing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 21:22:20 by ajones            #+#    #+#             */
/*   Updated: 2022/12/08 14:00:24 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	print_ant_move(t_data *data, int num, int index)
{
	t_room	**room;

	room = data->room;
	write(1, "L", 1);
	ft_putnbr(num);
	write(1, "-", 1);
	ft_putstr(room[index]->name);
	write(1, " ", 1);
}

void	move_ants(t_data *data, t_ant *ant)
{
	print_ant_move(data, ant->ant_num, ant->head->index);
	ant->head = ant->head->next;
	if (!ant->head)
	{
		data->ants_in_sink++;
		ant->finished = YES;
	}
}

void	launch_ants(int i, t_data *data, t_ant *ant, t_option *opt)
{
	while (i < data->nb_paths)
	{
		print_ant_move(data, ant->ant_num, ant->head->index);
		if (opt->used > 0)
		{
			opt->used--;
			opt->limit++;
			if (opt->used == 0)
				data->nb_paths--;
		}
		opt = opt->next;
		ant->head = ant->head->next;
		ant->launched = YES;
		ant = ant->next;
		i++;
	}
}

void	print_moves(t_data *data, t_option *opt, t_option *head, t_ant *ant)
{
	int	i;

	write(1, "\n", 1);
	while (data->ants_in_sink < data->nb_ants)
	{
		write(1, "\n", 1);
		ant = data->queen;
		while (ant != NULL)
		{
			i = 0;
			if (ant->launched == NO)
			{
				opt = head;
				launch_ants(i, data, ant, opt);
				break ;
			}
			if (ant->finished == NO && ant->launched == YES)
				move_ants(data, ant);
			ant = ant->next;
		}
	}
	write(1, "\n", 1);
}

void	print_output(t_data *data, t_option *option)
{
	t_option	*head;
	t_ant		*ant;
	int			p_tmp;

	p_tmp = data->nb_paths;
	option = get_option_head(option);
	head = option;
	make_ant_army(data, option);
	ant = data->queen;
	data->nb_paths = p_tmp;
	if (data->q_mode == OFF)
		ft_putstr(data->line);
	print_moves(data, option, head, ant);
	option = get_option_head(option);
	if (data->p_mode == ON)
	{
		print_paths(data, option);
		write(1, "\n", 1);
	}
}
