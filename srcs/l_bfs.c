/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_bfs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:39:49 by mtissari          #+#    #+#             */
/*   Updated: 2022/11/22 16:01:00 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_path	*init_path(t_data *data, t_room *room) //atm data is here only for free.
{
	t_path	*path;

	path = (t_path *)malloc(sizeof(t_path));
	if (!path)
		error_exit3("malloc failed in t_path", data, room);
	path->index = room->index;
	path->edges = -1;
	// path->name = room->name; // are we going to use this?
	path->previous = NULL;
	path->next = NULL;
	return (path);
}

t_path	*make_path(t_data *data, t_room **room, int sink)
{
	t_room	*temp_room;
	t_path	*path;
	int		edge_count;

	edge_count = 0;
	temp_room = room[sink];
	path = init_path(data, temp_room);
	while (1)
	{
		temp_room = room[temp_room->bfs_previous];
		path->previous = init_path(data, temp_room);
		path->previous->next = path;
		path = path->previous;
		if (room[temp_room->bfs_previous]->start == ON)
			break ;
		edge_count++;
	}
	path->edges = edge_count;
	return (path);
}

void	set_vertex_queue(t_data *data, t_room **room, int *queue, int index)
{
	int		i;
	int		in_list;
	t_edge	*edge;

	edge = room[index]->edge->head;
	if (room[index]->bfs_previous != -1 && room[index]->hop_off_switch == OFF)
		follow_backwards(room, queue, index);
	else
	{
		set_queue(data, room, queue, index);
		if (room[index]->hop_off_switch == ON)
			room[index]->hop_off_switch = OFF;
	}
	// free (edge);
}

void	set_queue(t_data *data, t_room **room, int *queue, int index)
{
	int		i;
	int		in_list;
	t_edge	*edge;

	edge = room[index]->edge->head;
	while (edge)
	{
		if (room[edge->room]->bfs_previous != -1 || edge->on_off == OFF)
			edge = edge->next;
		i = 0;
		in_list = OFF;
		while (queue[i])
		{
			if (search_int_in_int_array(edge->room, queue))
				in_list = ON;
			i++;
		}
		if (in_list == OFF)
			add_to_queue(room, edge, &queue[i], index);
		edge = edge->next;
	}
	// free (edge);
}

t_path	*bfs(t_data *data, t_room **room)
{
	t_path	*path;
	int		*queue;
	int		i;

	queue = init_queue(data);
	i = 0;
	while (queue && queue[i])
	{
		if (data->vertex == OFF)
			set_queue(data, room, queue, queue[i]);
		else if (data->vertex == ON)
			set_vertex_queue(data, room, queue, queue[i]);
		if (room[queue[i]]->end == ON)
			break ;
		i++;
	}
	if (room[queue[i]]->end == OFF)
		path = NULL;
	else
		path = make_path(data, room, queue[i]);
	clean_bfs(data, room, queue);
	return (path);
}

/*
	The idea of breadth-first search is to find the shortest path.
	We use it in a way that we stop the search when the shortest path is found,
	and return that. Then we call bfs again with an updated map to see if it 
	finds the next shortest path that can co-exist with the previous.
*/
