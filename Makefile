# Compiler and flags
CC := cc
CFLAGS := -Wall -Werror -Wextra -g
MLXFLAGS := -lmlx -lX11 -lXext


# Libft folder and files
LIBFT_FOLDER := libft
LIBFT := ${LIBFT_FOLDER}/libft.a


# MLX folder and files
MLX_FOLDER := minilibx-linux
MLX_URL := https://github.com/42Paris/minilibx-linux.git
MLX := ${MLX_FOLDER}/libmlx_Linux.a


# Main Program folder and files
NAME := cub3D
SRC_FOLDER := src

MAIN_FOLDER := ${addprefix ${SRC_FOLDER}, /main/}
MAIN_FILENAMES := main.c
MAIN_FILES := ${addprefix ${MAIN_FOLDER}, ${MAIN_FILENAMES}}

GRAPHICS_FOLDER := ${addprefix ${SRC_FOLDER}, /graphics/}
GRAPHICS_FILENAMES := game.c controls.c player.c images.c floor_render.c wall_render.c wall_texture.c
GRAPHICS_FILES := ${addprefix ${GRAPHICS_FOLDER}, ${GRAPHICS_FILENAMES}}

INIT_FOLDER := ${addprefix ${SRC_FOLDER}, /init/}
INIT_FILENAMES := init.c
INIT_FILES := ${addprefix ${INIT_FOLDER}, ${INIT_FILENAMES}}

MAP_FOLDER := ${addprefix ${SRC_FOLDER}, /map/}
MAP_FILENAMES := map_utils.c parse_map.c parse_map_2.c file_struct.c storing.c flood_fill.c file_struct_2.c
MAP_FILES := ${addprefix ${MAP_FOLDER}, ${MAP_FILENAMES}}

UTILS_FOLDER := ${addprefix ${SRC_FOLDER}, /utils/}
UTILS_FILENAMES := strcjoin.c cleanup.c pixel_put.c draw_to_img.c get_time.c exit_game.c
UTILS_FILES := ${addprefix ${UTILS_FOLDER}, ${UTILS_FILENAMES}}

SRC_FILES := ${MAIN_FILES} ${GRAPHICS_FILES} ${INIT_FILES} ${MAP_FILES} ${UTILS_FILES}

OBJS := ${SRC_FILES:.c=.o}

# Bonus Program folder and files
BONUS_NAME := cub3D_bonus
B_SRC_FOLDER := bonus

B_GRAPHICS_FOLDER := ${addprefix ${B_SRC_FOLDER}, /graphics/}
B_GRAPHICS_FILENAMES := game_bonus.c controls_bonus.c player_bonus.c images_bonus.c floor_render_bonus.c wall_render_bonus.c wall_texture_bonus.c minimap_bonus.c mouse_bonus.c door_bonus.c door_2_bonus.c sprite_bonus.c sprite_bonus_2.c
B_GRAPHICS_FILES := ${addprefix ${B_GRAPHICS_FOLDER}, ${B_GRAPHICS_FILENAMES}}

B_MAP_FOLDER := ${addprefix ${B_SRC_FOLDER}, /map/}
B_MAP_FILENAMES := map_utils_bonus.c parse_map_bonus.c parse_map_2_bonus.c file_struct_bonus.c storing_bonus.c flood_fill_bonus.c file_struct_2_bonus.c
B_MAP_FILES := ${addprefix ${B_MAP_FOLDER}, ${B_MAP_FILENAMES}}

BONUS_SRC := ${MAIN_FILES} ${B_GRAPHICS_FILES} ${INIT_FILES} ${B_MAP_FILES} ${UTILS_FILES}

BONUS_OBJS := ${BONUS_SRC:.c=.o}

# Rules
all: ${LIBFT} ${MLX} ${NAME}

bonus: ${LIBFT} ${MLX} ${BONUS_NAME}

clean:
	@echo "Cleaning object files.."
	@make -s -C ${LIBFT_FOLDER} clean > /dev/null 2>&1
	@
	@if [ -d ${MLX_FOLDER} ]; then \
		echo "Cleaning ${MLX_FOLDER}..."; \
		make -s -C ${MLX_FOLDER} clean > /dev/null 2>&1; \
	fi
	@rm -f ${OBJS} ${BONUS_OBJS}


fclean: clean
	@echo "Removing executable and MLX.."
	@make -s -C ${LIBFT_FOLDER} fclean
	@
	@if [ -d ${MLX_FOLDER} ]; then \
		echo "Removing ${MLX_FOLDER}..."; \
		rm -rf ${MLX_FOLDER}; \
	fi
	@rm -f ${NAME} ${BONUS_NAME}

re: fclean all


# Build libft library
${LIBFT}:
	@echo "Building libft.."
	@make -s -C ${LIBFT_FOLDER} all
	@make -s -C ${LIBFT_FOLDER} bonus


# Build MLX library (Clone if the folder does not exist)
${MLX}:
	@if [ ! -d ${MLX_FOLDER} ] || [ ! -f ${MLX} ]; then \
		echo "MLX not found. Cloning and building..."; \
		rm -rf ${MLX_FOLDER}; \
		git clone ${MLX_URL} ${MLX_FOLDER} > /dev/null 2>&1; \
		make -s -C ${MLX_FOLDER} > /dev/null 2>&1; \
	else \
		echo "MLX already exists. Skipping..."; \
	fi


# Build executable program (cub3D)
${NAME}: ${OBJS}
	@echo "Linking ${NAME}.."
	@${CC} ${CFLAGS} ${OBJS} ${LIBFT} -L${MLX_FOLDER} ${MLXFLAGS} -o $@ -lm

# Build executable program (bonus)
${BONUS_NAME}: ${BONUS_OBJS}
	@echo "Linking ${BONUS_NAME}.."
	@${CC} ${CFLAGS} ${BONUS_OBJS} ${LIBFT} -L${MLX_FOLDER} ${MLXFLAGS} -o $@ -lm


# Object file compilation rule
%.o: %.c
	@echo "Compiling $<.."
	@${CC} ${CFLAGS} -c $< -o $@

.PHONY: all bonus clean fclean re
