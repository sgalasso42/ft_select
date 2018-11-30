/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 22:38:18 by sgalasso          #+#    #+#             */
/*   Updated: 2018/11/30 02:23:52 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_escape(t_data *data)
{
	ft_new_term_conf(1);
	ft_lst_del(data->elem);
	exit(EXIT_SUCCESS);
}

int		ft_tputschar(int c)
{
	return (write(STDERR_FILENO, &c, 1));
}

t_elem	*ft_singleton(void)
{
	static		t_elem	*start = 0;

	if (!start)
	{
		if (!(start = (t_elem *)ft_memalloc(sizeof(t_elem))))
		{
			ft_putendl_fd("Errror : out of memory", 2);
			exit(EXIT_FAILURE);
		}
	}
	return (start);
}

void	ft_return_lst(t_data *data)
{
	t_elem	*start;

	start = data->elem;
	while (data->elem && !data->elem->color)
		data->elem = data->elem->next;
	if (data->elem)
	{
		ft_putstr_fd(data->elem->name, STDOUT_FILENO);
		data->elem = data->elem->next;
	}
	while (data->elem)
	{
		if (data->elem->color)
		{
			ft_putchar_fd(' ', STDOUT_FILENO);
			ft_putstr_fd(data->elem->name, STDOUT_FILENO);
		}
		data->elem = data->elem->next;
	}
	data->elem = start;
}
