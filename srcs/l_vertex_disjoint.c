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

/*
	Maybe don't delete after all!!
 Maybe we can use the edge->on_off button for this
so that we don't need to delete. could be like ON/OFF/BAD
 Because if we delete it completely, we lose
The data of that edge, which we might need
in case of this option doesn't work.

Although the paths are saved in the previous option
So will have to think which one to choose!
*/

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
				prev = prev->next;
				while (prev)
				{
					prev->head = room->edge->next;
					prev = prev->next;
				}
			}
			else
				prev->next = temp2->next;
			free_edge(temp2); // just this one edge!!!
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
			if (temp_room->edge->on_off == OFF) // turn to BAD? many are OFF already
				delete_the_edge(room[path->index]);
			temp_room->edge = temp_room->edge->next;
		}
		path = path->next;
	}
}

void	make_residual_path(t_option *option, t_room **room)
{
	t_path	*temp; //not used (yet)
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
	t_path		*temp_path;

	data->vertex = ON;
	make_residual_path(option, room);
	temp_path = bfs(data, room);
	if (temp_path == NULL)
		return (NULL);
	find_edge_to_delete(room, temp_path);
	data->vertex = OFF;
	// saving the bfs_previouses might help in here
	// But would have to save ONLY the used ones.

	// Do we use bfs here or make another similiar algo..?

	new_option = find_all_disjoin_paths(data, room);
	return (new_option);
}
