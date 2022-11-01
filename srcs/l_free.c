/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 00:41:59 by ajones            #+#    #+#             */
/*   Updated: 2022/10/27 00:43:03 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	free_verify(t_verify *verify)
{
	
}

void	free_data(t_data *data)
{
	t_room	*temp;

	while (data->source->next != NULL)
	{
		temp = data->source;
		data->source = data->source->next;
		free (temp);
	}
	if (data->sink)
		free (data->sink);
	free (data);
}
