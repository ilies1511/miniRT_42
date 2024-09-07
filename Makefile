NAME := miniRT
CC := cc
CFLAGS := -Wall -Wextra -fsanitize=address -g
FLAGS_SPEED := -Wall -Wextra -Ofast -march=native -flto -NDBUG=1
#-Werror
#-O3
# -Werror
LIBFT_DIR = libft/
LIBFT 	=	$(LIBFT_DIR)libft.a
INCLUDES= -I./includes -I./MLX42/include/MLX42 -I./MLX42/include -I./libft -I./includes/ft_math
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
SRC_MAIN = main.c
SRC_TEST_MAIN := main_tests.c
SOURCE_FILES := $(SRC_MAIN)\
	engine/utils/reset.c \
	init_exit/init.c \
	init_exit/at_exit.c \
	mlx_interface/hooks.c \
	ft_math/general/ft_floats.c \
	ft_math/tuple/tuple1.c \
	ft_math/tuple/tuple2.c \
	ft_math/tuple/tuple3.c \
	ft_math/tuple/tuple4.c \
	ft_math/tuple/tuple_tests1.c \
	ft_math/tuple/tuple_tests2.c \
	ft_math/tuple/tuple_tests3.c \


SOURCES = $(addprefix $(SRC_DIR), $(SOURCE_FILES))

OBJ_DIR = o_files/
OBJECTS=$(SOURCE_FILES:%.c=$(OBJ_DIR)%.o)

GREEN	=	\033[0;32m
YELLOW	=	\033[33m
CYAN	=	\033[0;36m
CLEAR	=	\033[0m

.PHONY: clone_mlx42 all clean fclean ffclean

all: mlx $(LIBFT) $(OBJECTS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) $(LIBFT) -o $(NAME) $(MLX_FLAGS)
	@echo "$(GREEN)$(NAME) compiled!$(CLEAR)"

test:
	make SRC_MAIN="$(SRC_TEST_MAIN)" NAME=tests.out

test_no_assert:
	@make SRC_MAIN=$(SRC_TEST_MAIN) CFLAGS="-DNO_ASSERT=1 $(CFLAGS)" NAME=tests.out

clean:
	@rm -f $(OBJECTS)
#@if [ -d $(OBJ_DIR) ]; then rmdir $(OBJ_DIR); fi
	@if [ -d $(LIBFT_DIR) ]; then cd libft && make clean; fi
	@echo "$(CYAN)object files cleaned$(CLEAR)"

fclean: clean
	@rm -f $(NAME)
	@if [ -d $(LIBFT_DIR) ]; then cd libft && make fclean; fi
	@echo "$(CYAN)miniRT fclean$(CLEAR)"

ffclean: fclean
	@rm -rf MLX42
	@rm -rf $(LIBFT_DIR)
	@echo "$(CYAN)miniRT ffclean$(CLEAR)"

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
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(OBJ_DIR)
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
	@if [ "$(USER)" = "frapp" ] || [ "$(USER)" = "fabi" ] ; then \
		echo "$(GREEN) User $(USER) recognized, cloning via SSH$(CLEAR)"; \
		git clone git@github.com:FabianRapp/libft.git $(LIBFT_DIR);\
	else \
		git clone https://github.com/FabianRapp/libft.git $(LIBFT_DIR);\
	fi

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
