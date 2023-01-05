/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_line_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajones <ajones@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:38:24 by ajones            #+#    #+#             */
/*   Updated: 2023/01/05 20:56:38 by ajones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	free_line(t_line *head)
{
	t_line	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->line);
		free(temp);
	}
}

void	print_map(t_data *data)
{
	t_line	*tmp;

	tmp = data->line;
	while (tmp)
	{
		ft_putstr(tmp->line);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}

t_line	*make_line(t_data *data, char *line)
{
	t_line	*line_str;

	line_str = (t_line *)malloc(sizeof(t_line));
	if (!line_str)
		error_exit1(LINE_FAIL, data);
	line_str->line = ft_strdup(line);
	line_str->next = NULL;
	return (line_str);
}

void	append_line(t_data *data, t_line *line)
{
	t_line	*tmp;

	tmp = data->line;
	while (data->line->next)
		data->line = data->line->next;
	data->line->next = line;
	data->line = tmp;
}

void	line_join(t_data *data, char *line)
{
	t_line	*l_str;

	l_str = make_line(data, line);
	if (!data->line)
		data->line = l_str;
	else
		append_line(data, l_str);
}
