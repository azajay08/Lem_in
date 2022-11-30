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

	while (nb >= 0)
	{
		edge = room[nb]->edge->head;
		while (edge)
		{
			edge->on_off = ON;
			edge = edge->next;
		}
		nb--;
	}
}

void	delete_the_edge(t_room *room)
{
	t_edge	*temp2;
	t_edge	*prev;

	temp2 = room->edge->head;
	prev = room->edge->head;
	while (temp2->next)
	{
		if (temp2->on_off == OFF)
		{
			if (prev == room->edge->head)
			{
				while (prev->next)
				{
					prev = prev->next;
					prev->head = room->edge->next;
				}
			}
			else
				prev->next = temp2->next;
			free(temp2);
			break ;
		}
		prev = temp2;
		temp2 = temp2->next;
	}
	//free (prev);
}

void	find_edge_to_delete(t_room **room, t_path *path)
{
	t_room	*temp_room;

	path = path->next;
	while (path)
	{
		temp_room = room[path->previous->index];
		while (temp_room->edge)
		{
			if (temp_room->edge->on_off == OFF)
				delete_the_edge(room[path->index]);
			temp_room->edge = temp_room->edge->next;
		}
		path = path->next;
	}
}

void	make_residual_path(t_option *option, t_room **room)
{
	t_path		*temp;
	t_option	*opt;

	opt = option;
	while (opt)
	{
		while (opt->path->next)
		{
			while (room[opt->path->index]->edge)
			{
				if (room[opt->path->index]->edge->room == opt->path->next->index)
				{
					room[opt->path->next->index]->bfs_previous = opt->path->index;
					room[opt->path->index]->edge->on_off = OFF;
				}
				else
					room[opt->path->index]->edge->on_off = ON;
				room[opt->path->index]->edge = room[opt->path->index]->edge->next;
			}
			opt->path = opt->path->next;
		}
		opt = opt->next;
	}
}

t_option	*vertex_disjoint(t_data *data, t_room **room, t_option *option)
{
	t_option	*new_option;
	t_path		*temp_path;

	data->vertex = ON;
	make_residual_path(option, room);
	temp_path = bfs(data, room);
	if (temp_path == NULL)
		return (NULL);
	find_edge_to_delete(room, temp_path);
	data->vertex = OFF;
	reset_map(room, data->nb_rooms - 1);
	new_option = find_all_disjoin_paths(data, room);
	return (new_option);
}
