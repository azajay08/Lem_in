/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_vertex_disjoint.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:45:54 by mtissari          #+#    #+#             */
/*   Updated: 2022/11/22 15:58:36 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	reset_map(t_room **room, int nb)
{
	t_edge	*edge;

	printf("\n\treset map\n");
	while (nb >= 0)
	{
		printf("\n\t\troom: %s", room[nb]->name);
		edge = room[nb]->edge;
		while (edge)
		{
			printf(", edge: %s", room[edge->room]->name);
			edge->on_off = ON;
			edge = edge->next;
		}
		room[nb]->bfs_previous = -1;
		room[nb]->bfs_folo = OFF;
		room[nb]->to_folo = -1;
		room[nb]->hop_off_switch = OFF;
		nb--;
	}
	printf("\n\treset map DONE\n\n");
}

void	delete_the_edge(t_room **room, int index)
{
	t_edge	*temp;
	t_edge	*prev;

	printf("\t------------delete the edge ");
	printf("from room: %s-------------\n\n", room[index]->name);
	temp = room[index]->edge;
	prev = room[index]->edge;
	while (temp)
	{
		printf("edge: (index)%i\n", temp->room);
		if (temp->on_off == OFF)
		{
			printf("\t NOW Deleting: (index)%i\n", temp->room);
			if (temp == room[index]->edge)
			{
				room[index]->edge = temp->next;
			}
			else
				prev->next = temp->next;
			temp->next = NULL;
			free(temp);
			break ;
		}
		prev = temp;
		temp = temp->next;
	}
	printf("\n\t----------delete the edge DONE----------\n");
}

int	find_from_path(t_path *path, int room)
{
	t_path	*temp;

	temp = path;
	while (path)
	{
		if (room == path->index)
		{
			if (!path->next || !path->previous)
				return (1);
			else
				return (0);
		}
		path = path->next;
	}
	path = temp;
	return (1);
}

void	find_edge_to_delete(t_room **room, t_path *path)
{
	t_edge	*temp_edge;
	t_path	*path_head;

	printf("\tfind edge to delete\n");
	path_head = path;
	path = path->next;
	while (path)
	{
		if (room[path->previous->index]->start == ON || room[path->previous->index]->end == ON)
			path = path->next;
		if (!path)
			break ;
		printf("\ttemp_room: %s\n", room[path->previous->index]->name);
		temp_edge = room[path->previous->index]->edge;
		while (temp_edge)
		{
			if (temp_edge->on_off == OFF && !find_from_path(path_head, temp_edge->room))
			{
				printf("edge to delete has been found: %s (%i), in paht: (%i)\n", room[temp_edge->room]->name, temp_edge->room, path->index);
				delete_the_edge(room, path->previous->index);
				break ;
			}
			temp_edge = temp_edge->next;
		}
		path = path->next;
	}
	path = path_head;
	printf("\tfind edge to delete DONE\n");
}

void	room_switch(t_room **room, int index, int vertex)
{
	if (vertex == ON)
	{
		room[index]->bfs_folo = ON;
	}
	else
		room[index]->bfs_folo = OFF;
}

void	make_residual_path(t_option *option, t_room **room, int vertex)
{
	t_path		*pathh;
	t_option	*opt;
	t_edge		*link;

	opt = option;
	while (opt->previous)
		opt = opt->previous;
	while (opt)
	{
		pathh = opt->path;
		while (pathh->next && room[pathh->index]->end == OFF)
		{
			link = room[pathh->index]->edge;
			while (link)
			{
				if (link->room == pathh->next->index)
				{
					room[pathh->next->index]->bfs_previous = pathh->index;
					room_switch(room, pathh->next->index, vertex);
					link->on_off = OFF;
				}
				else
					link->on_off = ON;
				link = link->next;
			}
			pathh = pathh->next;
		}
		opt = opt->next;
	}
}

t_option	*vertex_disjoint(t_data *data, t_room **room, t_option *option)
{
	t_option	*new_option;
	t_path		*temp_path;

	printf("\nvertex disjoint \n");
	data->vertex = ON;
	make_residual_path(option, room, ON);
	temp_path = bfs(data, room);
	printf("\n\t\tvertex done\n");
	if (temp_path == NULL)
		return (NULL);
	reset_map(room, data->nb_rooms - 1);
	make_residual_path(option, room, OFF);
	find_edge_to_delete(room, temp_path);
	printf("\n\t\t edge deletion done!\n");
	data->vertex = OFF;
	reset_map(room, data->nb_rooms - 1);
	new_option = find_all_disjoint_paths(data, room);
	return (new_option);
}
