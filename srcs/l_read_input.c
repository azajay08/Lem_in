/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_read_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:48:59 by ajones            #+#    #+#             */
/*   Updated: 2022/11/17 23:08:49 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_room	*make_index_room(t_vertex *head, t_room *new_room, int index)
{
	t_vertex	*old_room;
	
	new_room = (t_room *)malloc(sizeof(t_room));
	if (!new_room)
		return (NULL);
	init_room(new_room);
	old_room = head;
	old_room = find_room_index(old_room, index);
	new_room->index = index;
	new_room->name = ft_strdup(old_room->name);
	new_room->start = old_room->start;
	new_room->end = old_room->end;
	new_room->edge = old_room->edge;
	return (new_room);
}

void	make_room_array(t_data *data)
{
	t_vertex *head;
	t_room	**room;
	int		i;
	
	head = data->source;
	i = 0;
	room = (t_room **)malloc(sizeof(*room) * (data->nb_rooms));
	while (i < data->nb_rooms)
	{
		room[i] = make_index_room(head, *room, i);
		i++;
	}
	data->room = room;
}

int	verify_all(t_verify *verify, t_data *data)
{
	if (verify->nb_of_starts != 1 || verify->nb_of_ends != 1)
		error_exit2(TOO_MANY, data, verify);
	if (verify->start == ON || verify->end == ON)
		error_exit2(NO_COMMAND, data, verify);
	return (1);
}

void	comment_found(char *line, t_verify *verify)
{
	if (ft_strequ(line, "##start"))
	{
		verify->start = ON;
		verify->nb_of_starts++;
	}
	if (ft_strequ(line, "##end"))
	{
		verify->end = ON;
		verify->nb_of_ends++;
	}
}

void	read_room_and_link_info(char *line, t_verify *verify, t_data *data)
{
	t_vertex	*room;
	int		ret;

	room = NULL;
	while (1)
	{
		ret = get_next_line(0, &line);
		if (ret < 1)
			error_exit3(GNL_FAIL, verify, data, room);
		if (line[0] == '#')
			comment_found(line, verify);
		else if (line[0] == 'L')
			error_exit2(ROOM_FAIL, data, verify);
		else if (!ft_strchr(line, ' '))
			break ;
		else if (verify->all_rooms_read == NOT_READ)
			room = get_vertex_info(line, verify, data, room);
		//ft_strdel(&line);
	}
	get_link_info(line, verify, data);
}

void	read_input(t_data *data)
{
	t_verify	*verify;
	char		*line;

	verify = (t_verify *)malloc(sizeof(t_verify));
	if (!verify)
		error_exit1(VERIFY_FAIL, data);
	init_verify(verify);
	line = NULL;
	get_ant_info(line, data, verify);
	read_room_and_link_info(line, verify, data);
	if (!verify_all(verify, data))
		error_exit2(MAP_ERROR, data, verify);
	make_room_array(data);
}
