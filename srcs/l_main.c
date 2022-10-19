/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:19:09 by ajones            #+#    #+#             */
/*   Updated: 2022/10/19 17:23:39 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	read_all_data(t_data *data)
{
	char	*line;
	int		ret;

	ret = 1;
	if (get_next_line(0, &line) != 1)
		error_exit(GNL_FAIL, data);
	get_ant_info(line, data);
	ft_strdel(&line);
	while (data->rooms_read == NOT_READ && ret == 1)
	{
		ret = get_next_line(0, &line);
		if (ret != 1)
			error_exit(GNL_FAIL, data);
		if (line[0] == '#' && line[1] == '#')//this could be inside comment_found to save room
			start_or_end(line, data);
		else if (line[0] == '#')
			comment_found(line, data);
		else if (ft_strchr(line, '-'))//something like this could be used to get to links
			break ;
		else
			get_room_info(line, data);
		ft_strdel(&line);
	}
	while (data->links_read == NOT_READ && ft_strchr(line, '-') && ret == 1)
	{
		get_link_info(line, data);
		ft_strdel(&line);
		ret = get_next_line(0, &line);
		if (ret != 1 || ret != 0)
			error_exit(GNL_FAIL, data);
	}
	ft_strdel(&line);
}

int	main(int ac, char **argv)
{
	t_data	data;

	init_data(&data);
	// check error inputs and exit properly
	// can also take the check to another fucntion
	// read input if all is okay
	if (!read_all_data(&data))
		return (0);
	//do the algorithm here
	//print the solution here
	return (0);
}
