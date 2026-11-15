NAME = codexion

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -I$(HEAD_DIR)

SRCS_DIR = src
HEAD_DIR = header
OBJS_DIR = objs

HEADERS = $(HEAD_DIR)/codexion.h

MAIN = codexion.c

SRCS = parse_params.c \
	parsing_utils.c \
	init_dongles.c \
	init_coders.c \
	init_simulation.c \
	cleanup_simulation.c \
	threads.c \
	simulation_state.c \
	logging.c \
	monitoring_thread.c \
	


OBJ = $(OBJS_DIR)/$(MAIN:.c=.o) \
	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS) | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/$(MAIN:.c=.o): $(MAIN) $(HEADERS) | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re