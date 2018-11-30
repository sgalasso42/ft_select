/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 22:35:42 by sgalasso          #+#    #+#             */
/*   Updated: 2018/11/30 02:23:32 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		ft_exit(int signo)
{
	(void)signo;
	ft_new_term_conf(1);
	ft_lst_del(ft_singleton());
	exit(EXIT_SUCCESS);
}

static void		ft_sigtstp(int signo)
{
	struct termios		term;
	char				c[2];

	(void)signo;
	tcgetattr(STDERR_FILENO, &term);
	c[0] = term.c_cc[VSUSP];
	c[1] = '\0';
	ft_new_term_conf(1);
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDERR_FILENO, TIOCSTI, c);
}

static void		ft_sigcont(int signo)
{
	(void)signo;
	signal(SIGTSTP, ft_sigtstp);
	ft_new_term_conf(0);
	ft_display_args(ft_singleton());
}

static void		ft_redim(int signo)
{
	(void)signo;
	tputs(tgetstr("cl", 0), 1, &ft_tputschar);
	ft_display_args(ft_singleton());
}

void			ft_get_signal(void)
{
	signal(SIGHUP, ft_exit);
	signal(SIGINT, ft_exit);
	signal(SIGTERM, ft_exit);
	signal(SIGTSTP, ft_sigtstp);
	signal(SIGCONT, ft_sigcont);
	signal(SIGTTIN, ft_exit);
	signal(SIGTTOU, ft_exit);
	signal(SIGXCPU, ft_exit);
	signal(SIGPROF, ft_exit);
	signal(SIGWINCH, ft_redim);
}
