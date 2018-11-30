/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 00:38:56 by sgalasso          #+#    #+#             */
/*   Updated: 2018/11/30 02:27:11 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		ft_key_move_hor(int direction, t_data *data)
{
	struct winsize	wsize;
	int				i;

	i = -1;
	ioctl(STDERR_FILENO, TIOCGWINSZ, &wsize);
	if (direction == 1)
	{
		while (++i < wsize.ws_row - 1)
			data->current = (data->current->next)
			? data->current->next : data->current;
	}
	else if (direction == 0)
	{
		while (++i < wsize.ws_row - 1)
			data->current = (data->current->prev)
			? data->current->prev : data->current;
	}
}

static void		ft_key_move(long line, t_data *data)
{
	data->current->under = 0;
	if (line == KEY_DO)
	{
		data->current = (data->current->next)
		? data->current->next : data->elem;
	}
	else if (line == KEY_UP)
	{
		data->current = (data->current->prev)
		? data->current->prev : data->last;
	}
	else if (line == KEY_LE)
		ft_key_move_hor(0, data);
	else if (line == KEY_RI)
		ft_key_move_hor(1, data);
	data->current->under = 1;
}

static void		ft_after_del(t_elem *temp, t_data *data)
{
	ft_strdel(&(data->current->name));
	ft_memdel((void *)&(data->current));
	data->current = temp;
	data->current->under = 1;
	tputs(tgetstr("cl", 0), 1, &ft_tputschar);
}

static void		ft_key_del(t_data *data)
{
	t_elem	*temp;

	temp = 0;
	if (data->current == data->elem && data->current == data->last)
		ft_escape(data);
	else if (data->current == data->elem)
	{
		data->current->next->prev = 0;
		data->elem = data->current->next;
		temp = data->current->next;
	}
	else if (data->current == data->last)
	{
		data->current->prev->next = 0;
		data->last = data->current->prev;
		temp = data->elem;
	}
	else
	{
		data->current->prev->next = data->current->next;
		data->current->next->prev = data->current->prev;
		temp = data->current->next;
	}
	ft_after_del(temp, data);
}

void			ft_event(long line, t_data *data)
{
	if (line == KEY_ESC)
		ft_escape(data);
	else if (line == KEY_SPC)
	{
		data->current->color = (data->current->color == 1) ? 0 : 1;
		data->current->under = 0;
		data->current = (data->current->next)
		? data->current->next : data->elem;
		data->current->under = 1;
	}
	else if (line == KEY_DO || line == KEY_UP
	|| line == KEY_RI || line == KEY_LE)
		ft_key_move(line, data);
	else if (line == KEY_DEL || line == KEY_BSP)
		ft_key_del(data);
	else if (line == KEY_ENT)
	{
		ft_new_term_conf(1);
		ft_return_lst(data);
		ft_lst_del(data->elem);
		exit(EXIT_SUCCESS);
	}
}
