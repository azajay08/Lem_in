/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_read_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:06:41 by ajones            #+#    #+#             */
/*   Updated: 2022/10/27 16:07:03 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	get_link_info(char *line, t_data *data)
{
	int		ret;

	ret = 1;
	while (ret == 1)
	{
		save_link_info(line, data);	//example
		ft_strdel(&line);
		ret = get_next_line(0, &line);
	}
	if (ret != 0)
		error_exit(GNL_FAIL, data);
	return (1);
}
