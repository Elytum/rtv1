# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achazal <achazal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 11:54:29 by achazal           #+#    #+#              #
#    Updated: 2014/12/13 12:55:35 by achazal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -------------Compilateur------------------#
CC		=	gcc
#--------------Name-------------------------#
NAME	=	fdf
MYPATH	=	$(HOME)
#--------------Sources----------------------#
FILES	=	describe.c					\
			scene.c						\
			tools.c						\
			scene/describe.c			\
			plane/describe.c			\
			sphere/describe.c			\
			cylinder/describe.c			\
			cone/describe.c

INC		=	-I./include
CCFLAGS	=	-Wall -Wextra -Werror -g
LDFLAGS	=	

SRCS	=	$(addprefix srcs/, $(FILES))
OBJS	=	$(SRCS:.c=.o)

#--------------Actions----------------------#

.PHONY: MLX $(NAME) clean fclean re create describe

all: $(NAME)

MLX:
	ls

$(NAME): MLX $(OBJS)
	$(CC) $(CCFLAGS) $(LDFLAGS) $(INC) $(OBJS) -o $(NAME) -O3

create:
	$(CC) $(CCFLAGS) $(LDFLAGS) $(INC) $(OBJS) -o create -O3

describe:
	$(CC) $(CCFLAGS) $(LDFLAGS) $(INC) $(OBJS) -o describe -O3

draw:
	$(CC) $(CCFLAGS) $(LDFLAGS) $(INC) $(OBJS) -o draw -O3

%.o: %.c
	$(CC) $(CCFLAGS) -c  $(INC) $< -o $@
	
clean:
	make clean -C minilibx_macos
	rm -f $(OBJS)
	
fclean:	clean
	make clean -C minilibx_macos
	rm -f $(NAME)

re: fclean all
	make re -C minilibx_macos