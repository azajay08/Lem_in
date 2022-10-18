/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:19:09 by ajones            #+#    #+#             */
/*   Updated: 2022/10/18 14:37:05 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	some_sorter(t_data *data)
{
	char	*line;
	
	if (get_next_line(0, &line) != 1)
		error_exit(GNL_FAIL, data);
	get_ant_info(line, data);

	get_map_info(line, data);
		
	// if input has no errors, then first GNL will be ant number
}

int	main(int ac, char **argv)
{
	t_data	data;
	
	init_data(&data);
	
	
	// check error inputs and exit properly
	// can also take the check to another fucntion

	// read input if all is okay
	some_sorter(&data); // this is just an example
	

	return (0);
}