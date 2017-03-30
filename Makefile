NAME = wolf3d

MAKE = make 
MAKE_FLAGS = --no-print-directory

SRC_DIR = ./srcs

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SDL_FLAGS = `sdl-config --cflags --libs`

CC = gcc
CC_FLAGS = -Wall -Werror -Wextra

SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/map_processing.c \
		$(SRC_DIR)/handlers.c \
		$(SRC_DIR)/map_editor.c \
		$(SRC_DIR)/display_functions.c \
		$(SRC_DIR)/render.c \
		$(SRC_DIR)/ray_cast.c \
		$(SRC_DIR)/get_intersection_point.c \
		$(SRC_DIR)/check_if_collision.c \
		$(SRC_DIR)/player_movement.c \
		$(SRC_DIR)/player_collision_backward.c \
		$(SRC_DIR)/player_collision_forward.c \
		$(SRC_DIR)/free_memory.c \

OBJ = main.o map_processing.o handlers.o map_editor.o display_functions.o render.o ray_cast.o get_intersection_point.o check_if_collision.o player_movement.o player_collision_backward.o player_collision_forward.o free_memory.o

RM = rm -f

all: $(NAME)

$(NAME):
	@echo "--Compiling libft library--"
	@$(MAKE) $(MAKE_FLAGS) -C $(LIBFT_DIR)
	@echo "--Compiling sources--------"
	@$(CC) $(CC_FLAG) -c $(SRC)
	@mkdir -p bin
	@echo "--Creating executable------"
	@$(CC) -o bin/$(NAME) $(OBJ) $(LIBFT)  -rpath ./Frameworks -F./Frameworks -framework SDL2
	@echo "--Done---------------------"

clean:
	@echo "--Cleaning libraries-------"
	@$(MAKE) $(MAKE_FLAGS) fclean -C $(LIBFT_DIR)
	@echo "--Cleaning output files----"
	@$(RM) $(OBJ)

fclean: clean
	@echo "--Cleaning executable------"
	@$(RM) $(NAME)

re: fclean all

run: $(NAME)
	./bin/wolf3d

runforever:
	nodemon -e c,h --watch . --exec make run > /tmp/lala
