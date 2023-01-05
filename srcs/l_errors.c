/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_errors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtissari <mtissari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:09:53 by ajones            #+#    #+#             */
/*   Updated: 2023/01/05 14:51:38 by mtissari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	error_exit(char *error_str)
{
	ft_putstr(error_str);
	exit(1);
}

void	error_exit1(char *error_str, t_data *data)
{
	free_all(data, ERROR);
	ft_putstr(error_str);
	exit(1);
}

void	error_exit2(char *error_str, t_data *data, t_verify *verify)
{
	free(verify);
	free_all(data, ERROR);
	ft_putstr(error_str);
	exit(1);
}
