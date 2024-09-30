# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thomas <thomas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/26 16:10:23 by tle-moel          #+#    #+#              #
#    Updated: 2024/09/30 17:50:32 by thomas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
LIBFT = libft.a
CC = cc
CFLAG += -Wall -Wextra -Werror
LFLAG = -Llibft -lft
LDFLAG = -Lminilibx-linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
RM = rm -rf
SRCS = cub3D.c cub3D_utils.c cub3D_err.c cub3D_free.c cub3D_events.c \
	   cub3D_draw.c $(wildcard parsing/*.c)
OBJDIR = objs
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

# ANSI color codes
GREEN       = \033[0;32m
RED         = \033[0;31m
NC          = \033[0m

all: check_minilibx $(NAME)
	@echo -e '${GREEN}Build complete!${NC}'

check_minilibx:
ifneq ($(wildcard minilibx-linux),)
	@make -C minilibx-linux
else
	@echo -e '${RED}Error: minilibx-linux folder not found!${NC}'
	@exit 1
endif

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAG) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C libft
	@cp libft/$(LIBFT) .
	$(CC) $(OBJS) $(CFLAG) $(LDFLAG) $(LFLAG) -o $(NAME)
	@echo -ne '\n'

clean:
	$(MAKE) clean -C ./libft
ifneq ($(wildcard minilibx-linux),)
	$(MAKE)	clean -C ./minilibx-linux
endif
	$(RM) $(OBJDIR)
	@echo -e '${RED}Clean complete!${NC}'

fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME) $(LIBFT)
	@echo -e '${RED}Build deleted!${NC}'
	@echo -ne '\n'

re: fclean all

.PHONY: all check_minilibx clean fclean re

