# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/01 12:07:58 by meserghi          #+#    #+#              #
#    Updated: 2024/06/13 14:22:30 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

lib = lib/ft_strdup.c lib/ft_strlen.c lib/free_arr.c

utils = utils/mlx_hook.c utils/mlx_init.c

ray_casting = ray_casting/ray_casting.c

GREEN = \033[1;32m
RED = \033[1;31m
BLUE = \033[1;34m
YELL = \033[0;33m
STOP_C = \033[0m

FILE = ${lib} ${utils} ${ray_casting} Cub3D.c

FILE_OBJ = ${FILE:.c=.o}

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g

NAME = Cub3D

all : ${NAME}
	@echo "${GREEN}Cub3D has been built ...${STOP_C}"

%.o : %.c Cub3D.h
	@cc ${FLAGS} -Imlx_linux -O3 -c $< -o $@
	@echo "${BLUE}$@ has been built${NC}"

${NAME} : ${FILE_OBJ}
	cc ${FLAGS} ${FILE_OBJ} -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -o ${NAME}

clean :
	@rm -f ${FILE_OBJ}
	@echo "${RED}Cleaned object files${STOP_C}"

fclean : clean
	@rm -f ${NAME}
	@echo "${RED}Fully cleaned${STOP_C}"

re : fclean all
