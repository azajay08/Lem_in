/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_printing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 21:22:20 by ajones            #+#    #+#             */
/*   Updated: 2022/12/05 23:44:25 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	print_paths(t_data *data, t_option *option)
{

	
}

void	print_moves(t_data *data, t_option *option)
{
	
	
}

void	print_output(t_data *data, t_option *option)
{
	t_option	*head;
	t_ant		*ant;
	int			p_tmp;
	
	p_tmp = data->nb_paths;
	if (data->q_mode == ON)
		ft_putstr(data->line);
	option = get_option_head(option);
	head = option;
	make_ant_army(data, option);
	ant = data->queen;
	data->nb_paths = p_tmp;
	print_moves(data, option);
	if (data->p_mode == ON)
		print_paths(data, option);
	

}