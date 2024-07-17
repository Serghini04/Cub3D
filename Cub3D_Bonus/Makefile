# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/01 12:07:58 by meserghi          #+#    #+#              #
#    Updated: 2024/07/17 21:36:45 by meserghi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

lib = lib/ft_strdup.c lib/ft_strlen.c lib/free_arr.c lib/ft_memset.c \
	lib/ft_strjoin.c lib/ft_itoa.c

utils = utils/mlx_hook_bonus.c utils/mlx_init_bonus.c utils/init_textures_bonus.c \
	utils/rendering_bonus.c utils/get_color_bonus.c

ray_casting = ray_casting/ray_casting_bonus.c ray_casting/find_intersection_bonus.c

GREEN = \033[1;32m
RED = \033[1;31m
BLUE = \033[1;34m
YELL = \033[0;33m
STOP_C = \033[0m

FILE = ${lib} ${utils} ${ray_casting} Cub3D_bonus.c

FILE_OBJ = ${FILE:.c=.o}

FLAGS = -Wall -Wextra -Werror -O3 -fsanitize=address -g

# Linux :
# FMLX = -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm
# MacOS :
FMLX = -lmlx -framework OpenGL -framework AppKit

NAME = cub3D_bonus

all : ${NAME}
	@echo "${GREEN}Cub3D has been built ...${STOP_C}"

%.o : %.c Cub3D_bonus.h
	@cc ${FLAGS} -Imlx -O3 -c $< -o $@
	@echo "${BLUE}$@ has been built${NC}"

${NAME} : ${FILE_OBJ}
	cc ${FLAGS} ${FILE_OBJ} ${FMLX} -o ${NAME}

clean :
	@rm -f ${FILE_OBJ}
	@echo "${RED}Cleaned object files${STOP_C}"

fclean : clean
	@rm -f ${NAME}
	@echo "${RED}Fully cleaned${STOP_C}"

re : fclean all
