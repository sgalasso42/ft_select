/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_elem_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 19:29:42 by sgalasso          #+#    #+#             */
/*   Updated: 2018/11/30 02:21:58 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int				ft_lst_len(t_elem *elem)
{
	t_elem	*start;
	int		i;

	i = 0;
	start = elem;
	while (elem)
	{
		elem = elem->next;
		i++;
	}
	elem = start;
	return (i);
}

void			ft_lst_del(t_elem *elem)
{
	t_elem		*temp;

	while (elem)
	{
		ft_strdel(&(elem->name));
		temp = elem->next;
		free(elem);
		elem = temp;
	}
}

static void		ft_lst_error_exit(t_elem *elem)
{
	ft_lst_del(elem);
	ft_putendl_fd("Errror : out of memory", 2);
	exit(EXIT_FAILURE);
}

void			ft_lst_new(char *name, t_data *data)
{
	if (!(data->elem->name = ft_strdup(name)))
	{
		ft_putendl_fd("Errror : out of memory", 2);
		exit(EXIT_FAILURE);
	}
	data->elem->under = 1;
	data->last = data->elem;
	data->current = data->elem;
}

void			ft_lst_add(char *name, t_data *data)
{
	t_elem		*start;

	start = data->elem;
	while (data->elem->next)
		data->elem = data->elem->next;
	if (!(data->elem->next = (t_elem *)ft_memalloc(sizeof(t_elem))))
		ft_lst_error_exit(start);
	if (!(data->elem->next->name = ft_strdup(name)))
		ft_lst_error_exit(start);
	data->elem->next->prev = data->elem;
	data->last = data->elem->next;
	data->elem = start;
}
