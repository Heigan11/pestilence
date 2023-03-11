# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chilton <chilton@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/31 19:28:24 by chilton           #+#    #+#              #
#    Updated: 2021/04/23 16:46:27 by chilton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
SRC		= ft_char/ft_isalnum.c			ft_char/ft_isalpha.c \
		  ft_char/ft_isascii.c			ft_char/ft_isdigit.c \
		  ft_char/ft_isprint.c			ft_char/ft_tolower.c \
		  ft_char/ft_toupper.c \
		  ft_mem/ft_memset.c			ft_mem/ft_bzero.c \
		  ft_mem/ft_memcpy.c			ft_mem/ft_memccpy.c \
	 	  ft_mem/ft_memmove.c			ft_mem/ft_memchr.c \
	 	  ft_mem/ft_memcmp.c			ft_mem/ft_calloc.c \
		  ft_put/ft_putchar_fd.c		ft_put/ft_putstr_fd.c \
		  ft_put/ft_putendl_fd.c		ft_put/ft_putnbr_fd.c \
		  ft_str/ft_atoi.c				ft_str/ft_strlcat.c \
		  ft_str/ft_strlcpy.c			ft_str/ft_strlen.c \
		  ft_str/ft_strchr.c			ft_str/ft_strrchr.c \
		  ft_str/ft_strncmp.c			ft_str/ft_strnstr.c \
		  ft_str/ft_strdup.c			ft_str/ft_substr.c \
		  ft_str/ft_strjoin.c			ft_str/ft_strtrim.c \
		  ft_str/ft_itoa.c				ft_str/ft_split.c \
		  ft_str/ft_strmapi.c
BSRC	= ft_lst/ft_lstnew.c 			ft_lst/ft_lstadd_front.c \
		  ft_lst/ft_lstsize.c 			ft_lst/ft_lstlast.c \
		  ft_lst/ft_lstadd_back.c		ft_lst/ft_lstdelone.c \
		  ft_lst/ft_lstclear.c			ft_lst/ft_lstiter.c \
		  ft_lst/ft_lstmap.c			ft_lst/ft_lstremoveif_bonus.c \
		  ft_lst/ft_lstgetitem_bonus.c \
		  gnl/get_next_line_bonus.c		gnl/get_next_line_utils_bonus.c \
		  ft_str/ft_splitlen_bonus.c	ft_str/ft_splitfree_bonus.c \
		  ft_put/ft_putchar_bonus.c		ft_str/ft_strcmp_bonus.c \
		  ft_dllst/ft_dllst_bonus.c
OBJ		= $(SRC:.c=.o)
BOBJ	= $(BSRC:.c=.o)
DEPS	= $(SRC:.c=.d)
BDEPS	= $(BSRC:.c=.d)
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -I. -MMD
ifeq ($(MAKECMDGOALS), bonus)
OBJ := $(OBJ) $(BOBJ)
DEPS := $(DEPS) $(BDEPS)
endif

all:	$(NAME)

$(NAME):$(OBJ)
		ar -rcs $@ $?

-include $(DEPS)

bonus:	$(NAME)

clean:
		$(RM) $(OBJ) $(BOBJ) $(DEPS) $(BDEPS)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re bonus
