CC= cc
CFLAGS= -Wall -Wextra -fsanitize=address -g
FLAGS_SPEED = -Wall -Wextra -Ofast -march=native -flto -NDBUG=1
#-Werror
#-O3
# -Werror
NAME=cub3D
LIBFT_DIR = libft/
LIBFT 	=	$(LIBFT_DIR)libft.a
INCLUDES=-I./includes -I./MLX42/include/MLX42 -I./MLX42/include -I./libft
MLX=MLX42/build/libmlx42.a
#MLX_FLAGS_LINUX=-Iinclude -ldl -lglfw -pthread -lm
MLX_FLAGS_MAC= -framework Cocoa $(MLX) -framework OpenGL -framework IOKit -Iinclude -lglfw
#-L"/Users/$(USER)/.brew/opt/glfw/lib/"
MLX_FLAGS_LINUX =-I MLX42/include/MLX42 $(MLX) -Iinclude -ldl -lglfw -pthread -lm
OS := $(shell uname)

ifeq ($(OS), Darwin)
	MLX_FLAGS = $(MLX_FLAGS_MAC)
else
	MLX_FLAGS = $(MLX_FLAGS_LINUX)
endif


SRC_DIR = srcs/
SOURCE_FILES= \
	main.c 
SOURCES = $(addprefix $(SRC_DIR), $(SOURCE_FILES))

OBJ_DIR = o_files/
TMP=$(notdir $(SOURCES))
OBJECTS=$(TMP:%.c=$(OBJ_DIR)%.o)

GREEN	=	\033[0;32m
YELLOW	=	\033[33m
CYAN	=	\033[0;36m
CLEAR	=	\033[0m

.PHONY: clone_mlx42 all clean fclean ffclean

all: mlx $(LIBFT) $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) $(LIBFT) -o $(NAME) $(MLX_FLAGS)
	@echo "$(GREEN)$(NAME) compiled!$(CLEAR)"

clean:
	@rm -f $(OBJECTS)
	@if [ -d $(OBJ_DIR) ]; then rmdir $(OBJ_DIR); fi
	@cd libft && make clean
	@echo "$(CYAN)object files cleaned$(CLEAR)"

fclean: clean
	@rm -f $(NAME)
	@cd libft && make fclean
	@echo "$(CYAN)cub3D fclean$(CLEAR)"

ffclean: fclean
	@rm -rf MLX42
	@echo "$(CYAN)cub3D ffclean$(CLEAR)"

re: fclean
	@make all

rre: ffclean
	@make all

#to optimize for speed without debugging info
fast: fclean
	@make CFLAGS=$(FLAGS_SPEED)

#to create a performece profile on linux
prof: fclean
	@make CFLAGS="-march=native -Ofast -mavx2 -DNDEBUG=1 -g -pg" CC=gcc

###utils

$(OBJ_DIR)%.o: $(SRC_DIR)%.c  $(OBJ_DIR) mlx
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

mlx: clone_mlx
	@if [ ! -e $(MLX) ]; then \
		cd MLX42 && cmake -DDEBUG=1 -B build && cmake --build build -j4; \
		echo "$(GREEN) lib_MLX compiled!$(CLEAR)"; \
	fi

clone_mlx:
	@if [ ! -d "MLX42" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git; \
	fi

$(LIBFT): $(LIBFT_DIR)
	@cd libft && make CFLAGS=$(CLFAGS)

$(LIBFT_DIR):
	git clone https://github.com/FabianRapp/libft.git $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
