# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chajjar <chajjar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 09:49:21 by chajjar           #+#    #+#              #
#    Updated: 2023/03/14 09:53:37 by chajjar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = irc_clicli

SRC = IrcClient.c
OBJ = $(SRC:.cpp=.o)
CC = gcc

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) -o $(NAME) $(OBJ)

clean:
		rm -f $(NAME)
fclean: clean 
		rm -f $(OBJ)
re: clean all
.PHONY: all clean fclean re 