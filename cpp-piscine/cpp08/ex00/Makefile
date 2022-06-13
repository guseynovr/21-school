NAME		=	ex00

BLD_DIR		=	./build

SRC			=	$(wildcard *.cpp)

OBJ			=	$(SRC:%.cpp=$(BLD_DIR)/%.o)

DEP			=	$(OBJ:%.o=%.d)

CXX			=	clang++

CPPFLAGS	=	-Wall -Wextra -Werror -Wshadow -Wno-shadow -I .

CXXFLAGS	=	-std=c++98

RM			=	rm -f

$(NAME):	$(OBJ)
			$(CXX) $^ -o $@

-include	$(DEP)

$(BLD_DIR)/%.o:%.cpp
			mkdir -p $(@D)
			$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -c $< -o $@

all:		$(NAME)

run:		$(NAME)
			./$(NAME)

clean:
			$(RM) $(OBJ) $(DEP)
			$(RM) -r $(BLD_DIR)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

