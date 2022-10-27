/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_read_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:04:45 by ajones            #+#    #+#             */
/*   Updated: 2022/10/27 16:05:24 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	get_room_info(char *line, t_verify *verify)
{

	if (data->start == 1)
	{
		deal_with_start();
		data->start = 0;
	}
	else
		deal_with_rooms(); 
	while (ft_strchr(line) != ft_strrchr(line))//check if there are two spaces
	{
		save_room_info(line, data);	//example
		ft_strdel(&line);
		if (ft_strchr(line, '-')
			get_link_info(line, data);
		data->nb_rooms++;
	}
}