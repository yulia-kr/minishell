# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/30 15:08:09 by cudoh             #+#    #+#              #
#    Updated: 2022/12/26 21:39:33 by cudoh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SRCS:= $(shell ls *.c | grep -v lst | xargs)

SRCS:= main.c ft_ms_env_get_path_dirs.c ft_ms_sys_open_fd.c \
				ft_ms_sys_chdir.c ft_ms_sys_exit.c ft_ms_sys_env.c \
				ft_ms_sys_export.c ft_ms_sys_pwd.c ft_ms_sys_unset.c \
				ft_ms_sys_echo.c \
				\
				ft_ms_run_cmd.c  ft_ms_cmd_exec.c ft_ms_var_id_n_env_var.c \
				ft_ms_cmd_pipe.c  ft_ms_cmd_list.c ft_ms_cmd_redir.c \
				ft_ms_find_prog.c ft_ms_handle_status.c ft_ms_handle_sig.c \
				ft_ms_chk_quote.c ft_ms_handle_quotes_n_dollar.c \
				ft_ms_handle_env_var.c \
				ft_ms_env_lst_init.c ft_ms_env_get_var.c ft_ms_env_upd.c \
				ft_ms_env_add_var.c ft_ms_env_arr_sort.c \
				ft_ms_env_lst_to_arr_ptr.c ft_ms_free_ptr_to_arrs.c\
				ft_ms_free_lst.c ft_ms_free_rsc.c ft_ms_debug_print_cmd.c \
				ft_ms_dup_ptr_to_arr.c ft_ms_strcmp.c ft_ms_rst_free_ptr_to_arr.c \
				ft_ms_sys_call_parent.c ft_ms_sys_call_child.c ft_ms_prompt_usr.c \
				ft_ms_parse_usr_cmd.c ft_ms_append_str_to_str.c \
				ft_ms_export_on_parent.c \
				\
		parser.c ft_parser_init_var.c   ft_parser_get_max_args.c \
				 ft_parser_get_token.c  ft_parser_peek.c ft_parser_parse.c \
				 ft_parser_parse_line.c ft_parser_parse_pipe.c \
				 ft_parser_parse_exec.c ft_parser_parse_redir.c \
				 ft_parser_null_term.c ft_free_parser_tree.c \
		ft_term_config_init.c ft_term_config_set.c \


OBJS:= $(SRCS:.c=.o)

NAME = minishell
USR_LIB = libft.a
USR_LIB_PATH = ./libft

CC = cc
#CFLAGS = -Werror -Wall -Wextra -O3 -g #-fsanitize=address
CFLAGS = -Werror -Wall -Wextra -g
ifeq ($(shell uname), Linux)
# Compilation flag for Linux
	LIBFLAGS_STATIC = -L$(USR_LIB_PATH) -lft  -lreadline -lncurses
	INCLUDES = -I./ -I$(USR_LIB_PATH) 
else
# Compilation flag for MacOS (42 wolfsburg)
	LIBFLAGS_STATIC = -L$(USR_LIB_PATH) -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline
	INCLUDES = -I./ -I$(USR_LIB_PATH) -I $(HOME)/goinfre/.brew/opt/readline/include/
endif

NAME : all
all : $(NAME)
$(NAME) : $(OBJS) $(USR_LIB)
	@echo "\033[1;33mCompiling Executables: $(NAME) \033[0m"
	$(CC) $^ $(LIBFLAGS_STATIC) $(CFLAGS) $(INCLUDES) -o $@
	@echo; echo "\033[1;32mCompilation Successful. \033[0m"
	@echo; echo

	
# obj files output
%.o : %.c
	@echo
	@echo "\033[1;33mCompiling OBJ files \033[0m"
	$(CC) -c $^ $(CFLAGS) $(INCLUDES) -o $@
	@echo


$(USR_LIB) :
	@echo
#	$(AR) $(LIBFLAGS_STATIC) $@ $^						# create the library file for linking
	@echo "\033[1;33mCompiling LIBFT Library \033[0m"
	cd ./libft; make > /dev/null; cp libft.a ../; cd ..	
	@echo												# print new line on screen

	

# remove all object files
fclean:
	rm -rf *.o
	cd ./libft; make fclean; cd ..;

# remove final target files
clean: fclean
	rm -rf $(NAME)
	rm -rf *.a
	cd ./libft; make clean; cd ..;

# recompile everything
re: clean all

.PHONY : all fclean clean re 
