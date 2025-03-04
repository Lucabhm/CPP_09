NAME = btc
CC = c++
CFLAGS = -std=c++17 -Wall -Werror -Wextra -Ofast
SRCS = main.cpp \
		BitcoinExchange.cpp
OBJSDIR = objs/
OBJS = $(addprefix $(OBJSDIR), $(SRCS:.cpp=.o))

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -fsanitize=address

$(OBJSDIR)%.o:	%.cpp
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -c $< -o $@

all:			$(NAME)

clean:
				rm -rf $(OBJSDIR)

fclean:			clean
				rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re