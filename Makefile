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

OBJ = main.o map_processing.o handlers.o

RM = rm -f

all: $(NAME)

$(NAME):
	@echo "--Compiling libft library--"
	@$(MAKE) $(MAKE_FLAGS) -C $(LIBFT_DIR)
	@$(CC) $(CC_FLAG) -c $(SRC)
	@mkdir -p bin
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
	./bin/wolf3d default

runforever:
	nodemon -e c,h --watch . --exec make run > /tmp/lala
