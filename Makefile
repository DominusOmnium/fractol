# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 12:08:40 by dkathlee          #+#    #+#              #
#    Updated: 2019/12/04 12:00:52 by dkathlee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRCDIR = srcs/
INCDIR = includes/
OBJDIR = obj/

SRCS =	main.c init.c draw.c color.c mandelbrot.c julia.c keyboard_control.c \
		mouse_control.c load_cl_file.c init_opencl.c draw_gpu.c newton.c gui.c \

OBJS = $(addprefix $(OBJDIR), $(SRCS:.c=.o))

CC = gcc
CFLAGS = -Wall -Wextra -Werror

MLXDIR = mlx/
MLXLIB = $(addprefix $(MLXDIR), mlx.a)
MLXINC = -I $(MLXDIR)
MLXLNK = -l mlx -framework OpenGL -framework AppKit
OPENCLLNK = -framework OpenCL

FTDIR = libft/
FTLIB = $(addprefix $(FTDIR), libft.a)
FTINC = -I $(FTDIR)/includes
FTLNK = -L $(FTDIR) -l ft

all: obj $(FTLIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) $(FTINC) -I $(INCDIR) -o $@ -c $<

$(FTLIB):
	make -C $(FTDIR)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(OPENCLLNK) $(MLXLNK) $(FTLNK) -lm -o $(NAME)

linux:
	gcc -o q $(addprefix $(SRCDIR), $(SRCS)) $(FTLIB) -I $(INCDIR) $(MLXINC) $(FTINC) mlx_linux/libmlx_Linux.a -lm -lXext -lX11

clean:
	rm -rf $(OBJDIR)
	make -C $(FTDIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FTDIR) fclean

re: fclean all

.PHONY: clean fclean all re
