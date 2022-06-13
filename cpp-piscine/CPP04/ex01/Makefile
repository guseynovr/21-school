NAME		=	ex01

SRC			=	$(wildcard *.cpp)

OBJ			=	$(SRC:%.cpp=%.o)

DEP			=	$(OBJ:%.o=%.d)

CXX			=	clang++

CPPFLAGS	=	-Wall -Wextra -Werror -Wshadow -Wno-shadow

CXXFLAGS	=	-std=c++98

RM			=	rm -f

$(NAME):	$(OBJ)
			$(CXX) $^ -o $@

-include	$(DEP)

%.o:		%.cpp
			$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -c $< -o $@

all:		$(NAME)

run:		$(NAME)
			./$(NAME)

clean:
			$(RM) $(OBJ) $(DEP)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

