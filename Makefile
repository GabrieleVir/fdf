# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gvirga <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/12 23:31:55 by gvirga            #+#    #+#              #
#    Updated: 2019/03/19 02:57:46 by gvirga           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =fdf

LIBFT_DIR =libft/
LIBS =libft.a libmlx.a
LIBSDIR=libs/
LIBSPATH =$(addprefix $(LIBSDIR), $(LIBS))
SRCDIR=srcs/
CC =gcc
CFLAGS =-Wall -Werror -Wextra -g
MAIN =main.c
FILES =errors_read.c read_and_fill.c errors_mlx.c
SRCFILES =$(addprefix $(SRCDIR), $(FILES))
OBJ=$(subst .c,.o, $(FILES)) main.o
SRCOBJ =$(addprefix $(SRCDIR), $(OBJ))
INC_DIR =./includes/
LFLAGS =rc
FRAMEWORKS=appkit opengl
FRAMEWORKS_CMD=$(addprefix -framework , $(FRAMEWORKS))
OBJ2=ft_putchar.o ft_putchar_fd.o ft_putstr.o ft_putstr_fd.o ft_putendl.o \
ft_putendl_fd.o ft_memcpy.o ft_putwchar.o ft_putwstr.o \
\
ft_memccpy.o ft_memset.o ft_bzero.o ft_memmove.o \
ft_memchr.o ft_memcmp.o ft_strlen.o ft_strdup.o \
ft_strcpy.o ft_strncpy.o ft_strtrim.o ft_strsplit.o \
ft_strcat.o ft_strncat.o ft_strlcat.o ft_strstr.o ft_strdup.o ft_strcpy.o \
ft_strncpy.o ft_strchri.o ft_isdigit.o ft_putnbr.o ft_putnbr_fd.o ft_strchr.o \
ft_strrchr.o ft_strnstr.o ft_strcmp.o ft_strncmp.o \
ft_strnew.o ft_strdel.o ft_strclr.o ft_striter.o ft_striteri.o ft_strnjoin.o \
ft_strmap.o ft_strmapi.o ft_strequ.o ft_strnequ.o ft_strsub.o ft_strjoin.o \
\
ft_atoi.o ft_isalpha.o ft_isalnum.o ft_ispowerof2.o\
ft_isascii.o ft_isprint.o ft_toupper.o ft_tolower.o ft_memalloc.o ft_itoa.o \
ft_memdel.o ft_lstnew.o ft_lstdelone.o ft_lstdel.o ft_lstadd.o ft_itoa_base.o \
ft_lstiter.o ft_lstmap.o ft_lstcpy.o ft_wordcount.o ft_atol.o ft_push_back.o \
ft_strnboccur.o ft_strjoin_free.o ft_ipower.o ft_npower.o ft_rchr.o \
ft_nbdigit.o ft_strjoin_freei.o ft_strnew_free.o ft_strsub_free.o \
ft_strdup_free.o ft_putlstr.o ft_memljoin.o ft_llnbdigit.o ft_bigpower.o \
ft_ftoa.o ft_round_str_double.o
SRCOBJ2 =$(addprefix tmp_obj/, $(OBJ2))
SRCFILES2 =$(subst .c, .o, $(SRCOBJ2))

RED=\033[0;31m
YELLOW=\033[0;33m
GREEN=\033[0;32m
END=\033[0m
VOMI=\033[0;35m
VOMIETALEE=\033[44m
CYAN =\033[36m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(YELLOW)Checking updates in the libs$(END)"
	@make -C $(LIBFT_DIR)
	@cp $(LIBFT_DIR)libft.a libs/
	@echo "$(CYAN)Building the fdf executable$(END)"
	gcc $(CFLAGS) -o $@$(OBJ) $(LIBSPATH) $(FRAMEWORKS_CMD)
	@echo "$(GREEN)SUCCESS$(END)"

$(OBJ): $(SRCFILES) $(MAIN)
	@echo "$(CYAN)Compilation of source files for $(NAME) executable...$(END)"
	@$(CC) $(CFLAGS) $(MAIN) -c $(SRCFILES) -I $(INC_DIR)

clean:
	@rm -Rf $(OBJ)
	@echo "$(RED)Suppression$(END) of source files for $(CYAN)$(NAME)$(END)..."

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Suppression$(END) of the lib $(CYAN)$(NAME)$(END)"
	@make --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all
