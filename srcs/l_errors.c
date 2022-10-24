/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_errors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:09:53 by ajones            #+#    #+#             */
/*   Updated: 2022/10/24 14:49:09 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	error_exit(char *error_str, t_data *data)
{
	// str will contain the error message ?
	// free all that needs freeing or maybe not on an exit ?
	free(data);
	
	ft_putstr(error_str);

	exit(1);
}

void	error_handling(char *error_str)
{
	ft_putstr(error_str);
	exit(1);
}