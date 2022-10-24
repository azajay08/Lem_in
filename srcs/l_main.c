/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:19:09 by ajones            #+#    #+#             */
/*   Updated: 2022/10/24 14:48:33 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	comment_found(char *line, t_data *data)
{
	if (line[0] == '#' && line[1] == '#') ##START
		start_or_end();
}

void	start_or_end(char *line, t_data *data)
{
	data->start = 1;
	verify->nb_of_starts++;
}

int	read_all_data(t_data *data)
{
	char	*line;
	int		ret;

	ret = 1;
	while (ret == 1)
	{
		ret = get_next_line(0, &line);
		if (ret != 1 || ret != 0)
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
}

int	main(int ac, char **argv)
{
	t_data		*data;
	t_verify	*verify;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		error_handling(DATA_FAIL);
	verify = (t_verify *)malloc(sizeof(t_verify));
	if (!verify)
		error_exit(VERIFY_FAIL, data);
	init_data(data);
	init_verify(verify);
	// check error inputs and exit properly
	// can also take the check to another fucntion
	// read input if all is okay
	if (!read_all_data(data))
		return (0);
	//do the algorithm here
	//print the solution here
	return (0);
}
