/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:19:09 by ajones            #+#    #+#             */
/*   Updated: 2022/10/18 19:14:53 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	some_sorter(t_data *data)
{
	char	*line;
	
	if (get_next_line(0, &line) != 1)
		return (error_exit(GNL_FAIL, data));
	if (!get_ant_info(line, data))	//We can't use exit so we need to return
		return (0);
	if (!get_map_info(line, data))
		return (0);
	if (!get_link_info(line, data))
		return (0);
	// if input has no errors, then first GNL will be ant number
}

int	main(int ac, char **argv)
{
	t_data	data;
	
	init_data(&data);
	
	// check error inputs and exit properly
	// can also take the check to another fucntion

	// read input if all is okay
	if (!some_sorter(&data) // this is just an example
		return (0);

	return (0);
}
