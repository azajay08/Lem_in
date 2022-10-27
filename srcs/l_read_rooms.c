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
	t_room	*new_room;

	new_room = (t_room *)malloc(sizeof(t_room));
	if (!new_room)
		error_handling(MALLOC_ERROR);
	init_t_room(new_room);
	deal_with_rooms();
	if (data->start == 1)
	{
		add_start_to_the_beginning_of_the_list(new_room, rooms);
		data->start = 0;
	}
	/*while (ft_strchr(line, ' ') != ft_strrchr(line, ' '))//check if there are two spaces
	{
		save_room_info(line, data);	//example
		ft_strdel(&line);
		if (ft_strchr(line, '-'))
			get_link_info(line, data);
		data->nb_rooms++;
	}*/
}