NAME := miniRT
CC := cc
#when running 'make' add "SHADOWS=HARD" for hard shadows
SHADOWS := HARD
#when running 'make' add "AMBIENT=CUSTOM" for diffrent ambient light
AMBIENT := 42
CAMERA := 42
CAMERA_FLAG :="-DCAMERA_$(CAMERA)"
AMBIENT_FLAG := -DAMBIENT_$(AMBIENT)
REFLECTIONS = 3
REFLECTION_FLAG = "-DREFLECTION_COUNT=$(REFLECTIONS)"
SHADOWS_FLAG := -D$(SHADOWS)_SHADOWS
CFLAGS_DEBUG := -Wall -Wextra -Werror -DFSAN $(SHADOWS_FLAG) -fsanitize=address -g -O0 $(AMBIENT_FLAG) $(REFLECTION_FLAG) $(CAMERA_FLAG)
FLAGS_SPEED := -Wall -Wextra -Werror -g -Ofast -march=native -DNDBUG=1 $(SHADOWS_FLAG) $(AMBIENT_FLAG) $(REFLECTION_FLAG) $(CAMERA_FLAG)
CFLAGS := $(FLAGS_SPEED)
#-Werror
#-O3
# -Werror
LIBFT_DIR = libft/
LIBFT 	=	$(LIBFT_DIR)libft.a
INCLUDES= -I./includes -I./MLX42/include/MLX42 -I./MLX42/include -I./libft \
		  -I./includes/ft_math -I./includes/ft_engine -I./includes/parsing \
		  -I./includes/garbage_collector \
		  -I./includes/demo

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

SRC_FILES_ENGINE := \
	ft_engine/init_engine.c \
	ft_engine/world/add_objs_to_world.c \
	ft_engine/world/default_world.c \
	ft_engine/world/print_world.c \
	ft_engine/compute/prepare_computation.c \
	ft_engine/compute/shading.c \
	ft_engine/compute/shade_hit.c \
	ft_engine/compute/render.c \
	ft_engine/light/light.c \
	ft_engine/light/spot_light.c \
	ft_engine/canvas/canvas.c \
	ft_engine/mlx_interface/hooks.c \
	ft_engine/rays/init.c \
	ft_engine/rays/init2.c \
	ft_engine/rays/cleanup.c \
	ft_engine/rays/intersect.c \
	ft_engine/rays/intersect_utils.c \
	ft_engine/rays/cylinder_intersect.c \
	ft_engine/rays/cone_intersect.c \
	ft_engine/rays/cone_intersect_utils.c \
	ft_engine/rays/cone_caps.c \
	ft_engine/rays/ray_hit.c \
	ft_engine/rays/utils.c \
	ft_engine/objs/transform.c \
	ft_engine/objs/set_transform.c \
	ft_engine/reflections/reflect.c \
	ft_engine/refraction/refraction.c \
	ft_engine/refraction/fresnel.c \
	ft_engine/material.c \
	ft_engine/objs/normal_at.c \
	ft_engine/objs/normal_at_types.c \
	ft_engine/scene/transformation_view.c \
	ft_engine/scene/camera.c \
	ft_engine/shadow/shadow.c \
	ft_engine/objs/obj_utils.c \
	ft_engine/patterns/patterns.c \
	ft_engine/patterns/stripe_pattern.c \
	ft_engine/patterns/checker_pattern.c \
	ft_engine/patterns/square_pattern.c \
	ft_engine/bump_map/bump_wave.c \
	ft_engine/bump_map/bump.c \

SRC_FILES_MATH := \
	ft_math/ft_rand.c \
	ft_math/colors/color_utils.c \
	ft_math/colors/colors.c \
	ft_math/colors/init_colors.c \
	ft_math/tuple/tuple1.c \
	ft_math/tuple/tuple2.c \
	ft_math/tuple/tuple2_debug.c \
	ft_math/tuple/tuple3.c \
	ft_math/tuple/tuple3_debug.c \
	ft_math/tuple/tuple4.c \
	ft_math/general/ft_floats.c \
	ft_math/general/max_min_i.c \
	ft_math/matrix/matrix_rotation.c \
	ft_math/matrix/matrix_translation.c \
	ft_math/matrix/matrix_init.c \
	ft_math/matrix/matrix_mult.c \
	ft_math/matrix/matrix_determinant.c \
	ft_math/matrix/matrix_debug.c \
	ft_math/matrix/matrix_transpose.c \
	ft_math/matrix/matrix_inverse.c \
	ft_math/matrix/matrix_scaling.c \
	ft_math/matrix/matrix_shearing.c

SRC_FILES_GB_COLLECT := \
	garbage_collector/gb_garbage_collector.c \
	garbage_collector/test_gc.c \
	garbage_collector/gb_utils.c \
	garbage_collector/gc_dyn_arr.c

SRC_FILES_MATERIALS := \
	materials/landscape.c \
	materials/metal.c

SRC_FILES_DEMO := \
	demo_scenes/ocean.c \
	demo_scenes/ocean_balls.c \
	demo_scenes/inner_sphere.c \
	demo_scenes/reflection_demo.c \
	demo_scenes/one_piece.c \
	demo_scenes/internal_reflection.c

SRC_FILES_PARSER := \
	parsing/ppm_parser/store_as_ppm.c \
	parsing/parser_42/parser.c \
	parsing/parser_42/utils.c \
	parsing/parser_42/utils2.c \
	parsing/parser_42/parse_object.c \
	parsing/parser_42/parse_objects2.c \
	parsing/parser_42/parse_objects3.c \
	parsing/parser_42/collision_handlers.c

#BETTER_PARSER := \
#	 better_parser/p_main.c \


SOURCE_FILES := \
	$(SRC_MAIN)\
	$(SRC_FILES_ENGINE) \
	$(SRC_FILES_MATH) \
	$(SRC_FILES_GB_COLLECT) \
	$(SRC_FILES_PARSER) \
	$(SRC_FILES_MATERIALS) \
	$(SRC_FILES_DEMO) \
	init_exit/init.c \
	init_exit/at_exit.c \

SOURCES = $(addprefix $(SRC_DIR), $(SOURCE_FILES))

OBJ_DIR = o_files/
OBJECTS=$(SOURCE_FILES:%.c=$(OBJ_DIR)%.o)

GREEN	=	\033[0;32m
YELLOW	=	\033[33m
CYAN	=	\033[0;36m
CLEAR	=	\033[0m

.PHONY: clone_mlx42 all clean fclean ffclean redebug print_vars

all: $(NAME)

$(NAME): print_vars mlx $(LIBFT) $(OBJECTS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) $(LIBFT) -o $(NAME) $(MLX_FLAGS) $(CFLAGS)
	@echo "$(GREEN)$(NAME) compiled!$(CLEAR)"

print_vars:
	@echo "$(YELLOW)REFLECTIONS: $(CLEAR)$(GREEN)$(REFLECTIONS) $(CLEAR)$(YELLOW)(any integer >= 0) $(CLEAR)"
	@echo "$(YELLOW)SHADOWS: $(CLEAR)$(GREEN)'$(SHADOWS)' $(CLEAR)$(YELLOW)('SMOOTH\' or 'HARD') $(CLEAR)"
	@echo "$(YELLOW)AMBIENT: $(CLEAR)$(GREEN)'$(AMBIENT)' $(CLEAR)$(YELLOW)('42' or 'CUSTOM') $(CLEAR)"
	@echo "$(YELLOW)CAMERA: $(CLEAR)$(GREEN)'$(CAMERA)' $(CLEAR)$(YELLOW)('42' or 'GOOD') $(CLEAR)"

debug:
	make CFLAGS="$(CFLAGS_DEBUG)"

redebug: fclean debug


clean:
	@rm -f $(OBJECTS)
	@rm -f $(SRC_MAIN:%c=$(OBJ_DIR)%o)

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
		git clone https://github.com/codam-coding-college/MLX42.git --no-checkout; \
		cd MLX42; \
		git checkout 5d14c832a05a88dd219dd6dc05a5bbf1b577ae0c; \
		cd .. ;\
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
