/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_vertex_disjoint.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:45:54 by mtissari          #+#    #+#             */
/*   Updated: 2022/12/21 15:14:36 by mtissari         ###   ########.fr       */
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
	{
		room[index]->bfs_folo = OFF;
	}
}

void	make_residual_map(t_opt *option, t_room **room, int vertex)
{
	t_path	*pathh;
	t_opt	*opt;
	t_edge	*link;

	opt = get_opt_head(option);
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

/*
	A residual map is basically a map of leftovers.
	The function turns off all the edges that have been used, which leaves
	only edges(links) that haven't been used - the leftovers.
*/

t_opt	*vertex_disjoint(t_data *data, t_room **room, t_opt *option)
{
	t_opt	*new_option;
	t_path	*temp_path;

	data->vertex = ON;
	make_residual_map(option, room, ON);
	temp_path = bfs(data, room);
	if (temp_path == NULL)
		return (NULL);
	reset_map(room, data->nb_rooms - 1);
	make_residual_map(option, room, OFF);
	find_edge_to_delete(room, temp_path);
	free_path (temp_path);
	data->vertex = OFF;
	reset_map(room, data->nb_rooms - 1);
	new_option = find_all_disjoint_paths(data, room);
	return (new_option);
}

/*
	vertex_disjoint is another solver,
	that makes new paths if they can be found.

	First it finds an alternative path by using a residual map,
	then the path is used to delete an edge which prevents us from finding
	more paths.
	After deleting the edge, this solver makes another option for the real
	solver to calculate whether to use it or not.
*/
