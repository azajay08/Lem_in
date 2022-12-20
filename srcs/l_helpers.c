/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_helpers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:05:46 by ajones            #+#    #+#             */
/*   Updated: 2022/12/20 15:13:57 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_vert	*find_room_name(t_vert *head, char *target)
{
	t_vert	*temp;

	temp = head;
	while (temp != NULL)
	{
		if (ft_strequ(target, temp->name))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	check_dup_links(t_edge *edge, int index)
{
	t_edge	*head;

	head = edge->head;
	while (head)
	{
		if (head->room == index)
			return (1);
		head = head->next;
	}
	return (0);
}

t_path	*get_path_head(t_path *path)
{
	t_path	*head;

	head = path;
	while (head->previous != NULL)
		head = head->previous;
	return (head);
}

t_opt	*get_opt_head(t_opt *option)
{
	t_opt	*head;

	head = option;
	while (head->previous != NULL)
		head = head->previous;
	return (head);
}

t_opt	*get_opt_tail(t_opt *option)
{
	t_opt	*tail;

	tail = option;
	while (tail->next != NULL)
		tail = tail->next;
	return (tail);
}
