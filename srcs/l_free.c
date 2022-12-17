/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 00:41:59 by ajones            #+#    #+#             */
/*   Updated: 2022/12/17 03:16:20 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	free_path(t_path *path)
{
	t_path	*temp;

	path = get_path_head(path);
	while (path)
	{
		temp = path;
		path = path->next;
		temp->previous = NULL;
		temp->next = NULL;
		free(temp);
	}
}

void	free_ants(t_data *data)
{
	t_ant	*temp;

	while (data->queen != NULL)
	{
		temp = data->queen;
		data->queen = data->queen->next;
		temp->next = NULL;
		temp->head = NULL;
		free(temp);
	}
}

void	free_option(t_opt *option)
{
	t_opt	*temp;

	option = get_opt_head(option);
	while (option)
	{
		temp = option;
		free_path(option->path);
		option = option->next;
		temp->previous = NULL;
		temp->next = NULL;
		free(temp);
	}
	free(option);
}
