/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_bfs_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:00:15 by mtissari          #+#    #+#             */
/*   Updated: 2022/11/22 16:00:39 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	*init_queue(t_data *data)
{
	int	*queue;

	queue = (int *)malloc(sizeof(data->nb_rooms));
	if (!queue)
		return (NULL); //need to check how to exit from here, need to free?
	queue[0] = data->src_index;
	return (queue);
}

void	clean_bfs(t_data *data, t_room **room, int *queue)
{
	int		i;

	i = 0;
	while (i < data->nb_rooms)
	{
		room[i]->bfs_previous = -1;
		room[i]->hop_off_switch = OFF;
		i++;
	}
	free (queue);
}

int	search_int_in_int_array(int index, int *queue) // better name?
{
	int	i;

	i = 0;
	while (queue[i])
	{
		if (index == queue[i] || index == -1)
			return (1);
		i++;
	}
	return (0);
}

void	add_to_queue(t_room **room, t_edge *temp, int *queue, int index)
{
	int		i;

	i = 0;
	queue[i] = temp->room;
	room[temp->room]->bfs_previous = index;
}
