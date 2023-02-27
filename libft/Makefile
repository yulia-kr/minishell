# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/30 15:08:09 by cudoh             #+#    #+#              #
#    Updated: 2022/06/18 01:41:29 by cudoh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS:= $(shell ls *.c | xargs)
#SRCS:= $(shell ls *.c | grep -v lst | xargs)
#SRCS:= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c 	\
#			ft_isalpha.c ft_isascii.c ft_isdigit.c		\
#			ft_isprint.c ft_itoa.c ft_memchr.c			\
#			ft_memcmp.c ft_memcpy.c ft_memmove.c		\
#			ft_memset.c ft_putchar_fd.c ft_putendl_fd.c	\
#			ft_putnbr_fd.c ft_putstr_fd.c ft_split.c 	\
#			ft_strchr.c ft_strdup.c ft_striteri.c 		\
#			ft_strjoin.c ft_strlcat.c ft_strlcpy.c 		\
#			ft_strlen.c ft_strmapi.c ft_strncmp.c 		\
#			ft_strnstr.c ft_strrchr.c ft_strtrim.c 		\
#			ft_substr.c ft_tolower.c ft_toupper.c
#
##SRCS_BONUS:= $(shell ls *.c| grep lst | xargs)
#SRCS_BONUS:= ft_lstadd_back.c  ft_lstadd_front.c  ft_lstclear.c	\
#				ft_lstdelone.c  ft_lstiter.c  ft_lstlast.c 		\
#				ft_lstmap.c  ft_lstnew.c  ft_lstsize.c
 

#OBJS_BONUS:=$(SRCS_BONUS:.c=.o)
OBJS:=$(SRCS:.c=.o)

CC = cc
AR = ar
CFLAGS = -Werror -Wall -Wextra
LIBFLAGS_STATIC = rcs

NAME = libft.a
INCLUDES = -I ./


# obj files output
%.o : %.c
	$(CC) -c $^ $(CFLAGS) $(INCLUDES) -o $@

NAME : all
all : $(NAME)
$(NAME) : $(OBJS)
	@echo
	$(AR) $(LIBFLAGS_STATIC) $@ $^						# create the library file for linking
	@echo												# print new line on screen

#
#bonus: $(OBJS_BONUS)
#	@echo
#	$(AR) $(LIBFLAGS_STATIC) $(NAME) $^					# create the library file for linking
#	@echo												# print new line on screen


# remove all object files
fclean:
	rm -rf $(OBJS)
#	rm -rf $(OBJS) $(OBJS_BONUS)

# remove final target files
clean: fclean
	rm -rf $(NAME)

# recompile everything
re: clean all

.PHONY : all fclean clean re 
