# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/27 17:07:31 by vmercadi          #+#    #+#              #
#    Updated: 2018/04/04 21:31:03 by cquillet         ###   ########.fr        #
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
    srcs/draw.c srcs/event_screen.c

INCLUDES = -I includes -I libft -I lib/SDL2/Headers
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)
MFLAGS = -lpthread -O3
SDL = lib/SDL2/SDL2
SRCO = $(SRC:%.c=%.o)
LIB = lib/libft/libft.a
H = includes/rtv1.h includes/color.h

#Install imagemagick to convert screenshots
MAGICK_NAME =imagemagick
MAGICK = $(shell brew info $(MAGICK_NAME) | grep -o "Not installed")

#Installing SDL2_ttf and SDL2_image and move SDL2 if necessary
SDL_SDL_NAME =SDL2
SDL_SDL = $(shell ls ~/Library/Frameworks | grep "^SDL2$$")

SDL_IMG_NAME =sdl2_image
SDL_IMG = $(shell brew info $(SDL_IMG_NAME) | grep -o "Not installed")
#SDL_IMG = $(shell ls ~/.brew/lib/ | grep libSDL2_image.a)

SDL_TTF_NAME =sdl2_ttf
SDL_TTF = $(shell brew info $(SDL_TTF_NAME) | grep -o "Not installed")
#SDL_TTF = $(shell ls ~/.brew/lib/ | grep libSDL2_ttf.a)

LIBS =

ifeq "$(SDL_SDL)" ""
LIBS += $(SDL_SDL_NAME)
endif

ifeq "$(SDL_TTF)" "Not installed"
LIBS += $(SDL_TTF_NAME)
endif

ifeq "$(SDL_IMG)" "Not installed"
LIBS += $(SDL_IMG_NAME)
endif

ifeq "$(MAGICK)" "Not installed"
LIBS += $(MAGICK_NAME)
endif

.PHONY: all re clean fclean it reit ultra $(SDL_SDL_NAME) $(SDL_IMG_NAME) $(SDL_TTF_NAME) $(MAGICK_NAME)

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

$(SDL_IMG_NAME) $(SDL_TTF_NAME) $(MAGICK_NAME):
	@brew install $@

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

