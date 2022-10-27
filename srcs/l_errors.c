/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_errors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:09:53 by ajones            #+#    #+#             */
/*   Updated: 2022/10/27 15:32:16 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	error_exit(char *error_str, t_verify *verify)
{
	// str will contain the error message ?
	// free all that needs freeing or maybe not on an exit ?
	free(verify);
	
	ft_putstr(error_str);

	exit(1);
}

void	error_handling(char *error_str)
{
	ft_putstr(error_str);
	exit(1);
}