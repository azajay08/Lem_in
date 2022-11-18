/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_read_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:04:45 by ajones            #+#    #+#             */
/*   Updated: 2022/11/18 20:40:34 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	arrange_source_or_sink(t_vert *new_room, t_data *data, t_verify *verify)
{
	t_vert	*temp;

	temp = data->source;
	if (verify->start == ON)
	{
		new_room->next = temp;
		data->source = new_room;
		verify->start = OFF;
	}
	else if (verify->end == ON)
	{
		verify->end = OFF;
	}
}

t_vert	*make_room(char *line, t_verify *verify, t_data *data)
{
	t_vert	*new_room;
	char	**temp;

	temp = ft_strsplit(line, ' ');
	if (!temp || !check_if_line_is_digits(temp[1])
		|| !check_if_line_is_digits(temp[2]) || temp[3])
		error_exit2(COORD_FAIL, data, verify);
	new_room = (t_vert *)malloc(sizeof(t_vert));
	if (!new_room)
		error_exit2(VERT_FAIL, data, verify);
	init_vert(new_room);
	new_room->name = ft_strdup(temp[0]);
	new_room->coord_x = ft_atoi(temp[1]);
	new_room->coord_y = ft_atoi(temp[2]);
	new_room->index = data->nb_rooms;
	data->nb_rooms++;
	if (verify->start == ON)
		new_room->start = ON;
	else if (verify->end == ON)
	{
		new_room->end = ON;
		data->sink_index = new_room->index;
	}
	ft_2d_free(temp);
	return (new_room);
}

t_vert	*get_vert_info(char *line, t_verify *verify, t_data *data, t_vert *room)
{
	t_vert	*new_room;

	if (!room)
	{
		new_room = make_room(line, verify, data);
		data->source = new_room;
		if (verify->start == ON || verify->end == ON)
			arrange_source_or_sink(new_room, data, verify);
		room = new_room;
	}
	else
	{
		new_room = make_room(line, verify, data);
		if (verify->start == ON)
			arrange_source_or_sink(new_room, data, verify);
		else
		{
			if (verify->end == ON)
				arrange_source_or_sink(new_room, data, verify);
			room->next = new_room;
			room = room->next;
		}
	}
	return (room);
}
