/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:19:09 by ajones            #+#    #+#             */
/*   Updated: 2022/10/27 16:09:22 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	main(int ac, char **argv)
{
	t_verify	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		error_handling("MALLOC_FAIL");
	init_data(data);
	read_input(data);
	// check error inputs and exit properly
	// can also take the check to another fucntion
	// read input if all is okay
	
	//do the algorithm here
	//print the solution here
	return (0);
}
