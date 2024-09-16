# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/22 10:22:20 by rpandipe          #+#    #+#              #
#    Updated: 2024/08/28 16:47:12 by tle-moel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= cc
CFLAGS	= -Wall -Werror -Wextra
RM	= rm -rf
SRCS	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	  ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	  ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	  ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	  ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
	  ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	  ft_printf.c ft_printstr.c ft_printnbr.c ft_printmem.c \
	  get_next_line.c get_next_line_utils.c ft_strcmp.c	  
SRCSB	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
	  ft_lstmap.c ft_bonus1.c ft_bonussorter.c ft_savemem.c ft_savenbr.c \
	  ft_savestr.c ft_width.c ft_nbraux.c ft_bonus2.c ft_precision.c \
	  ft_plusaux.c ft_dealcomb.c
OBJS	= $(SRCS:.c=.o)
OBJSB	= $(SRCSB:.c=.o)
NAME	= libft.a
LIBC	= ar rcs

all: $(NAME)

$(NAME): $(OBJS) $(OBJSB)
	$(LIBC) $(NAME) $(OBJS) $(OBJSB)

.c.o: 
	$(CC) $(CFLAGS) -c $< -o  ${<:.c=.o}

bonus: $(NAME) $(OBJSB)
	$(LIBC) $(NAME) $(OBJSB)

clean:
	$(RM) $(OBJS) $(OBJSB)

fclean: clean
	$(RM) $(NAME) $(bonus)

re: fclean all

.PHONY: all bonus clean fclean re

