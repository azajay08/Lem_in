/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 00:41:59 by ajones            #+#    #+#             */
/*   Updated: 2022/11/18 20:31:37 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	free_room(t_vert *room)
{
	if (room)
		free(room);
}

void	free_verify(t_verify *verify)
{
	if (verify)
		free(verify);
}

void	free_data(t_data *data)
{
	t_vert	*temp;

	while (data->source != NULL)
	{
		temp = data->source;
		data->source = data->source->next;
		free(temp->name);
		// free(temp->edges);
		// free(temp->next);
		free(temp);
	}
	// if (data->sink)
	// 	free (data->sink);
	if (data)
		free (data);
}
