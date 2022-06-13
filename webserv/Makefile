NAME		=	webserv

BLD_DIR		=	build

SRC_DIR		=	src

PARSER_SRC	=	$(wildcard src/http/parser/*.cpp)
CONFIG_SRC	=	$(wildcard src/config/*.cpp)
CONFP_SRC	=	$(wildcard src/config/parser/*.cpp)
SRC			=	$(wildcard $(SRC_DIR)/*.cpp)
# SRC			=	$(subst $(SRC_DIR)/,,$(wildcard $(SRC_DIR)/*.cpp))

CONFIG_OBJ	=	$(CONFIG_SRC:%.cpp=$(BLD_DIR)/%.o)
CONFP_OBJ	=	$(CONFP_SRC:%.cpp=$(BLD_DIR)/%.o)
PARSER_OBJ  =   $(PARSER_SRC:%.cpp=$(BLD_DIR)/%.o)
OBJ			=	$(SRC:%.cpp=$(BLD_DIR)/%.o)
# OBJ			=	$(SRC:%.cpp=%.o)
# OBJ			=	$(subst $(SRC_DIR), $(BLD_DIR), $(SRC:%.cpp=%.o))

DEP			=	$(OBJ:%.o=%.d)
DEP_PARSER	=	$(PARSER_OBJ:%.o=%.d)
DEP_CONFIG	=	$(CONFIG_OBJ:%.o=%.d)
DEP_CONFP	=	$(CONFP_OBJ:%.o=%.d)

CXX			=	c++

CPPFLAGS	=	-Wall -Wextra -Werror -Wshadow -Wno-shadow -I $(SRC_DIR) -I inc/http -I inc/config

CXXFLAGS	=	-std=c++98

RM			=	rm -f

$(NAME):	$(OBJ) $(PARSER_OBJ) $(CONFIG_OBJ) $(CONFP_OBJ)
			$(CXX) $^ -o $@

-include	$(DEP)
-include	$(DEP_PARSER)
-include	$(DEP_CONFIG)
-include	$(DEP_CONFP)

$(BLD_DIR)/%.o:%.cpp
			mkdir -p $(@D)
			$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -c $< -o $@

all:		$(NAME)

run:		$(NAME)
			./$(NAME)

compile:	$(OBJ) $(PARSER_OBJ) $(CONFIG_OBJ) $(CONFP_OBJ)

clean:
			$(RM) $(OBJ) $(PARSER_OBJ) $(DEP) $(DEP_PARSER) $(DEP_CONFIG) $(DEP_CONFP)
			$(RM) -r $(BLD_DIR)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re compile debug
