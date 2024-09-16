# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/11 10:23:22 by rpandipe          #+#    #+#              #
#    Updated: 2024/09/16 14:50:19 by rpandipe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cube3D
LIBFT		= libft.a
CC			= cc
CFLAG		= -Wall -Werror -Wextra -g
RM 			= rm -rf
SRCS		= raytracing.c raymath.c
OBJS		= $(SRCS:.c=.o)

all : $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

$(NAME): $(OBJS)
	make -C libft
	cp libft/$(LIBFT) .
	$(CC) $(OBJS) $(LIBFT) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	cd libft && $(MAKE) clean
	$(RM) $(OBJS)

fclean:	clean
	cd libft && $(MAKE) fclean
	$(RM) $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re