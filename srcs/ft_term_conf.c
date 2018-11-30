/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_conf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 19:37:25 by sgalasso          #+#    #+#             */
/*   Updated: 2018/11/30 02:23:42 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		ft_err_conf_exit(char *err)
{
	ft_putendl_fd(err, STDERR_FILENO);
	ft_lst_del(ft_singleton());
	exit(EXIT_FAILURE);
}

void			ft_new_term_conf(int reset)
{
	static struct termios	saved;
	struct termios			term;

	if (reset)
	{
		tcsetattr(STDERR_FILENO, TCSANOW, &saved);
		tputs(tgetstr("ve", 0), 1, &ft_tputschar);
		tputs(tgetstr("te", 0), 1, &ft_tputschar);
		return ;
	}
	if (tgetent(0, getenv("TERM")) <= 0)
		ft_err_conf_exit("Error : Terminal not found");
	if (!tgetstr("cl", 0) || !tgetstr("vi", 0) || !tgetstr("ve", 0)
	|| !tgetstr("ti", 0) || !tgetstr("te", 0))
		ft_err_conf_exit("Error : Terminal capacity");
	if (tcgetattr(STDERR_FILENO, &term) == -1)
		ft_err_conf_exit("Error : Can not get terminal attribute");
	saved = term;
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	tcsetattr(STDERR_FILENO, TCSANOW, &term);
	tputs(tgetstr("vi", 0), 1, &ft_tputschar);
	tputs(tgetstr("ti", 0), 1, &ft_tputschar);
}
