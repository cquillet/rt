# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/25 19:54:18 by cquillet          #+#    #+#              #
#    Updated: 2018/04/25 20:39:20 by cquillet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		libft.a

SRC = 	ft_isalpha.c		ft_isprint.c		ft_memcmp.c			\
		ft_atoi.c			ft_strlcat.c		ft_strncmp.c		\
		ft_toupper.c		ft_bzero.c			ft_isascii.c		\
		ft_memcpy.c			ft_strcat.c			ft_strcpy.c			\
		ft_strncpy.c		ft_strstr.c			ft_isalnum.c		\
		ft_memchr.c			ft_memmove.c		ft_strchr.c			\
		ft_strncat.c		ft_strnstr.c		ft_tolower.c		\
		ft_itoa.c			ft_strdel.c			ft_putendl.c		\
		ft_strjoin.c		ft_strnew.c			ft_memalloc.c		\
		ft_putstr.c			ft_strequ.c			ft_strmap.c			\
		ft_memdel.c			ft_striter.c		ft_memccpy.c		\
		ft_strmapi.c		ft_strsub.c			ft_putchar.c		\
		ft_strclr.c			ft_striteri.c		ft_strnequ.c		\
		ft_memset.c			ft_strrchr.c		ft_strlen.c			\
		ft_isdigit.c		ft_strdup.c			ft_putendl_fd.c		\
		ft_strsplit.c		ft_putnbr.c			ft_putchar_fd.c		\
		ft_putnbr_fd.c		ft_putstr_fd.c		ft_lstnew.c			\
		ft_strcmp.c			ft_strtrim.c		ft_lstdelone.c		\
		ft_lstadd.c			ft_lstdel.c			ft_lstiter.c		\
		ft_lstmap.c			ft_range.c			ft_putstrcolor.c	\
		ft_sqrt.c			ft_resetcolor.c		ft_putnbrcolor.c	\
		ft_putnbrendl.c		ft_cp_tab.c			ft_file_to_str.c	\
		ft_print_tab.c		swap_tab.c			ft_changecolor.c	\
		ft_putendlcolor.c	ft_strjoin_free.c	ft_putcharendl.c	\
		get_next_line.c		ft_revstr.c			ft_isupper.c		\
		no_case.c			repeat.c			tab_len.c			\
		swap_tab.c 			free_tab.c			tab_new.c			\
		sort_ascii.c		search_tab.c 		ft_atof.c

CC =		gcc
CFLAGS =	-Wall -Wextra -Werror

SRCDIR =	.
INCDIR =	.
OBJDIR =	objs

INCFILE =	$(INCDIR)/libft.h

OBJ =		$(SRC:%.c=$(OBJDIR)/%.o)

all: obj
	@$(MAKE) $(NAME)

obj:
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCFILE)
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ -c $<

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -rf $(OBJDIR)

fclean:
	rm -f $(NAME)
	rm -rf $(OBJDIR)

re: fclean all

