NAME := miniRT
CC := cc
#when running 'make' add "SHADOWS=HARD" for hard shadows
SHADOWS := HARD
TEST_FLAG :=
SHADOWS_FLAG := -D$(SHADOWS)_SHADOWS
CFLAGS := -Wall -Wextra -DFSAN $(SHADOWS_FLAG) -fsanitize=address -g -O0 $(TEST_FLAG)
#CFLAGS := -Wall -Wextra -g
# FLAGS_SPEED := -Wall -Wextra -Ofast -march=native-flto -DNDBUG=1
FLAGS_SPEED := -Wall -Wextra -g -O3 -march=native -DNDBUG=1 $(TEST_FLAG) $(SHADOWS_FLAG)

#-Werror
#-O3
# -Werror
LIBFT_DIR = libft/
LIBFT 	=	$(LIBFT_DIR)libft.a
INCLUDES= -I./includes -I./MLX42/include/MLX42 -I./MLX42/include -I./libft \
		  -I./includes/ft_math -I./includes/ft_engine -I./includes/parsing \
		  -I./includes/garbage_collector

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

SRC_FILES_ENGINE := \
	ft_engine/init_engine.c \
	ft_engine/world/add_objs_to_world.c \
	ft_engine/world/default_world.c \
	ft_engine/world/print_world.c \
	ft_engine/compute/prepare_computation.c \
	ft_engine/compute/test_prepare_comp.c \
	ft_engine/compute/shading.c \
	ft_engine/canvas/canvas.c \
	ft_engine/mlx_interface/hooks.c \
	ft_engine/rays/init.c \
	ft_engine/rays/cleanup.c \
	ft_engine/rays/intersect.c \
	ft_engine/rays/intersect_utils.c \
	ft_engine/rays/cylinder_intersect.c \
	ft_engine/rays/cone_intersect.c \
	ft_engine/rays/test_cone.c \
	ft_engine/rays/ray_hit.c \
	ft_engine/rays/utils.c \
	ft_engine/rays/tests.c \
	ft_engine/objs/transform.c \
	ft_engine/objs/set_transform.c \
	ft_engine/objs/test.c \
	ft_engine/reflections/reflect.c \
	ft_engine/reflections/tests.c \
	ft_engine/refraction/refraction.c \
	ft_engine/refraction/tests.c \
	ft_engine/refraction/fresnel.c \
	ft_engine/refraction/test_fresnel.c \
	ft_engine/light.c \
	ft_engine/light_tests.c \
	ft_engine/material.c \
	ft_engine/objs/normal_at.c \
	ft_engine/objs/test_normal.c \
	ft_engine/scene/transformation_view.c \
	ft_engine/scene/test_scene.c \
	ft_engine/scene/camera.c \
	ft_engine/scene/test_camera.c \
	ft_engine/shadow/shadow.c \
	ft_engine/shadow/test_shadow.c \
	ft_engine/objs/obj_utils.c \
	ft_engine/objs/test_shape.c \
	ft_engine/compute/test_shade_hit.c \
	ft_engine/test_cylinder.c \
	ft_engine/patterns/patterns.c \
	ft_engine/patterns/stripe_pattern.c \
	ft_engine/patterns/checker_pattern.c \
	ft_engine/patterns/square_pattern.c \
	ft_engine/patterns/test_patterns.c \


SRC_FILES_MATH := \
	ft_math/ft_rand.c \
	ft_math/colors/color_utils.c \
	ft_math/colors/colors.c \
	ft_math/colors/init_colors.c \
	ft_math/tuple/tuple1.c \
	ft_math/tuple/tuple2.c \
	ft_math/tuple/tuple3.c \
	ft_math/tuple/tuple4.c \
	ft_math/tuple/tuple_tests1.c \
	ft_math/tuple/tuple_tests2.c \
	ft_math/tuple/tuple_tests3.c \
	ft_math/general/ft_floats.c \
	ft_math/general/max_min_i.c \
	ft_math/matrix/matrix_rotation.c \
	ft_math/matrix/matrix_translation.c \
	ft_math/matrix/matrix_init.c \
	ft_math/matrix/matrix_mult.c \
	ft_math/matrix/matrix_determinant.c \
	ft_math/matrix/matrix_determinant_tests.c \
	ft_math/matrix/matrix_mult_tests.c \
	ft_math/matrix/matrix_other_tests.c \
	ft_math/matrix/matrix_debug.c \
	ft_math/matrix/matrix_transpose.c \
	ft_math/matrix/test_mtx_transpose.c \
	ft_math/matrix/test_mtx_minor.c \
	ft_math/matrix/matrix_inverse.c \
	ft_math/matrix/test_mtx_inverse.c \
	ft_math/matrix/test_mix.c \
	ft_math/matrix/test_matrix_translation.c \
	ft_math/matrix/matrix_scaling.c \
	ft_math/matrix/test_mtx_scaling.c \
	ft_math/matrix/matrix_shearing.c

SRC_FILES_GB_COLLECT := \
	garbage_collector/gb_garbage_collector.c \
	garbage_collector/test_gc.c \
	garbage_collector/gb_utils.c \
	garbage_collector/gc_dyn_arr.c

SRC_FILES_PARSER := \
	parsing/ppm_parser/store_as_ppm.c \
	parsing/parser_42/parser.c \
	parsing/parser_42/utils.c \
	parsing/parser_42/parse_object.c \
	parsing/parser_42/collision_handlers.c


SOURCE_FILES := \
	$(SRC_MAIN)\
	$(SRC_FILES_ENGINE) \
	$(SRC_FILES_MATH) \
	$(SRC_FILES_GB_COLLECT) \
	$(SRC_FILES_PARSER) \
	init_exit/init.c \
	init_exit/at_exit.c \
	playgrounds/1/projectile.c \
	playgrounds/sphere1/test.c \
	playgrounds/sphere1/test2.c \
	playgrounds/sphere1/test3.c \
	playgrounds/chap_6/1.c \
	playgrounds/chap_9/1.c \
	playgrounds/chap_10/1.c \
	playgrounds/chap_11.c

SOURCES = $(addprefix $(SRC_DIR), $(SOURCE_FILES))

OBJ_DIR = o_files/
OBJECTS=$(SOURCE_FILES:%.c=$(OBJ_DIR)%.o)

NAME_TEST=tests.out

GREEN	=	\033[0;32m
YELLOW	=	\033[33m
CYAN	=	\033[0;36m
CLEAR	=	\033[0m

.PHONY: clone_mlx42 all clean fclean ffclean test

all: $(NAME) test

$(NAME): mlx $(LIBFT) $(OBJECTS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) $(LIBFT) -o $(NAME) $(MLX_FLAGS)
	@echo "$(GREEN)$(NAME) compiled!$(CLEAR)"

test: mlx $(LIBFT)
	rm -f $(OBJ_DIR)ft_engine/compute/shading.o
	make $(NAME_TEST) CFLAGS="$(CFLAGS) -DTEST" SRC_MAIN="$(SRC_TEST_MAIN)" NAME=$(NAME_TEST)

#test_no_assert:
#	@make SRC_MAIN=$(SRC_TEST_MAIN) CFLAGS="-DNO_ASSERT=1 $(CFLAGS)" NAME=tests.out

clean:
	@rm -f $(OBJECTS)
	@rm -f $(SRC_TEST_MAIN:%c=$(OBJ_DIR)%o)
	@rm -f $(SRC_MAIN:%c=$(OBJ_DIR)%o)

#@if [ -d $(OBJ_DIR) ]; then rmdir $(OBJ_DIR); fi
	@if [ -d $(LIBFT_DIR) ]; then cd libft && make clean; fi
	@echo "$(CYAN)object files cleaned$(CLEAR)"

fclean: clean
	@rm -f $(NAME) $(NAME_TEST)
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
fast:
	@make CFLAGS="$(FLAGS_SPEED)"

refast: fclean fast

#to create a performece profile on linux
prof: fclean
	@make CFLAGS="$(FLAGS_SPEED) -g -pg" CC=gcc

###utils
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
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
	@cd libft && make CFLAGS="$(CFLAGS)"

$(LIBFT_DIR):
	@if [ "$(USER)" = "frapp" ] || [ "$(USER)" = "fabi" ] ; then \
		echo "$(GREEN) User $(USER) recognized, cloning via SSH$(CLEAR)"; \
		git clone git@github.com:FabianRapp/libft.git $(LIBFT_DIR);\
	else \
		git clone https://github.com/FabianRapp/libft.git $(LIBFT_DIR);\
	fi

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
