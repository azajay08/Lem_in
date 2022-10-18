/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_errors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:09:53 by ajones            #+#    #+#             */
/*   Updated: 2022/10/18 14:12:39 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	error_exit(char *str, t_data *data)
{
	// str will contain the error message ?
	// free all that needs freeing or maybe not on an exit ?
	free(data);

	exit(1);
}