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

t_queue	*init_queue(t_data *data)
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

void	clean_rooms(t_data *data)
{
	t_room	*temp_room;

	temp_room = data->source;
	while (temp_room)
	{
		temp_room->bfs_previous = -1; // need to agree on this.
		temp_room = temp_room->next;
	}
	// free (temp_room);
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

	room = room;
	while (room->edges->index)
	{
		i = 0;
		in_list = OFF;
		while (queue->room_queue[i])
		{
			if (room->edges->index == queue->room_queue)
				in_list = ON;
			i++;
		}
		if (in_list == OFF)
			add_to_queue(data, room, queue, room->edges->index);
		room->edges->index++;
	}
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
	while (queue->room_queue[i] != data->sink->index || queue->room_queue[i])
	{
		set_queue(data, room, queue);
		//check the links in bfs order.
		//keep track of the paths.
		i++;
		room = hash_find(data, queue->next_room[i]);
	}
	path = make_path(data);
	clean_rooms(data);
	while (path->previous != NULL)
		path = path->previous;
	return (path);
}

/*
	The idea of breadth-first search is to find the shortest path.
	We use it in a way that we stop the search when the shortest path is found,
	and return that. Then we call bfs again with an updated map to see if it 
	finds the next shortest path that can co-exist with the previous.
*/
