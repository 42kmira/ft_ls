# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmira <kmira@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/30 09:04:56 by kmira             #+#    #+#              #
#    Updated: 2019/06/02 23:51:35 by kmira            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror
NAME = ft_ls
LIBRARY = libft/libft.a

FILES = \
			errors \
			file_expansion \
			flag_parser \
			ls_entry \
			ls_recursion \
			main \
			output \
			utils \
			set_compare_function

SRCS = $(addsuffix .c, $(FILES))
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
	gcc $(FLAGS) -c $(SRCS)

clean:
	@echo "Cleaning your .o files"
	@rm -f libft.a
	@rm -f $(OBJS)

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all

rebuild: clean
	rm -f $(NAME)
	make all
	make clean
	clear
