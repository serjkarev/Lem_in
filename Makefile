#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/01 14:41:37 by skarev            #+#    #+#              #
#    Updated: 2018/12/26 12:15:36 by skarev           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = lem-in

CFLAG = -g -O3 -Wall -Wextra

SRCS = main.c parsing.c tools.c tools_2.c find_ways.c \
		lgnl.c cut_n_pack.c run_ants_run.c tools_3.c \
		choose_pack.c helpers.c tools_4.c tools_5.c

LIBS = ./libft/libft.a

all: $(NAME)

$(NAME): $(SRCS)
	@make -C libft
	@gcc $(CFLAG) -o $(NAME) $(SRCS) $(LIBS)

clean:
		@make -C libft clean

fclean: clean
		@make -C libft fclean
		@/bin/rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean re
