/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:19:09 by ajones            #+#    #+#             */
/*   Updated: 2022/10/27 01:14:55 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	comment_found(char *line, t_data *data)
{
	if (line[0] == '#')
	{
		if (ft_strstr(line, "##start") || ft)
	}
		start_or_end();
}

void	start_or_end(char *line, t_data *data)
{
	data->start = 1;
	verify->nb_of_starts++;
}

int	read_all_data(t_data *data)
{
	t_verify	verify;
	char		*line;
	int			ret;

	init_verify(&verify);
	get_ant_info(line, &verify);
	while (ret == 1)
	{
		ret = get_next_line(0, &line);
			error_exit(GNL_FAIL, data);
		else if (line[0] == '#')
			comment_found(line, data);
		else if (ants)
			get_ant_info(line, data);
		else if (rooms)
			get_room_info(line, data);
		else if(links)
			get_link_info(line, data);
		ft_strdel(&line);
	}
	free_verify(&verify);
	if (!data->valid_map)
		error_exit(MAP_ERROR, data);
}

int	main(int ac, char **argv)
{
	t_data		*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		error_handling(DATA_FAIL);
	init_data(data);
	read_all_data(data);
	// check error inputs and exit properly
	// can also take the check to another fucntion
	// read input if all is okay
	
	//do the algorithm here
	//print the solution here
	return (0);
}
