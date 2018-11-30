/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 19:29:29 by sgalasso          #+#    #+#             */
/*   Updated: 2018/11/30 02:26:37 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# define C_UNDER "\033[4m"
# define C_COLOR "\033[7m"
# define C_NONE "\033[0m"

# define KEY_ESC 27
# define KEY_SPC 32
# define KEY_DEL 2117294875L
# define KEY_BSP 127
# define KEY_ENT 10
# define KEY_LE	4479771
# define KEY_UP	4283163
# define KEY_RI	4414235
# define KEY_DO	4348699

# include "../libft/libft.h"
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <signal.h>

typedef struct s_elem	t_elem;
typedef struct s_data	t_data;

struct					s_elem
{
	int			color;
	int			under;
	char		*name;
	t_elem		*prev;
	t_elem		*next;
};

struct					s_data
{
	t_elem		*elem;
	t_elem		*last;
	t_elem		*current;
	int			nb_elems;
	int			max_size;
};

void					ft_escape(t_data *data);
int						ft_tputschar(int c);
t_elem					*ft_singleton(void);
void					ft_return_lst(t_data *data);

int						ft_lst_len(t_elem *elem);
void					ft_lst_del(t_elem *elem);
void					ft_lst_new(char *name, t_data *data);
void					ft_lst_add(char *name, t_data *data);

void					ft_get_signal(void);
void					ft_event(long line, t_data *data);
void					ft_display_args(t_elem *elem);
void					ft_new_term_conf(int reset);

#endif
