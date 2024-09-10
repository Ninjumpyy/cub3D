# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thomas <thomas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/26 16:10:23 by tle-moel          #+#    #+#              #
#    Updated: 2024/09/10 10:41:16 by thomas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
LIBFT = libft.a
CC = cc
CFLAG += -Wall -Wextra -Werror
LFLAG = -Llibft -lft
LDFLAG = -Lminilibx-linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -LX11 -lm -lz
RM = rm -rf
SRCS = cub3D.c cub3D_utils.c parsing.c parsing_utils.c parse_info_utils.c \
	   parsing_map.c cub3D_err.c cub3D_free.c parse_map_utils.c
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

