NAME		=	PmergeMe

CC			=	c++

FLAGS		=	-Wall -Werror -Wextra -std=c++98

SRCS		=	main.cpp			\
				PmergeMe.cpp		\
				myStoi.cpp

INCL		=	PmergeMe.hpp

OBJS		=	$(SRCS:%.cpp=$(OBJ_DIR)%.o)

OBJ_DIR		=	objs/

RM			=	rm -rf

all:		$(NAME)

$(OBJ_DIR)%.o: %.cpp $(INCL) | $(OBJ_DIR)
		$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
			mkdir -p $@

$(NAME):	$(OBJS) $(INCL)
			$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean:		
			$(RM) $(OBJ_DIR)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re