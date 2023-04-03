# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egervais <egervais@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/03 19:11:19 by egervais          #+#    #+#              #
#    Updated: 2023/03/28 13:28:16 by egervais         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= fractol
CFLAGS	:= -Wextra -Wall -Wunreachable-code -Wno-unused-parameter -Wno-unused-result -O3 -fsanitize=address -g
SRCS	:= test1.c
OBJS	:= ${SRCS:.c=.o}
LIBMLX	:= ../../../MLX42/
LIBS	:= $(LIBMLX)build/libmlx42.a -Iinclude -L "/Users/egervais/.brew/opt/glfw/lib/" -lglfw -framework Cocoa -framework OpenGL -framework IOKit

all: $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build

$(NAME): libmlx $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	@echo "Compiling: $(notdir $<)"
	@$(CC) $(CFLAGS) -I ../include -o $@ -c $<

run: $(NAME)
	@./$(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean $(NAME)