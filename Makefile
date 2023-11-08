LIBFT_PATH		=	./libft
LIBFT			=	$(LIBFT_PATH)/libft.a -lreadline 

SRCDIR		=	src
SRC			=	minishell.c \

B_SRCDIR	=	src_bonus
BONUS_SRC	=	

NAME		=	minishell
BONUS_NAME	=	minishell_bonus
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror 
OBJ			= 	$(SRC:.c=.o)
B_OBJ		= 	$(BONUS_SRC:.c=.o)



all: depend $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT)

bonus: $(B_OBJ) depend
	$(CC) $(CFLAGS) $(B_OBJ) -o $(BONUS_NAME) $(LIBFT) 

depend:		
	make -C $(LIBFT_PATH) &> /dev/null

clean:
	make -C $(LIBFT_PATH) fclean
	rm -f $(OBJ) 
	rm -f $(B_OBJ)

fclean: clean
	rm -f $(NAME) 
	rm -f $(BONUS_NAME)

re: fclean all
	
norm: 
	norminette $(SRCDIR) $(B_SRCDIR)

.PHONY: clean fclean re all norm bonus