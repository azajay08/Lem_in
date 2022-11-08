/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:19:09 by ajones            #+#    #+#             */
/*   Updated: 2022/11/08 19:10:00 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	main(int ac, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		error_exit(DATA_FAIL);
	init_data(data);
	read_input(data);
	// DO WE NEED TO PARSE SOMETHING ELSE,
	// so that we could send that to the solver?
	// That way we could make another struct here

	// check error inputs and exit properly
	// can also take the check to another fucntion
	// read input if all is okay
	solver(data);
	//print the solution here?
	return (0);
}
