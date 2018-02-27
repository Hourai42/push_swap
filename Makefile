# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttran <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/17 18:59:37 by ttran             #+#    #+#              #
#    Updated: 2018/02/17 18:59:38 by ttran            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 = checker
NAME2 = push_swap
SRCS_DIR = ./srcs/
INCLUDES = ./includes/
RM = /bin/rm -f
FILES1 = checker
FILES2 = push_swap small_sort large_sort quick_sort updated_sort
COMMON = common
CFILES1 = $(patsubst %, $(SRCS_DIR)%.c, $(FILES1)) 
CFILES2 = $(patsubst %, $(SRCS_DIR)%.c, $(FILES2))
COMMONC = $(patsubst %, $(SRCS_DIR)%.c, $(COMMON))
OFILES1 = $(patsubst %, %.o, $(FILES1))
OFILES2 = $(patsubst %, %.o, $(FILES2))
COMMONO = $(patsubst %, %.o, $(COMMON))
CFLAGS = -Wall -Wextra -Werror

#libft
LFT = ./libft/
LFT_LIB = $(addprefix $(LFT), ft.a)
LFT_INC = -I $(LFT)
LFT_LINK = -L $(LFT) -l ft

#ft_printf 
PRINTF = ./ft_printf/
PRINT_INC = -I $(LFT)$(PRINTF)

all: $(LFT_LIB) $(COMMON) $(NAME1) $(NAME2) 

$(LFT_LIB):
	@make -C $(LFT)

$(OFILES1):
	@gcc $(CFLAGS) -c -I $(INCLUDES) $(LFT_INC) $(PRINT_INC) $(CFILES1)

$(OFILES2):
	@gcc $(CFLAGS) -c -I $(INCLUDES) $(LFT_INC) $(PRINT_INC) $(CFILES2)

$(COMMON):
	@gcc $(CFLAGS) -c -I $(INCLUDES) $(LFT_INC) $(PRINT_INC) $(COMMONC)

$(NAME1): $(OFILES1)
	@gcc $(CFLAGS) $(OFILES1) $(COMMONO) $(LFT_LINK) -o $(NAME1)

$(NAME2): $(OFILES2)
	@gcc $(CFLAGS) $(OFILES2) $(COMMONO) $(LFT_LINK) -o $(NAME2)

clean:
	@make -C $(LFT) clean
	@$(RM) $(OFILES1) $(OFILES2) $(COMMONO)

fclean: clean
	@make -C $(LFT) fclean
	@$(RM) $(NAME1) $(NAME2)

re: fclean all

.PHONY: all clean fclean re
