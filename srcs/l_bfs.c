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
	int	*queue;

	queue = (int *)malloc(sizeof(data->nb_rooms));
	if (!queue)
		return (NULL); //need to check how to do this!!
	return (queue);
	/*
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
	return (queue);*/
}

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

void	clean_bfs(t_data *data, t_room **room, t_queue *queue)
{
	int		i;

	i = 0;
	while (i < data->nb_rooms)
	{
		room[i]->bfs_previous = -1;
		i++;
	}
	free (queue);
}

int	search_int_in_int_array(int	index, int *queue) // better name?
{
	int	i;

	i = 0;
	while (queue[i])
	{
		if (index == queue[i] || index == -1)
			return (1);
		i++;
	}
	return (0);
}

void	add_to_queue(t_room **room, t_edge *temp, int *queue, int index)
{
	int		i;

	i = 0;
	queue[i] = temp->room;
	room[temp->room]->bfs_previous = index;
}

void	set_queue(t_data *data, t_room **room, int *queue, int index)
{
	int		i;
	int		in_list;
	t_edge	*edge;

	edge = room[index]->edge;
	while (edge)
	{
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
	// free (dge);
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
		set_queue(data, room, queue, queue[i]);
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
