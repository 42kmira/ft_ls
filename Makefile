# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmira <kmira@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/30 09:04:56 by kmira             #+#    #+#              #
#    Updated: 2019/11/08 11:50:17 by kmira            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror -march=native
# -O2 -flto -march=native
NAME = ft_ls
LIBRARY = libft/libft.a
INCLUDES = -I includes

FILES = \
			cmp_functions \
			debug \
			flag_parser \
			free_tree \
			get_inodes \
			io_out \
			list_directory \
			ls_error \
			ls_utils \
			main \

C_FILES = $(addprefix srcs/, $(FILES))

SRCS = $(addsuffix .c, $(C_FILES))
OBJS = $(addsuffix .o, $(FILES))

all: $(NAME)

$(NAME): $(LIBRARY) $(OBJS)
	@echo "\033[32m""Making your ft_ls executable"
	@gcc -o $(NAME) $(OBJS) $(LIBRARY)
	@echo "\033[32m""Done!"

$(LIBRARY):
	make -C libft/
	make clean -C libft/

$(OBJS):
	@gcc $(FLAGS) $(INCLUDES) -c $(SRCS)

clean:
	@echo "Cleaning your .o files"
	@rm -f libft.a
	@rm -f $(OBJS)

fclean: clean
	@make -C libft/ fclean
	@rm -f $(NAME)

re: fclean all

rebuild: clean
	@rm -f $(NAME)
	@make all
	@make clean
	@clear

.PHONY: clean
