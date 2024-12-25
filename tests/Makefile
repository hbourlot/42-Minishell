CC = cc
LIB = tests.a
OBJ_DIR = obj/
C_FUNCTIONS = test parsing error debug
LINK = -L./library/ -lft
NAME = run
LIBFT = ./library/libft.a

SRC_FILES = $(C_FUNCTIONS:=.c)

OBJ_SRC = $(addprefix $(OBJ_DIR), $(SRC_FILES:%.c=%.o))

all:	$(NAME)

$(NAME):		$(LIBFT) $(LIB)
				$(CC) $(LIB) $(LINK) -o $@

$(LIBFT):
			make -s -C ./library

$(LIB):		$(OBJ_SRC)
			@ar rcs $@ $^

$(OBJ_DIR)%.o: %.c
			@mkdir -p $(dir $@)
			$(CC) -c -I. $< -o $@

clean:
	@make fclean -s -C ./library
	@rm -rf $(OBJ_DIR)
	@rm -rf $(LIB)

r: all
	./$(NAME)

v: clean all
	valgrind --leak-check=full ./$(NAME)
