# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/27 17:07:31 by vmercadi          #+#    #+#              #
#    Updated: 2018/04/23 22:46:32 by cquillet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

SRC = srcs/maintest2.c srcs/error.c srcs/event.c srcs/vect_calc1.c \
    srcs/vect_calc2.c srcs/vect_utils.c srcs/utils.c srcs/init.c \
    srcs/intersections.c srcs/color.c srcs/lux.c srcs/scene.c srcs/matrice.c \
    srcs/cam.c srcs/vector.c srcs/to_fdf.c srcs/obj.c srcs/calc_obj.c     \
    srcs/action.c srcs/event_obj.c srcs/parsing.c srcs/help.c \
    srcs/color_calc.c srcs/color_utils.c srcs/event_move.c srcs/init_obj.c \
    srcs/init_data.c srcs/init_sheit.c srcs/parse_utils.c srcs/lux_calc.c \
    srcs/draw.c srcs/event_screen.c srcs/cast_ray.c

INCLUDES = -I includes -I lib/libft -I lib/SDL2/Headers
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)
MFLAGS = -lpthread -O3
SDL = lib/SDL2/SDL2
SRCO = $(SRC:%.c=%.o)
LIB = lib/libft/libft.a
H = includes/rtv1.h includes/color.h

#Installing SDL2_ttf and SDL2_image and move SDL2 if necessary
SDL_SDL_NAME =SDL2
SDL_SDL = $(shell ls ~/Library/Frameworks | grep "^SDL2$$")

LIBS =

ifeq "$(SDL_SDL)" ""
LIBS += $(SDL_SDL_NAME)
endif

.PHONY: all re clean fclean it reit ultra $(SDL_SDL_NAME)

all: $(NAME)

$(NAME): $(LIBS) $(H) $(SRC)
	@make -s -C lib/libft/
	@echo "\033[32;4mLIBFT\x1b[0m	\033[32;7mcompiled\x1b[0m"
	@gcc $(CFLAGS) $(SDL) $(LIB) -o $(NAME) $(SRC) $(MFLAGS)
	@echo "\033[32;4mRTV1\x1b[0m	\033[32;7mcompiled\x1b[0m"
	@echo "\033[32;3m-----------------------------------"
	@echo "Things went great ! For this time.."
	@echo "-----------------------------------\x1b[0m"

$(SDL_SDL_NAME):
	$(shell mkdir -p ~/library/Frameworks && cp -rf ./lib/SDL2/ ~/library/Frameworks)

it: all
	@./RTv1

clean:
	@rm -rf $(SRCO)
	@make clean -s -C lib/libft/

fclean: clean
	@rm -rf $(NAME)

re: fclean all

ultra: all clean

reit: re clean
	@./RTv1

