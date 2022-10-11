/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_toend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 16:50:56 by ajones            #+#    #+#             */
/*   Updated: 2021/12/29 16:42:18 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_toend(t_list **alst, t_list *new)
{
	t_list	*newelem;

	if (*alst && alst)
	{
		newelem = *alst;
		newelem = ft_lstlast(*alst);
		newelem->next = new;
		return ;
	}
	*alst = new;
}
