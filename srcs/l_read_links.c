/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_read_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:06:41 by ajones            #+#    #+#             */
/*   Updated: 2022/11/26 18:09:56 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_edge	*append_edge(t_vert *room)
{
	t_edge	*new_edge;

	new_edge = (t_edge *)malloc(sizeof(t_edge));
	if (!new_edge)
		return (NULL);
	new_edge->room = room->index;
	new_edge->on_off = ON;
	new_edge->next = NULL;
	new_edge->head = NULL;
	return (new_edge);
}

int	assign_link(char *link_to, t_vert *curr_room, t_vert *head)
{
	t_vert	*room;

	room = head;
	room = find_room_name(room, link_to);
	if (!curr_room->edge)
	{
		curr_room->edge = append_edge(room);
		curr_room->edge->head = curr_room->edge;
	}
	else
	{
		while (curr_room->edge->next)
			curr_room->edge = curr_room->edge->next;
		curr_room->edge->next = append_edge(room);
		curr_room->edge->next->head = curr_room->edge->head;
		curr_room->edge = curr_room->edge->next;
	}
	curr_room->edge = curr_room->edge->head;
	return (1);
}

int	verify_and_assign_names(char *line, t_vert *start)
{
	char	**temp;
	t_vert	*room;
	int		counter;
	int		counter2;

	counter = 0;
	counter2 = 0;
	room = start;
	temp = ft_strsplit(line, '-');
	if (!temp)
		return (0);
	while (room != NULL)
	{
		if (ft_strequ(temp[0], room->name))
			counter += assign_link(temp[1], room, start);
		if (ft_strequ(temp[1], room->name))
			counter2 += assign_link(temp[0], room, start);
		room = room->next;
	}
	ft_2d_free(temp);
	if (counter != 1 || counter2 != 1)
		return (0);
	return (1);
}

int	save_link_info(char *line, t_vert *start, t_verify *verify)
{
	if (ft_strchr(line, '-') != ft_strrchr(line, '-'))
	{
		//ft_strdel(&line);
		return (0);
	}
	if (verify->ants)
	{
		if (!verify_and_assign_names(line, start))
		{
			return (0);
		}
	}
	return (1);
}

void	get_link_info(char *line, t_verify *verify, t_data *data)
{
	int		ret;
	t_vert	*start;

	start = data->source;
	ret = 1;
	while (ret == 1)
	{
		if (data->q_mode == OFF)
			data->line = ft_strjoin_line(data->line, line);
		if (ret == -1)
			error_exit2(GNL_FAIL, data, verify);
		start = data->source;
		if (line[0] == '#')
			comment_found(line, verify, data);
		else if (ft_strchr(line, ' '))
			error_exit3(ROOM_FAIL, verify, data, start);
		else if (!save_link_info(line, start, verify))
			error_exit3(LINK_FAIL, verify, data, start);
		ft_strdel(&line);
		ret = get_next_line(0, &line);
	}
	ft_strdel(&line);
}
