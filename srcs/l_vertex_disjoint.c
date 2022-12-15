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
		edge = room[nb]->edge;
		while (edge)
		{
			edge->on_off = ON;
			edge = edge->next;
		}
		room[nb]->bfs_previous = -1;
		room[nb]->bfs_folo = OFF;
		room[nb]->to_folo = -1;
		room[nb]->hop_off_switch = OFF;
		nb--;
	}
}

void	room_switch(t_room **room, int index, t_edge *link, int vertex)
{
	link->on_off = OFF;
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

	opt = get_option_head(option);
	while (opt)
	{
		pathh = opt->path;
		while (pathh->next && room[pathh->index]->end == OFF)
		{
			link = room[pathh->index]->edge;
			while (link)
			{
				link->on_off = ON;
				if (link->room == pathh->next->index)
				{
					room[pathh->next->index]->bfs_previous = pathh->index;
					room_switch(room, pathh->next->index, link, vertex);
				}
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

	data->vertex = ON;
	make_residual_path(option, room, ON);
	temp_path = bfs(data, room);
	if (temp_path == NULL)
		return (NULL);
	reset_map(room, data->nb_rooms - 1);
	make_residual_path(option, room, OFF);
	find_edge_to_delete(room, temp_path);
	free_path (temp_path);
	data->vertex = OFF;
	reset_map(room, data->nb_rooms - 1);
	new_option = find_all_disjoint_paths(data, room);
	return (new_option);
}
