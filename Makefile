# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/01 12:07:58 by meserghi          #+#    #+#              #
#    Updated: 2024/09/07 17:14:21 by meserghi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

lib = Cub3D/lib/ft_strdup.c Cub3D/lib/ft_strlen.c Cub3D/lib/free_arr.c Cub3D/lib/ft_strjoin.c Cub3D/lib/ft_split.c\
	Cub3D/lib/ft_atoi.c

utils = Cub3D/utils/mlx_hook.c Cub3D/utils/mlx_init.c Cub3D/utils/init_textures.c Cub3D/utils/rendering.c\
		Cub3D/utils/get_color.c

ray_casting = Cub3D/ray_casting/ray_casting.c Cub3D/ray_casting/find_intersection.c

handel_input = Cub3D_Bonus/Cub3D/handel_Cub3D_Bonus/cub3d/ft_strncmp.c Cub3D_Bonus/Cub3D/handel_Cub3D_Bonus/cub3d/get_next_line_utils.c\
	Cub3D_Bonus/Cub3D/handel_Cub3D_Bonus/cub3d/get_next_line.c Cub3D_Bonus/Cub3D/handel_Cub3D_Bonus/cub3d/ft_lenmap.c Cub3D_Bonus/Cub3D/handel_Cub3D_Bonus/cub3d/handel_Cub3.c\
	Cub3D_Bonus/Cub3D/handel_Cub3D_Bonus/cub3d/ft_utils.c Cub3D_Bonus/Cub3D/handel_Cub3D_Bonus/cub3d/ft_checkColours.c Cub3D_Bonus/Cub3D/handel_Cub3D_Bonus/cub3d/ft_handelline.c\
	Cub3D_Bonus/Cub3D/handel_Cub3D_Bonus/Cub3d/read_lines.c Cub3D_Bonus/Cub3D/handel_Cub3D_Bonus/Cub3d/ft_spand0.c

lib_bonus = Cub3D_Bonus/lib/ft_strdup.c Cub3D_Bonus/lib/ft_strlen.c Cub3D_Bonus/lib/free_arr.c Cub3D_Bonus/lib/ft_memset.c \
	Cub3D_Bonus/lib/ft_strjoin.c Cub3D_Bonus/lib/ft_itoa.c

utils_bonus = Cub3D_bonus/utils/mlx_hook_bonus.c Cub3D_bonus/utils/mlx_init_bonus.c Cub3D_bonus/utils/init_textures_bonus.c \
	Cub3D_bonus/utils/rendering_bonus.c Cub3D_bonus/utils/get_color_bonus.c

ray_casting_bonus = Cub3D_bonus/ray_casting/ray_casting_bonus.c Cub3D_bonus/ray_casting/find_intersection_bonus.c

GREEN = \033[1;32m
RED = \033[1;31m
BLUE = \033[1;34m
YELL = \033[0;33m
STOP_C = \033[0m

FILE = ${lib} ${utils} ${ray_casting} ${handel_input} Cub3D.c

FILE_BONUS = ${lib_bonus} ${utils_bonus} ${ray_casting_bonus} Cub3D_bonus.c


FILE_OBJ = ${FILE:.c=.o}

FILE_OBJ_BONUS = ${FILE_BONUS:.c=.o}

FLAGS = -Wall -Wextra -Werror -O3 #-fsanitize=address -g

# Linux :
# FMLX = -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm
# MacOS :
FMLX = mlx/libmlx.a  -framework OpenGL -framework AppKit

NAME = cub3D

NAME_BONUS = cub3D_bonus

all : ${NAME}
	@echo "${GREEN}Cub3D has been built ...${STOP_C}"

%.o : %.c Cub3D.h
	@cc ${FLAGS} -Imlx -O3 -c $< -o $@
	@echo "${BLUE}$@ has been built${NC}"

%_bonus.o : %_bonus.c Cub3D_bonus.h
	@cc ${FLAGS} -Imlx -O3 -c $< -o $@
	@echo "${BLUE}$@ has been built${NC}"

${NAME} : ${FILE_OBJ}
	cc ${FLAGS} ${FILE_OBJ} ${FMLX} -o ${NAME}

${NAME_BONUS} : ${FILE_OBJ_BONUS}
	cc ${FLAGS} ${FILE_OBJ_BONUS} ${FMLX} -o ${NAME_BONUS}

bonus : {NAME_BONUS}
	@echo "${GREEN}Cub3D Bonus has been built ...${STOP_C}"

clean :
	@rm -f ${FILE_OBJ} ${FILE_OBJ_BONUS}
	@echo "${RED}Cleaned object files${STOP_C}"

fclean : clean
	@rm -f ${NAME}
	@echo "${RED}Fully cleaned${STOP_C}"

re : fclean all
