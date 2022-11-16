/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_bfs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:39:49 by mtissari          #+#    #+#             */
/*   Updated: 2022/11/11 14:48:48 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_queue	*init_queue(t_data *data) //This might not even need a struct, but int array
{
	t_queue	*queue;

	queue = (t_queue *)malloc(sizeof(t_queue));
	if (!queue)
		error_exit1("malloc_error in t_queue", data);
	queue->room_queue = (int *)malloc(sizeof(int) * data->nb_rooms);
	queue->cold_rooms = (int *)malloc(sizeof(int) * data->nb_rooms);
	if (!queue->room_queue || !queue->cold_rooms)
		error_exit1("malloc_error in t_queue", data);
	queue->room_queue[0] = data->source->index;
	//the struct might get something else inside
	return (queue);
}

t_path	*init_path(t_data *data, t_room *room)
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

t_path	*make_path(t_data *data)
{
	t_room	*room;
	t_path	*path;
	int		edge_count;

	edge_count = 0;
	room = data->sink;
	while (1)
	{
		if (room->end == ON)
			path = init_path(data, room);
		else
		{
			path->previous = init_path(data, room);
			path->previous->next = path;
			path = path->previous;
		}
		room = hash_find(data, room->bfs_previous);
		if (room->start == ON)
			break ;
		edge_count++;
	}
	path->edges = edge_count;
	return (path);
}

void	clean_bfs(t_data *data, t_room *room, t_queue *queue)
{
	t_room	*temp_room;

	temp_room = data->source;
	while (temp_room)
	{
		temp_room->bfs_previous = -1; // need to agree on this.
		temp_room = temp_room->next;
	}
	// free (temp_room);
	// free (room);
	free (queue->room_queue);
	// free all other queue things if we use a struct
	// free (queue); // if we use it as a struct
}

int	search_int_in_int_array(int	needle, int *haystack) // better name?
{
	int	i;

	i = 0;
	while (haystack[i])
	{
		if (needle == haystack[i])
			return (1);
		i++;
	}
	return (0);
}

void	add_to_queue(t_data *data, t_room *room, t_queue *queue, int index)
{
	int	i;
	t_room	*temp_room;

	i = 0;
	while (queue->room_queue[i])
		i++;
	queue->room_queue[i] = index;
	temp_room = data->source;
	while (temp_room->index != index || temp_room)
		temp_room = temp_room->next;
	if (temp_room->index == index)
		temp_room->bfs_previous = room->index;
	// free (temp_room);
}

void	set_queue(t_data *data, t_room *room, t_queue *queue)
{
	int		i;
	int		in_list;
	t_edge	*temp;

	temp = room->edges;
	while (temp)
	{
		i = 0;
		in_list = OFF;
		while (queue->room_queue[i])
		{
			if (search_int_in_int_array(temp->index, queue->room_queue))
				in_list = ON;
			i++;
		}
		if (in_list == OFF)
			add_to_queue(data, room, queue, temp->index);
		temp = temp->next;
	}
	// free (temp);
}

t_path	*bfs(t_data *data)
{
	t_room	*room;
	t_queue	*queue;
	t_path	*path;
	int		i;

	room = data->source;
	queue = init_queue(data);
	i = 0;
	while (queue->room_queue[i])
	{
		set_queue(data, room, queue);
		if (room->end == ON)
			break ;
		i++;
		room = hash_find(data, queue->room_queue[i]);
	}
	if (room->end == OFF)
		path = NULL;
	else
		path = make_path(data);
	clean_bfs(data, room, queue);
	return (path);
}

/*
	The idea of breadth-first search is to find the shortest path.
	We use it in a way that we stop the search when the shortest path is found,
	and return that. Then we call bfs again with an updated map to see if it 
	finds the next shortest path that can co-exist with the previous.
*/
