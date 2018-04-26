# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/25 19:54:36 by cquillet          #+#    #+#              #
#    Updated: 2018/04/26 20:20:24 by cquillet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		RTv1

SRC = action.c \
calc_obj.c \
cam.c \
cast_ray.c \
clean.c \
color.c \
color_calc.c \
color_utils.c \
draw.c \
error.c \
event.c \
event_move.c \
event_obj.c \
event_screen.c \
help.c \
init.c \
init_data.c \
init_obj.c \
init_sheit.c \
intersections.c \
lux.c \
lux_calc.c \
maintest2.c \
matrice.c \
obj.c \
parse_utils.c \
parsing.c \
scene.c \
utils.c \
vect_calc1.c \
vect_calc2.c \
vect_utils.c

CC =		gcc
CFLAGS =	-Wall -Wextra -Werror

SRCDIR	= srcs
INCDIR	= includes
OBJDIR	= objs
SDLDIR	= ~/Library/Frameworks

INCFILE = $(addprefix $(INCDIR)/,$(NAME).h)

OBJ		= $(SRC:%.c=$(OBJDIR)/%.o)

FT		= lib/libft
FT_LNK	= -L$(FT) -lft
FT_INC	= -I$(INCDIR) -I$(FT)

ifeq "$(shell brew info sdl2 | grep -o 'Not installed')" "Not installed"
INSTALL	= install
else
INSTALL	=
endif

.PHONY: all re clean fclean it reit ultra obj install
 
all: obj $(INSTALL)
	@make -C $(FT)
	@$(MAKE) $(NAME)

install:
	@brew install sdl2

obj:
	@mkdir -p $(OBJDIR)
	@rm -rf $(SDLDIR)/SDL2
	@mkdir -p $(SDLDIR)/SDL2
	@cp -R lib/sdl2 ~/Library/Frameworks

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(FT_INC) -o $@ -c $< $(shell sdl2-config --cflags)

$(NAME): $(OBJ) lib/libft/libft.a
	$(CC) $(OBJ) $(FT_LNK) $(shell sdl2-config --libs) -lm -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	@make -C $(FT) clean

fclean:
	rm -rf $(OBJDIR)
	rm -f $(NAME)
	@make -C $(FT) fclean

re: fclean all
