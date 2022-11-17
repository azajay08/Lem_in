/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_read_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:04:45 by ajones            #+#    #+#             */
/*   Updated: 2022/11/08 20:10:29 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	arrange_source_or_sink(t_room *new_room, t_data *data, t_verify *verify)
{
	t_room	*temp;

	temp = data->source;
	if (verify->start == ON)
	{
		new_room->next = temp;
		data->source = new_room;
		verify->start = OFF;
	}
	else if (verify->end == ON)
	{
		data->sink = new_room;
		verify->end = OFF;
	}
}
/*
	When we get a room that is marked with ##start or ##end,
	this function is called.
	arrange_source_or_sink puts the ##start-room to the beginning of the list,
	or just marks the ##end-room for arrange_sink -function
	to do the work when all rooms have been read.
*/

t_room	*make_room(char *line, t_verify *verify, t_data *data)
{
	t_room	*new_room;
	char	**temp;

	temp = ft_strsplit(line, ' ');
	if (!temp || !check_if_line_is_digits(temp[1])
		|| !check_if_line_is_digits(temp[2]) || temp[3])
		error_exit2(COORD_FAIL, data, verify);//Also return (NULL);
	new_room = (t_room *)malloc(sizeof(t_room));
	if (!new_room)
		error_exit2(T_ROOM_FAIL, data, verify);//Also return (NULL);
	init_room(new_room);
	new_room->name = ft_strdup(temp[0]);
	new_room->coord_x = ft_atoi(temp[1]);
	new_room->coord_y = ft_atoi(temp[2]);
	if (verify->start == ON)
		new_room->start = ON;
	else if (verify->end == ON)
		new_room->end = ON;
	ft_2d_free(temp);
	return (new_room);
}
/*
	make_room -function verifies the coordinates and
	allocates memory to the struct.
	This is where the room-struct is initialized.
*/

t_room	*get_room_info(char *line, t_verify *verify, t_data *data, t_room *room)
{
	t_room	*new_room;

	if (!room)
	{
		new_room = make_room(line, verify, data);
		data->source = new_room;
		if (verify->start == ON || verify->end == ON)
			arrange_source_or_sink(new_room, data, verify);
	}
	else
	{
		new_room = make_room(line, verify, data);
		if (verify->start == ON || verify->end == ON)
			arrange_source_or_sink(new_room, data, verify);
		else
		{
			room->next = new_room;
			room = room->next;
		}
	}
	return (room);
}
/*
	Here we make the list.
*/
