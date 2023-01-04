/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_printing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 21:22:20 by ajones            #+#    #+#             */
/*   Updated: 2023/01/05 01:09:57 by ajones           ###   ########.fr       */
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
	ant->head = ant->head->next;
	if (!ant->head)
	{
		data->ants_in_sink++;
		ant->finished = YES;
	}
}

void	launch_ants(int i, t_data *data, t_ant *ant, t_opt *opt)
{
	int	reduce;

	reduce = OFF;
	while (i < data->nb_paths)
	{
		print_ant_move(data, ant->ant_num, ant->head->index);
		if (opt->used > 0)
		{
			opt->used--;
			if (opt->used == 0)
				reduce++;
		}
		if (opt->p_len > 1)
			i++;
		if (opt->next)
			opt = opt->next;
		move_ants(data, ant);
		ant->launched = YES;
		ant = ant->next;
		if (!ant)
			break ;
	}
	if (reduce)
		data->nb_paths -= reduce;
}

void	print_moves(t_data *data, t_opt *opt, t_opt *head, t_ant *ant)
{
	int	i;

	while (data->ants_in_sink < data->nb_ants)
	{
		write(1, "\n", 1);
		data->turns++;
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
			{
				print_ant_move(data, ant->ant_num, ant->head->index);
				move_ants(data, ant);
			}
			ant = ant->next;
		}
	}
	write(1, "\n", 1);
}

void	print_output(t_data *data, t_opt *option)
{
	t_opt	*head;
	t_ant	*ant;
	int		p_tmp;

	p_tmp = data->nb_paths;
	option = get_opt_head(option);
	head = option;
	make_ant_army(data, option);
	ant = data->queen;
	data->nb_paths = p_tmp;
	if (data->q_mode == OFF)
	{
		ft_putstr(data->line);
		write(1, "\n", 1);
	}
	print_moves(data, option, head, ant);
	option = get_opt_head(option);
	if (data->t_mode == ON || data->p_mode == ON)
		print_flag_modes(data, option, p_tmp);
	free_option(option);
	free_ants(data);
}

/*
	In the printing, using the data we get from the solver, we make a list of
	ants. After the ant army has been made, we check what flag modes have been 
	activated, so we can decide what needs to be printed. Then we will loop
	through the ants printing their moves at which ever point they are at.
*/