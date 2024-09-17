# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/01 12:07:58 by meserghi          #+#    #+#              #
#    Updated: 2024/09/17 14:54:54 by meserghi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

lib = Mandatory/lib/ft_strdup.c Mandatory/lib/ft_strlen.c Mandatory/lib/free_arr.c Mandatory/lib/ft_strjoin.c Mandatory/lib/ft_split.c\
	Mandatory/lib/ft_atoi.c Mandatory/lib/ft_strncmp.c Mandatory/lib/ft_strtrim.c

utils = Mandatory/utils/mlx_hook.c Mandatory/utils/mlx_init.c Mandatory/utils/init_textures.c\
		Mandatory/utils/rendering.c Mandatory/utils/get_color.c Mandatory/utils/my_free.c

ray_casting = Mandatory/ray_casting/ray_casting.c Mandatory/ray_casting/find_intersection.c

handel_input = Mandatory/handel_cub3d/get_next_line_utils.c\
	Mandatory/handel_cub3d/get_next_line.c Mandatory/handel_cub3d/ft_lenmap.c Mandatory/handel_cub3d/handel_Cub3.c\
	Mandatory/handel_cub3d/ft_utils.c Mandatory/handel_cub3d/ft_checkColours.c Mandatory/handel_cub3d/ft_handelline.c\
	Mandatory/handel_cub3d/read_lines.c Mandatory/handel_cub3d/ft_spand0.c Mandatory/handel_cub3d/check_previous.c

lib_bonus = Bonus/lib/ft_strdup.c Bonus/lib/ft_strlen.c Bonus/lib/free_arr.c Bonus/lib/ft_memset.c \
	Bonus/lib/ft_strjoin.c Bonus/lib/ft_itoa.c Mandatory/lib/ft_split.c\
	Mandatory/lib/ft_atoi.c bonus/lib/ft_strncmp.c

utils_bonus = bonus/utils/mlx_hook_bonus.c bonus/utils/mlx_init_bonus.c bonus/utils/init_textures_bonus.c \
	bonus/utils/rendring_bonus.c bonus/utils/get_color_bonus.c bonus/utils/math_utils_bonus.c\
	bonus/utils/is_wall_bonus.c bonus/utils/rendring_utils_bonus.c bonus/utils/my_free_bonus.c

ray_casting_bonus = bonus/ray_casting/ray_casting_bonus.c bonus/ray_casting/find_intersection_bonus.c\
					bonus/ray_casting/first_intersection_bonus.c

handel_input_bonus = Bonus/handel_cub3d_bonus/get_next_line_utils.c\
	Bonus/handel_cub3d_bonus/get_next_line.c Bonus/handel_cub3d_bonus/ft_lenmap.c Bonus/handel_cub3d_bonus/handel_Cub3.c\
	Bonus/handel_cub3d_bonus/ft_utils.c Bonus/handel_cub3d_bonus/ft_checkColours.c Bonus/handel_cub3d_bonus/ft_handelline.c\
	Bonus/handel_cub3d_bonus/read_lines.c Bonus/handel_cub3d_bonus/ft_spand0.c Bonus/handel_cub3d_bonus/check_previous.c

GREEN = \033[1;32m
RED = \033[1;31m
BLUE = \033[1;34m
YELL = \033[0;33m
STOP_C = \033[0m

FILE = ${lib} ${utils} ${ray_casting} ${handel_input} Mandatory/Cub3D.c

FILE_BONUS = ${lib_bonus} ${utils_bonus} ${ray_casting_bonus} ${handel_input_bonus} bonus/Cub3D_bonus.c


FILE_OBJ = ${FILE:.c=.o}

FILE_OBJ_BONUS = ${FILE_BONUS:.c=.o}

FLAGS = -Wall -Wextra -Werror #-O3 -fsanitize=address -g

# Linux :
# FMLX = -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm

# MacOS :
FMLX = mlx/libmlx.a  -framework OpenGL -framework AppKit

NAME = cub3D

NAME_BONUS = cub3D_bonus

all : ${NAME}
	@echo "${GREEN}Cub3D has been built ...${STOP_C}"

%.o : %.c Mandatory/Cub3D.h Bonus/Cub3D_bonus.h
	@cc ${FLAGS} -Imlx -O3 -c $< -o $@
	@echo "${BLUE}$@ has been built${STOP_C}"

${NAME} : ${FILE_OBJ}
	@cc ${FLAGS} ${FILE_OBJ} ${FMLX} -o ${NAME}

${NAME_BONUS} : ${FILE_OBJ_BONUS}
	@cc ${FLAGS} ${FILE_OBJ_BONUS} ${FMLX} -o ${NAME_BONUS}

bonus : ${NAME_BONUS}
	@echo "${GREEN}Cub3D Bonus has been built ...${STOP_C}"

clean :
	@rm -f ${FILE_OBJ} ${FILE_OBJ_BONUS}
	@echo "${RED}Cleaned object files${STOP_C}"

fclean : clean
	@rm -f ${NAME} ${NAME_BONUS}
	@echo "${RED}Fully cleaned${STOP_C}"

re : fclean all
