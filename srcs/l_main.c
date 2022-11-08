/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:19:09 by ajones            #+#    #+#             */
/*   Updated: 2022/11/08 17:03:58 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	main(int ac, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		error_nothing_to_be_freed("MALLOC_FAIL");
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
