/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_read_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:04:45 by ajones            #+#    #+#             */
/*   Updated: 2022/11/17 23:01:45 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	arrange_source_or_sink(t_vertex *new_room, t_data *data, t_verify *verify)
{
	t_vertex	*temp;

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

t_vertex	*make_room(char *line, t_verify *verify, t_data *data)
{
	t_vertex	*new_room;
	char	**temp;

	temp = ft_strsplit(line, ' ');
	if (!temp || !check_if_line_is_digits(temp[1])
		|| !check_if_line_is_digits(temp[2]) || temp[3])
		error_exit2(COORD_FAIL, data, verify);//Also return (NULL);
	new_room = (t_vertex *)malloc(sizeof(t_vertex));
	if (!new_room)
		error_exit2(VERTEX_FAIL, data, verify);//Also return (NULL);
	init_vertex(new_room);
	new_room->name = ft_strdup(temp[0]);
	new_room->coord_x = ft_atoi(temp[1]);
	new_room->coord_y = ft_atoi(temp[2]);
	new_room->index = data->nb_rooms;
	data->nb_rooms++;
	if (verify->start == ON)
		new_room->start = ON;
	else if (verify->end == ON)
		new_room->end = ON;
	//ft_2d_free(temp);
	return (new_room);
}

t_vertex	*get_vertex_info(char *line, t_verify *verify, t_data *data, t_vertex *room)
{
	t_vertex	*new_room;

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

