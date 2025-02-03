CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes

NAME = cubo

OBJ_DIR = ./objs
SRC_PATH = ./srcs

SRCS =	$(SRC_PATH)/main.c \
		$(SRC_PATH)/init.c \
		$(SRC_PATH)/event_handler.c \
		$(SRC_PATH)/data_init.c \
		$(SRC_PATH)/rendering.c \
		$(SRC_PATH)/colli.c \
		$(SRC_PATH)/colli_move1.c \
		$(SRC_PATH)/colli_move2.c \
		$(SRC_PATH)/raycast.c \
		$(SRC_PATH)/movement.c \
		$(SRC_PATH)/parser/gnl.c \
		$(SRC_PATH)/parser/helpers.c \
		$(SRC_PATH)/parser/input_handle.c \
		$(SRC_PATH)/parser/split.c \
		$(SRC_PATH)/parser/singleton.c \
		$(SRC_PATH)/parser/validate.c \

OBJ = $(SRCS:$(SRC_PATH)/%.c=$(OBJ_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm -o $(NAME) -lreadline -lncurses

$(OBJ_DIR)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
