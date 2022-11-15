/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_solver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:13:06 by mtissari          #+#    #+#             */
/*   Updated: 2022/11/08 20:44:11 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_path	*find_all_disjoint_paths(t_data *data)
{
	t_path		*cur_path;
	t_option	*paths;

	while (1)
	{
		cur_path = bfs(data);
		if (cur_path == NULL)
			break ;
		if (paths->previous == NULL)
			paths->start = cur_path;
		else
		{
			paths->next->start = cur_path;
		}
		free_paths (cur_path);
	}
}

/*
	I think we need to make another struct that holds all the paths inside.
	Like that option -thing, like option 1 has 2 paths inside, option 2 has 3 etc...
*/

void	solver(t_data *data)
{
	t_option	*paths;
	t_option	*next_added;

	if (data->nb_ants == 1)
		return (bfs(data));//Just to show that it skips all funcitons after bfs.
	paths = find_all_disjoint_paths(data);
	if (we use less paths than found in above function)
		return (paths);
	while (paths->turns >= next_added->turns)
	{
		next_added = vertex_disjoint(data, paths);
	}
	// print here or in the main?
	// If in the main, we need to either return the string from here,
	// or save it in data.
}

/*	Hasbulla once said... Coca cola
	Ive just cleaned some stuff, the error exit functions are numbered 
	according to how many structs are being freed. im still unsure about 
	the t_room being freed? does that come unpacked with with data ?
*/