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

t_path	*init_path(t_data *data, t_room *room, int index) //atm data is here only for free.
{
	t_path	*new_path;

	new_path = (t_path *)malloc(sizeof(t_path));
	if (!new_path)
		error_exit1("malloc failed in t_path", data); //CHECK THIS
	printf("\t'![%s]!'\t", room->name);
	printf("index: %i\n", index);
//	printf("\n\n|path: %p|\n", &new_path);
//	printf("\tin init_path\n\n");
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
	printf("\nPATH:\n");
	path = init_path(data, temp_room, sink);
	while (1)
	{
		index = temp_room->bfs_previous;
		temp_room = room[temp_room->bfs_previous];
		path->previous = init_path(data, temp_room, index);
		path->previous->next = path;
		path = path->previous;
		if (temp_room->start == ON)
			break ;
		edge_count++;
	}
	path->edges = edge_count;
	return (path);
}

void	set_vert_queue(t_room **room, int *queue, int index)
{
	int		i;
	int		in_list;
	t_edge	*edge;

	edge = room[index]->edge;
	while (edge)
	{
		if (edge && (room[edge->room]->bfs_previous != -1 || edge->on_off == OFF
			|| room[edge->room]->bfs_previous == index)
			&& room[edge->room]->bfs_folo == OFF)
			edge = edge->next;
		if (!edge)
			break ;
		in_list = OFF;
		i = search_int_from_path(room, edge->room, index, queue);
		if (!i)
			in_list = ON;
		if (in_list == OFF && ((room[edge->room]->bfs_previous == -1
			&& edge->on_off == ON) || (room[edge->room]->bfs_folo == ON
			&& room[index]->start == OFF && room[index]->bfs_previous != edge->room)))
		{
			printf("\tedge to: %s\t", room[edge->room]->name);
			add_to_queue(room, edge, &queue[i], index);
		}
		edge = edge->next;
		if (!edge)
			break ;
	}
}

void	set_vertex_queue(t_room **room, int *queue, int index)
{
	int	i;

	i = 0;
	printf("\n\n********************* VERTEX QUEUE ! ************************\n\n");
	printf("\troom: %s, index: %i\n", room[index]->name, index);
	printf("queue:\n");
	while (queue[i] != -1 && i < 108)
	{
		printf(" %s,", room[queue[i]]->name);
		i++;
	}
	printf("\n\n");
	if (room[index]->bfs_previous != -1 && room[index]->hop_off_switch == OFF
		&& room[index]->bfs_folo == ON && room[index]->start == OFF
		&& room[index]->end == OFF)
	{
		printf("\tfollow backwards!\n");
		follow_backwards(room, queue, index);
	}
	else
	{
		printf("\tDON'T follow back");
		set_vert_queue(room, queue, index);
	}
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
			|| room[edge->room]->bfs_previous == index) && room[edge->room]->end == OFF)
			edge = edge->next;
		if (!edge)
			break ;
		in_list = OFF;
		i = search_int_in_int_array(edge->room, queue);
		if (!i)
			in_list = ON;
		if ((in_list == OFF && room[edge->room]->bfs_previous == -1
			&& edge->on_off == ON) || (in_list == OFF && room[edge->room]->end == ON))
		{
			printf("\tedge to: %s\t", room[edge->room]->name);
			add_to_queue(room, edge, &queue[i], index);
		}
		edge = edge->next;
		if (!edge)
			break ;
	}
}

t_path	*bfs(t_data *data, t_room **room)
{
	t_path	*path;
	int		i;

	printf("_________________________________BFS START__________________________________");
	init_queue(data);
	i = 0;
	while (data->queue[i] != -1)
	{
		printf("\nbfs loop[%i] ", i);
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
	printf("\nbfs after!");
//	printf("\t\t\troom->queue: %s\n\n", room[data->queue[i]]->name);
	if (room[data->queue[i]]->end == OFF)
		path = NULL;
	else
		path = make_path(data, room, data->queue[i]);
	clean_bfs(data, room);
	printf("_______________________________BFS END_________________________________");
	return (path);
}

/*
	The idea of breadth-first search is to find the shortest path.
	We use it in a way that we stop the search when the shortest path is found,
	and return that. Then we call bfs again with an updated map to see if it 
	finds the next shortest path that can co-exist with the previous.
*/
