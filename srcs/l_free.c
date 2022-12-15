/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 00:41:59 by ajones            #+#    #+#             */
/*   Updated: 2022/12/05 23:43:31 by ajones           ###   ########.fr       */
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
		// if (temp->previous != NULL)
		// 	printf("\nyep\n");
		// if (path->next == NULL)
		// {
		// 	free (path);
		// 	break ;
		// }
		free(temp);
		// path = path->next;
	}
}

void	free_ants(t_data *data)
{
	t_ant	*temp;

	while (data->queen != NULL)
	{
		temp = data->queen;
		data->queen = data->queen->next;
		free(temp);
	}
}

void	free_option(t_option *option)
{
	t_option	*temp;

	option = get_option_head(option);
	while (option)
	{
		temp = option;
		free_path(option->path);
		// if (option->previous)
		// 	free(option->previous);
		// if (option->next == NULL)
		// {
		// 	free (option);
		// 	break ;
		// }
		option = option->next;
		free(temp);
	}
	free(option);
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

/*MIGHT NOT NEED FREE DATA, I HAVE MADE THE FREE ALL FUNCTION
THE OTHERS COULD BE ADDED TO THAT*/
