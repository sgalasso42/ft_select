/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 19:30:36 by sgalasso          #+#    #+#             */
/*   Updated: 2018/11/30 02:26:35 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		ft_load_args(char **argv, t_data *data)
{
	data->elem = ft_singleton();
	ft_lst_new(*(argv++), data);
	while (*argv)
		ft_lst_add(*(argv++), data);
}

static void		ft_select_loop(t_data *data)
{
	long	line;

	while (1)
	{
		line = 0;
		read(STDERR_FILENO, &line, 8);
		ft_event(line, data);
		data->nb_elems = ft_lst_len(data->elem);
		ft_display_args(data->elem);
	}
}

int				main(int argc, char **argv)
{
	t_data		data;

	if (argc < 2)
	{
		ft_putendl_fd("Usage : ./ft_select [args...]", 2);
		return (0);
	}
	ft_bzero(&data, sizeof(data));
	ft_get_signal();
	ft_load_args(++argv, &data);
	ft_new_term_conf(0);
	ft_display_args(data.elem);
	ft_select_loop(&data);
	return (0);
}
