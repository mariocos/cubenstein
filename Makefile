CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes

NAME = cubo

SRCS =	main.c \
		init.c \
		event_handler.c \
		data_init.c \
		rendering.c \
		
		

OBJS = ${SRCS:.c=.o}

RM = rm -f

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm -o ${NAME}

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re