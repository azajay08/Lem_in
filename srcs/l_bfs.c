/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_bfs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:39:49 by mtissari          #+#    #+#             */
/*   Updated: 2022/12/16 18:28:19 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_path	*init_path(t_data *data, int index)
{
	t_path	*new_path;

	new_path = (t_path *)malloc(sizeof(t_path));
	if (!new_path)
		error_exit1(PATH_FAIL, data);
	new_path->index = index;
	new_path->edges = -1;
	new_path->previous = NULL;
	new_path->next = NULL;
	return (new_path);
}

t_path	*make_path(t_data *data, t_room **room, int sink)
{
	t_room	*temp_room;
	t_path	*path;
	int		edge_count;
	int		index;

	edge_count = 1;
	temp_room = room[sink];
	path = init_path(data, sink);
	while (1)
	{
		index = temp_room->bfs_previous;
		temp_room = room[temp_room->bfs_previous];
		path->previous = init_path(data, index);
		path->previous->next = path;
		path = path->previous;
		if (temp_room->start == ON)
			break ;
		edge_count++;
	}
	path->edges = edge_count;
	return (path);
}

void	set_queue(t_room **room, int *queue, int index)
{
	int		i;
	int		in_list;
	t_edge	*edge;

	edge = room[index]->edge;
	while (edge)
	{
		if (edge && (room[edge->room]->bfs_previous != -1 || edge->on_off == OFF
				|| room[edge->room]->bfs_previous == index)
			&& room[edge->room]->end == OFF)
			edge = edge->next;
		if (!edge)
			break ;
		in_list = OFF;
		i = search_int_in_int_array(edge->room, queue);
		if (!i)
			in_list = ON;
		if ((in_list == OFF && room[edge->room]->bfs_previous == -1
				&& edge->on_off == ON)
			|| (in_list == OFF && room[edge->room]->end == ON))
			add_to_queue(room, edge, &queue[i], index);
		edge = edge->next;
	}
	edge = NULL;
}

t_path	*bfs(t_data *data, t_room **room)
{
	t_path	*path;
	int		i;

	init_queue(data);
	i = 0;
	while (data->queue[i] != -1)
	{
		if (room[data->queue[i]]->end == ON)
			break ;
		if (data->vertex == OFF)
			set_queue(room, data->queue, data->queue[i]);
		else if (data->vertex == ON)
			set_vertex_queue(room, data->queue, data->queue[i]);
		i++;
		if (i == data->nb_rooms * 2)
			break ;
	}
	if (data->queue[i] == -1)
		i--;
	if (room[data->queue[i]]->end == OFF)
		path = NULL;
	else
		path = make_path(data, room, data->queue[i]);
	clean_bfs(data, room);
	return (path);
}

/*
	The idea of breadth-first search is to find the shortest path.
	We use it in a way that we stop the search when the shortest path is found,
	and return that. Then we call bfs again with an updated map to see if it 
	finds the next shortest path that can co-exist with the previous.
*/
