/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_helpers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:05:46 by ajones            #+#    #+#             */
/*   Updated: 2022/11/18 20:31:23 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_vert	*find_room_name(t_vert *head, char *target)
{
	t_vert *temp;

	temp = head;
	while (temp != NULL)
	{
		if (ft_strequ(target, temp->name))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

t_vert	*find_room_index(t_vert *head, int target)
{
	t_vert *temp;

	temp = head;
	while (temp != NULL)
	{
		if (temp->index == target)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}
