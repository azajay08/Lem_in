/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breadth_first.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:39:49 by mtissari          #+#    #+#             */
/*   Updated: 2022/11/01 15:36:55 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	set_queue(t_room *room, t_queue *queue)
{
	t_room	*temp_room;

	temp_room = room;
	while (temp_room->next != NULL)
	{
		if (ft_strstr(room->edges, temp_room->name))
		{
			queue->room_queue = ft_strjoin(queue->room_queue, temp_room->name);
			queue->room_queue = ft_strjoin(queue->room_queue, '-');
		}
		temp_room = temp_room->next;
	}
	temp_room = room;
	while (temp_room->next != NULL)
	{
		if (temp_room->name == the first name in the queue)
			break ;
		temp_room = temp_room->next;
	}
	queue->next_room = temp_room;
	clean_room_queue(queue); //to get rid of the first room in the queue.
}

void	bfs(t_data *data)
{
	t_room	*room;
	t_queue	*queue;

	room = data->source;
	while (room->next != NULL)
	{
		set_queue(room, queue);
		//check the links in bfs order.
		//keep track of the paths.
		room = queue->next_room;
	}
}