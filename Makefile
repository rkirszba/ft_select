# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 12:50:11 by rkirszba          #+#    #+#              #
#    Updated: 2019/07/01 11:18:34 by rkirszba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select 

LIB_PATH = ./libft

SRC_PATH = src
SRC_NAME = ft_select.c\
		   analyze_char.c\
		   analyze_char_end.c\
		   arguments_functions.c\
		   cmd_functions.c\
		   cmd_functions_end.c\
		   errors.c\
		   errors_term.c\
		   free_functions.c\
		   init_structs.c\
		   signals_manager.c\
		   write_args.c\
		   write_arg.c

HEADER_PATH = ./includes/

OBJ_PATH = obj
OBJ_NAME = $(SRC_NAME:.c=.o)

CC = gcc
CCFLAGS = -Wall\
		  -Wextra\
		  -Werror

CPPFLAGS = -I $(HEADER_PATH) -MMD
LIBFLAGS = -L $(LIB_PATH) -lft -ltermcap

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: lib $(NAME)

lib:
	@make -C libft/

$(NAME): $(OBJ)
	@make -C libft/
	$(CC) $(CCFLAGS) $(LIBFLAGS) $^ -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CCFLAGS) $(CPPFLAGS) -o $@ -c $<

$(OBJ_PATH):
	@mkdir $(OBJ_PATH) 2> /dev/null || true

clean:
	@make clean -C libft/
	@rm -f $(OBJ) $(OBJ:.o=.d)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	@make fclean -C libft/
	@rm -f $(NAME)

re: fclean
	$(MAKE) all

norme:
	norminette $(SRC)
	norminette $(HEADER_PATH)

.PHONY: lib make clean fclean re san

-include $(OBJ:.o=.d)
