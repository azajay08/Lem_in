/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_read_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:04:45 by ajones            #+#    #+#             */
/*   Updated: 2022/12/15 15:23:17 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	check_dups(t_vert *head, t_vert *curr_room)
{
	t_vert	*temp;

	temp = head;
	while (temp != NULL)
	{
		if (curr_room->coord_x == temp->coord_x
			&& curr_room->coord_y == temp->coord_y)
			return (0);
		if (ft_strequ(curr_room->name, temp->name))
			return (0);
		temp = temp->next;
	}
	return (1);
}

void	set_start_end(t_data *data, t_vert *new_room, t_verify *verify)
{
	if (verify->start == ON)
	{
		new_room->start = ON;
		data->src_index = new_room->index;
	}
	else if (verify->end == ON)
	{
		new_room->end = ON;
		data->sink_index = new_room->index;
	}
}

t_vert	*make_room(char *line, t_verify *verify, t_data *data)
{
	t_vert	*new_room;
	char	**temp;

	temp = ft_strsplit(line, ' ');
	if (!temp || !check_line_is_digits(temp[1])
		|| !check_line_is_digits(temp[2]) || temp[3])
		error_exit2(COORD_FAIL, data, verify);
	new_room = (t_vert *)malloc(sizeof(t_vert));
	if (!new_room)
		error_exit2(VERT_FAIL, data, verify);
	init_vert(new_room);
	new_room->name = ft_strdup(temp[0]);
	new_room->coord_x = ft_atoi(temp[1]);
	new_room->coord_y = ft_atoi(temp[2]);
	new_room->next = NULL;
	ft_2d_free(temp);
	new_room->index = data->nb_rooms;
	if (!check_dups(data->source, new_room))
		error_exit2(DUPLICATE, data, verify);
	if (verify->start == ON || verify->end == ON)
		set_start_end(data, new_room, verify);
	return (new_room);
}

t_vert	*get_vert_info(char *line, t_verify *verify, t_data *data, t_vert *room)
{
	t_vert	*new_room;

	new_room = make_room(line, verify, data);
	if (!room)
	{
		data->source = new_room;
		room = new_room;
	}
	else
	{
		room->next = new_room;
		room = room->next;
	}
	verify->start = OFF;
	verify->end = OFF;
	data->nb_rooms++;
	return (room);
}
