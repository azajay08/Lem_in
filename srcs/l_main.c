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
	t_verify	*verify;

	verify = (t_verify *)malloc(sizeof(t_verify));
	if (!verify)
		error_handling(VERIFY_FAIL);
	init_verify(verify);
	read_input(verify);
	// check error inputs and exit properly
	// can also take the check to another fucntion
	// read input if all is okay
	
	//do the algorithm here
	//print the solution here
	return (0);
}
