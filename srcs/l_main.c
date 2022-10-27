/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:19:09 by ajones            #+#    #+#             */
/*   Updated: 2022/10/27 15:31:53 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

// void	comment_found(char *line, t_data *data)
// {
// 	if (line[0] == '#')
// 	{
// 		if (ft_strstr(line, "##start") || ft)
// 	}
// 		start_or_end();
// }

// void	start_or_end(char *line, t_data *data)
// {
// 	data->start = 1;
// 	verify->nb_of_starts++;
// }

/*
	DONT WORRY, I started doing some last night but was tired so doesnt make
	much sense
*/

int	main(int ac, char **argv)
{
	t_verify	*verify;

	verify = (t_verify *)malloc(sizeof(t_verify));
	if (!verify)
		error_handling(DATA_FAIL);
	init_verify(verify);
	read_input(verify);
	// check error inputs and exit properly
	// can also take the check to another fucntion
	// read input if all is okay
	
	//do the algorithm here
	//print the solution here
	return (0);
}
