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

INIT_FOLDER := ${addprefix ${SRC_FOLDER}, /init/}
INIT_FILENAMES := init.c
INIT_FILES := ${addprefix ${INIT_FOLDER}, ${INIT_FILENAMES}}

SRC_FILES := ${MAIN_FILES}

OBJS := ${SRC_FILES:.c=.o}


# Rules
all: ${LIBFT} ${MLX} ${NAME}

clean:
	@make -C ${LIBFT_FOLDER} clean
	@if [ -d ${MLX_FOLDER} ]; then \
		echo "Cleaning ${MLX_FOLDER}..."; \
		make -C ${MLX_FOLDER} clean; \
	fi
	rm -f ${OBJS}

fclean: clean
	@make -C ${LIBFT_FOLDER} fclean
	@if [ -d ${MLX_FOLDER} ]; then \
		echo "Removing ${MLX_FOLDER}..."; \
		rm -rf ${MLX_FOLDER}; \
	fi
	rm -f ${NAME}

re: fclean all


# Build libft library
${LIBFT}:
	make -C ${LIBFT_FOLDER} all
	make -C ${LIBFT_FOLDER} bonus


# Build MLX library (Clone if the folder does not exist)
${MLX}:
	@if [ ! -d ${MLX_FOLDER} ] || [ ! -f ${MLX} ]; then \
		echo "MLX not found. Cloning and building..."; \
		rm -rf ${MLX_FOLDER}; \
		git clone ${MLX_URL} ${MLX_FOLDER}; \
		make -C ${MLX_FOLDER}; \
	else \
		echo "MLX already exists. Skipping..."; \
	fi


# Build executable program (cub3D)
${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -L${MLX_FOLDER} ${MLXFLAGS} -o $@


# Object file compilation rule
%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

.PHONY: all clean fclean re
