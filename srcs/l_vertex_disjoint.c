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

int	delete_edge(t_room *room)
{
	t_edge	*temp1;
	t_edge	*temp2;

	temp1 = NULL;
	temp2 = room->edge->head;
	while (room->edge)
	{
		if (room->edge->on_off == ON)
		{
			if (temp1)
				temp1->next = temp2;
			if (temp2 == room->edge)
			{
				temp2 = room->edge->next;
				while (temp2)
				{

					temp2 = temp2->next;
				}
			}
			free_edge(room->edge); // function doesn't exist yet!
		}
		temp1 = room->edge;
		room->edge = room->edge->next;
	}
	return (1);
}

void	find_edge_to_delete(t_room **room, t_path *path)
{
	int		counter;
	t_room	*temp_room;

	counter = 0;
	path = path->next;
	while (path)
	{
		temp_room = room[path->previous->index];
		while (temp_room->edge)
		{
			if (temp_room->edge->on_off == ON)
				counter += delete_edge(room[path->index]);
			temp_room->edge = temp_room->edge->next;
		}
		path = path->next;
	}
}

void	make_residual_path(t_option *option, t_room **room)
{
	t_path	*temp;
	//Make some temps??

	while (option)
	{
		while (option->path->next)
		{
			while (room[option->path->index]->edge)
			{
				if (room[option->path->index]->edge->room == option->path->next->index)
				{
					room[option->path->next->index]->bfs_previous = option->path->index;
					room[option->path->index]->edge->on_off = OFF;
				}
				else
					room[option->path->index]->edge->on_off = ON;
				room[option->path->index]->edge = room[option->path->index]->edge->next;
			}
			option->path = option->path->next;
		}
		option = option->next;
	}
}

t_option	*vertex_disjoint(t_data *data, t_room **room, t_option *option)
{
	t_option	*new_option;
	t_path		*temp;

	make_residual_path(option, room);
	temp = bfs(data, room);
	if (temp == NULL)
		return (NULL);
	find_edge_to_delete(room, temp);
	// saving the bfs_previouses might help in here
	// But would have to save ONLY the used ones.

	// Do we use bfs here or make another similiar algo..?

	new_option = find_all_disjoin_paths(data, room);
	return (new_option);
}
