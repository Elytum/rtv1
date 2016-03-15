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
# NAME	=	draw
MYPATH	=	$(HOME)
#--------------Sources----------------------#
FILES	=	scene.c						\
			tools.c						\
			scene/describe.c			\
			material/describe.c			\
			light/describe.c			\
			plane/describe.c			\
			sphere/describe.c			\
			cylinder/describe.c			\
			vec/vec3.c					\
			ray/ray.c					\
			cone/describe.c

DRAW_FILES		=	draw.c
CREATE_FILES	=	create.c
DESCRIBE_FILES	=	describe.c

INC		=	-I./include -I./minilibx_macos
CCFLAGS	=	-Wall -Wextra -Werror -g
LDFLAGS	=	-framework glut -framework Cocoa -framework OpenGL

SRCS	=			$(addprefix srcs/, $(FILES))
OBJS	=			$(SRCS:.c=.o)
DRAW_SRCS		=	$(addprefix srcs/, $(DRAW_FILES))
DRAW_OBJS		=	$(DRAW_SRCS:.c=.o)
CREATE_SRCS		=	$(addprefix srcs/, $(CREATE_FILES))
CREATE_OBJS		=	$(CREATE_SRCS:.c=.o)
DESCRIBE_SRCS	=	$(addprefix srcs/, $(DESCRIBE_FILES))
DESCRIBE_OBJS	=	$(DESCRIBE_SRCS:.c=.o)


#--------------Actions----------------------#

.PHONY: MLX MLX_RE $(NAME) clean fclean re create describe draw

all: $(NAME) draw create describe

MLX:
	make -C minilibx_macos

$(NAME): MLX
	create
	describe
	draw

draw: MLX $(OBJS) $(DRAW_OBJS)
	$(CC) $(CCFLAGS) $(LDFLAGS) $(INC) $(OBJS) $(DRAW_OBJS) minilibx_macos/libmlx.a -o draw -O3

create: MLX $(OBJS) $(CREATE_OBJS)
	$(CC) $(CCFLAGS) $(LDFLAGS) $(INC) $(OBJS) $(CREATE_OBJS) -o create -O3

describe: MLX $(OBJS) $(DESCRIBE_OBJS)
	$(CC) $(CCFLAGS) $(LDFLAGS) $(INC) $(OBJS) $(DESCRIBE_OBJS) -o describe -O3

%.o: %.c
	$(CC) $(CCFLAGS) -c  $(INC) $< -o $@
	
clean:
	make clean -C minilibx_macos
	rm -f $(OBJS)
	rm -f $(DRAW_OBJS)
	rm -f $(CREATE_OBJS)
	rm -f $(DESCRIBE_OBJS)
	
fclean:	clean
	rm -f create describe draw

re: fclean all