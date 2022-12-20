/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_room_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 20:14:04 by ajones            #+#    #+#             */
/*   Updated: 2022/12/20 15:09:35 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_edge	*make_edge(t_edge *head)
{
	t_edge	*new_edge;
	int		i;

	i = head->room;
	new_edge = (t_edge *)malloc(sizeof(t_edge));
	if (!new_edge)
		return (NULL);
	new_edge->room = i;
	new_edge->next = NULL;
	new_edge->head = NULL;
	new_edge->on_off = ON;
	return (new_edge);
}

t_edge	*make_new_edge(t_room *room, t_edge *head, t_edge *edge)
{
	t_edge	*new_edge;

	while (head)
	{
		new_edge = make_edge(head);
		if (!new_edge)
			return (NULL);
		if (!edge)
		{
			room->edge = new_edge;
			edge = new_edge;
		}
		else
		{
			edge->next = new_edge;
			edge = edge->next;
		}
		head = head->next;
	}
	return (edge);
}

t_room	*make_index_room(t_vert *head, t_room *new_room, int index)
{
	t_edge	*new_edge;

	new_room = (t_room *)malloc(sizeof(t_room));
	if (!new_room)
		return (NULL);
	new_edge = NULL;
	init_room(new_room);
	new_room->index = index;
	new_room->name = ft_strdup(head->name);
	new_room->start = head->start;
	new_room->end = head->end;
	if (head->edge)
	{
		new_edge = make_new_edge(new_room, head->edge, new_edge);
		if (!new_edge)
			return (NULL);
	}
	return (new_room);
}

void	fill_room_array(t_data *data, t_room **room, t_vert *head, int i)
{
	while (i < data->nb_rooms)
	{
		room[i] = make_index_room(head, *room, i);
		if (!room[i])
		{
			i = 0;
			while (i < data->rooms_malloced)
			{
				free(room[i]->name);
				free(room[i]);
				i++;
			}
			free(room);
			free_all(data, ERROR);
			error_exit(T_ROOM_FAIL);
		}
		head = head->next;
		i++;
		data->rooms_malloced++;
	}
}

t_room	**make_room_array(t_data *data)
{
	t_vert	*head;
	t_room	**room;
	int		i;

	head = data->source;
	i = 0;
	room = (t_room **)malloc(sizeof(t_room *) * (data->nb_rooms));
	if (!room)
	{
		free_all(data, ERROR);
		error_exit(T_ROOM_FAIL);
	}
	else
		fill_room_array(data, room, head, i);
	free_vert(data);
	return (room);
}
