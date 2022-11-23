/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_free_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 19:42:09 by ajones            #+#    #+#             */
/*   Updated: 2022/11/23 19:42:38 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	free_edge(t_edge *head)
{
	t_edge *temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}

void	free_room_arr(t_data *data)
{
	t_room	**temp;
	int		i;

	i = 0;
	temp = data->room;
	while (i < data->nb_rooms)
	{
		free(temp[i]->name);
		temp[i]->name = NULL;
		free_edge(temp[i]->edge->head);
		free(temp[i]);
		i++;
	}
	free(data->room);
	data->room = NULL;
}

void	free_all(t_data *data)
{
	t_vert	*temp;

	free_room_arr(data);
	if (data->q_mode == OFF)
		free(data->line);
	data->line = NULL;
	while (data->source != NULL)
	{
		temp = data->source;
		data->source = data->source->next;
		free(temp->name);
		temp->name = NULL;
		free(temp);
	}
	free (data);
}
