NAME = PmergeMe
CC = c++
CFLAGS = -Wall -Werror -Wextra -std=c++17
SRCS = main.cpp
OBJSDIR = objs/
OBJS = $(addprefix $(OBJSDIR), $(SRCS:.cpp=.o))

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -fsanitize=address

$(OBJSDIR)%.o:	%.cpp
				@mkdir -p $(dir $@)
				$(CC) -c $< -o $@

all:			$(NAME)

clean:
				rm -rf $(OBJSDIR)

fclean:			clean
				rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re