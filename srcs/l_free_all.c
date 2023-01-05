/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_free_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 19:42:09 by ajones            #+#    #+#             */
/*   Updated: 2023/01/05 20:32:49 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	free_edge(t_edge *head)
{
	t_edge	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		temp->next = NULL;
		temp->head = NULL;
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
		if (temp[i]->edge)
			free_edge(temp[i]->edge);
		free(temp[i]);
		i++;
	}
	free(data->room);
	data->room = NULL;
}

void	free_vert(t_data *data)
{
	t_vert	*temp;

	while (data->source != NULL)
	{
		temp = data->source;
		data->source = data->source->next;
		if (temp->edge)
			free_edge(temp->edge);
		free(temp->name);
		temp->name = NULL;
		free(temp);
		temp->next = NULL;
	}
}

void	free_all(t_data *data, int condition)
{
	t_vert	*temp;

	if (data->q_mode == OFF)
		free_line(data->first);
	if (data->queue)
		free(data->queue);
	while (data->source != NULL)
	{
		temp = data->source;
		data->source = data->source->next;
		if (temp->edge)
			free_edge(temp->edge);
		free(temp->name);
		temp->name = NULL;
		free(temp);
	}
	if (condition == SUCCESS)
		free_room_arr(data);
	free(data);
}
