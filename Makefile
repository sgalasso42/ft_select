# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/16 19:28:36 by sgalasso          #+#    #+#              #
#    Updated: 2018/11/30 02:26:39 by sgalasso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select

SRC = srcs/main.c \
	  srcs/ft_event.c \
	  srcs/ft_utils.c \
	  srcs/ft_get_signal.c \
	  srcs/ft_elem_lst.c \
	  srcs/ft_term_conf.c \
	  srcs/ft_display_args.c \

OBJ = $(SRC:.c=.o)

INCLUDES = includes/

all:	lib $(NAME)

$(NAME):	$(OBJ)
	gcc -Wall -Wextra -Werror -o $(NAME) -ltermcap \
	libft/libft.a $(OBJ) -I $(INCLUDES)

lib:
	make -C libft/

%.o: %.c $(INCLUDES)ft_select.h Makefile
	gcc -Wall -Wextra -Werror -o $@ -c $< -I $(INCLUDES)

clean:
	rm -f $(OBJ) && make -C libft/ clean

fclean:		clean
	rm -f $(NAME) && make -C libft/ fclean

re:			fclean all

.PHONY : all clean fclean re
