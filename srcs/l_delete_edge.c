/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_delete_edge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:54:33 by mtissari          #+#    #+#             */
/*   Updated: 2022/12/17 03:18:50 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	delete_the_edge(t_room **room, int index)
{
	t_edge	*temp;
	t_edge	*prev;

	temp = room[index]->edge;
	prev = room[index]->edge;
	while (temp)
	{
		if (temp->on_off == OFF)
		{
			printf("edge to delete address: %p\n", temp);
			if (temp == room[index]->edge)
				room[index]->edge = temp->next;
			else
				prev->next = temp->next;
			temp->next = NULL;
			// if (temp->head)	//probs will delete
			// {
			// 	free (temp->head);
			// 	temp->head = NULL;
			// }
			free(temp);
			temp = NULL;
			break ;
		}
		prev = temp;
		temp = temp->next;
	}
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
	t_path	*temp_path;

	temp_path = path->next;
	while (temp_path)
	{
		if (room[temp_path->previous->index]->start == ON
			|| room[temp_path->previous->index]->end == ON)
			temp_path = temp_path->next;
		if (!temp_path)
			break ;
		temp_edge = room[temp_path->previous->index]->edge;
		while (temp_edge)
		{
			if (temp_edge->on_off == OFF
				&& !find_from_path(path, temp_edge->room))
			{
				delete_the_edge(room, temp_path->previous->index);
				break ;
			}
			temp_edge = temp_edge->next;
		}
		temp_path = temp_path->next;
	}
}
