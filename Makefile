NAME = TicTacToe-Ai
SRC = src/Game.cpp src/MCTS.cpp src/Node.cpp main.cpp
OBJ = ${SRC:.cpp=.o}
CC = c++
CPPFLAGS = -Wall -Wextra -Werror

all : $(NAME)

%.o : %.cpp Inc/Game.hpp Inc/MCTS.hpp Inc/Node.hpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(CPPFLAGS) -o $@ $^

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : clean all

.PHONY : all re clean fclean