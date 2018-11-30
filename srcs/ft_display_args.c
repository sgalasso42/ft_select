/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 20:23:13 by sgalasso          #+#    #+#             */
/*   Updated: 2018/11/30 02:21:28 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int		ft_get_max_size(t_elem *elem)
{
	t_elem	*start;
	int		max;

	max = 0;
	start = elem;
	while (elem)
	{
		if ((int)ft_strlen(elem->name) > max)
			max = ft_strlen(elem->name);
		elem = elem->next;
	}
	elem = start;
	return (max);
}

static int		ft_calc_size(t_elem *elem)
{
	t_elem	*start;
	size_t	temp;

	temp = 0;
	start = elem;
	while (elem)
	{
		if (ft_strlen(elem->name) > temp)
			temp = ft_strlen(elem->name);
		elem = elem->next;
	}
	elem = start;
	return ((int)temp);
}

static int		ft_fill_it(struct winsize *wsize, t_elem *elem)
{
	int nbcol;
	int	ismod;

	ismod = (ft_lst_len(elem) % (wsize->ws_row - 1) != 0) ? 0 : 1;
	nbcol = ft_lst_len(elem) / (wsize->ws_row - 1) + ismod;
	if ((nbcol + 1) * (ft_get_max_size(elem) + 2) > wsize->ws_col)
		return (0);
	return (1);
}

static void		ft_display_loop(struct winsize *wsize, t_elem *elem)
{
	t_elem			*start;
	int				row;
	int				col;

	row = 0;
	col = 0;
	start = elem;
	while (elem)
	{
		if (row == wsize->ws_row - 1)
		{
			col += ft_calc_size(start) + 2;
			row = 0;
		}
		tputs(tgoto(tgetstr("cm", 0), col, row++), 1, &ft_tputschar);
		if (elem->under)
			ft_putstr_fd(C_UNDER, STDERR_FILENO);
		if (elem->color)
			ft_putstr_fd(C_COLOR, STDERR_FILENO);
		ft_putstr_fd(elem->name, STDERR_FILENO);
		ft_putstr_fd(C_NONE, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		elem = elem->next;
	}
	elem = start;
}

void			ft_display_args(t_elem *elem)
{
	struct winsize	wsize;

	ioctl(STDERR_FILENO, TIOCGWINSZ, &wsize);
	if (!ft_fill_it(&wsize, elem))
	{
		tputs(tgetstr("cl", 0), 1, &ft_tputschar);
		ft_putendl_fd("> Terminal too small <", STDERR_FILENO);
		return ;
	}
	ft_display_loop(&wsize, elem);
}
