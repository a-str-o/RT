# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/22 16:14:13 by yoelguer          #+#    #+#              #
#    Updated: 2020/02/22 15:55:05 by yoelguer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= 	main.c \
			vector.c\
			vector2.c\
			vector3.c\
			file.c\
			data_camera.c\
			data_sphere.c\
			data_malloc.c\
			data_plane.c\
			data_light.c\
			data_cone.c\
			data_cylinder.c\
			ft_atof.c\
			val.c\
			data_paraploid.c\
			data_ellipsoid.c\
			data_cube.c\
			sdl.c\
			raytrace.c\
			

HEADER = 	header/data.h\
			header/rt.h\
			header/vector.h\

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

NAME 	= RT

CFLAGS = -Wall -Wextra -Werror -g

INCLUDE	= -I /Users/$$USER/.brew/Cellar/sdl2/2.0.14_1/include \
	-I /Users/$$USER/.brew/Cellar/sdl2_image/2.0.5/include \

LIB = -L /Users/$$USER/.brew/Cellar/sdl2/2.0.14_1/lib \
	-L /Users/$$USER/.brew/Cellar/sdl2_image/2.0.5/lib \

SDL = `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image 

SRC_DIR = ./src

OBJ_DIR = ./obj

LIBFT_DIR = ./libft

LIBFT_LIB = $(LIBFT_DIR)/libft.a


CC = @gcc 

all : $(NAME)

$(LIBFT_LIB): force
	@make -C $(LIBFT_DIR)

force:


$(NAME) : $(LIBFT_LIB) $(OBJ)
	@gcc $(OBJ) $(CFLAGS) -o $(NAME) $(INCLUDE) $(LIB)  $(SDL) $(LIBFT_LIB)
	@echo "\033[92mDone for RTV1\033[0m"

$(OBJ_DIR):
	@-mkdir $(OBJ_DIR)

$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	@gcc -c  $(INCLUDE) $< -o $@ 

clean :
	@make clean -C ./libft/
	@rm -rf $(OBJ_DIR)

fclean : clean
	@make fclean -C ./libft/
	@rm -rf $(NAME)

norme:
	@norminette $(SRC_DIR)

re : fclean all
