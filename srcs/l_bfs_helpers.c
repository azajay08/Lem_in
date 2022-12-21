/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_bfs_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:00:15 by mtissari          #+#    #+#             */
/*   Updated: 2022/12/21 15:21:41 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	init_queue(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_rooms * 2)
	{
		data->queue[i] = -1;
		i++;
	}
	i = 0;
	data->queue[0] = data->src_index;
	data->queue[data->nb_rooms * 2] = END;
}

void	clean_bfs(t_data *data, t_room **room)
{
	int		i;

	i = 0;
	while (i < data->nb_rooms)
	{
		data->queue[i] = -1;
		room[i]->bfs_previous = -1;
		room[i]->bfs_folo = OFF;
		room[i]->to_folo = -1;
		room[i]->hop_off_switch = OFF;
		i++;
	}
}

int	search_int_array(int index, int *queue)
{
	int	i;

	i = 0;
	while (queue[i] != END)
	{
		if (queue[i] == -1)
			break ;
		if (index == queue[i] || index == -1)
			return (0);
		i++;
	}
	return (i);
}

void	add_to_queue(t_room **room, t_edge *temp, int *queue, int index)
{
	int		i;

	i = 0;
	queue[i] = temp->room;
	if (room[temp->room]->bfs_folo == ON && room[index]->hop_off_switch == ON)
		room[temp->room]->hop_off_switch = ON;
	else if (room[temp->room]->bfs_folo == ON)
		room[temp->room]->to_folo = room[temp->room]->bfs_previous;
	if (room[index]->end == OFF)
		room[temp->room]->bfs_previous = index;
}

/*
	add_to_queue adds the room to the queue as the name suggests,
	but it also does some checks when we are making an alternative path
	from bfs_vertex.
	It also sets the bfs_previous, which is used to make the path.
*/
