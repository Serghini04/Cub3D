# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/01 12:07:58 by meserghi          #+#    #+#              #
#    Updated: 2024/09/07 16:06:20 by meserghi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

lib = lib/ft_strdup.c lib/ft_strlen.c lib/free_arr.c lib/ft_strjoin.c lib/ft_split.c\
	lib/ft_atoi.c

utils = utils/mlx_hook.c utils/mlx_init.c utils/init_textures.c utils/rendering.c\
		utils/get_color.c

ray_casting = ray_casting/ray_casting.c ray_casting/find_intersection.c

handel_input = handel_cub3d/ft_strncmp.c handel_cub3d/get_next_line_utils.c\
	handel_cub3d/get_next_line.c handel_cub3d/ft_lenmap.c handel_cub3d/handel_Cub3.c\
	handel_cub3d/ft_utils.c handel_cub3d/ft_checkColours.c handel_cub3d/ft_handelline.c\
	handel_Cub3d/read_lines.c handel_Cub3d/ft_spand0.c

GREEN = \033[1;32m
RED = \033[1;31m
BLUE = \033[1;34m
YELL = \033[0;33m
STOP_C = \033[0m

FILE = ${lib} ${utils} ${ray_casting} ${handel_input} Cub3D.c

FILE_OBJ = ${FILE:.c=.o}

FLAGS = -Wall -Wextra -Werror -O3 #-fsanitize=address -g

# Linux :
# FMLX = -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm
# MacOS :
FMLX = mlx/libmlx.a  -framework OpenGL -framework AppKit

NAME = cub3D

all : ${NAME}
	@echo "${GREEN}Cub3D has been built ...${STOP_C}"

%.o : %.c Cub3D.h
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

