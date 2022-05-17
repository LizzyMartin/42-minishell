.PHONY: all clean fclean re

CC =            clang
CFLAGS = 		-Wall -Wextra -Werror -ggdb3
RLFLAG =		-lreadline
AR =            ar -rcs
RM =            rm -rfd

LIBFT_DIR = 	libs/libft/app
LIBFT.A =       $(LIBFT_DIR)/libft.a

# Mandatory

SRCS_DIR =   	srcs
OBJS_DIR =   	$(SRCS_DIR)/.objs
HEADER_DIR =   ./srcs/includes
HEADER =		$(HEADER_DIR)/minishell.h
NAME =			minishell

SRCS_FILES +=	builtins/ms_cd.c \
				builtins/ms_echo.c \
				builtins/ms_env.c \
				builtins/ms_exit.c \
				builtins/ms_export.c \
				builtins/ms_pwd.c \
				builtins/ms_unset.c

SRCS_FILES +=	execute/ms_execute.c

SRCS_FILES +=	init/ms_init.c

SRCS_FILES +=	parse/ms_parse.c

SRCS_FILES +=	signals/ms_signals.c

SRCS_FILES +=	utils/free_exit.c

SRCS_FILES +=	minishell.c \
				main.c

SRCS = 			$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS =          $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c
	$(CC) -I$(HEADER_DIR) $(CFLAGS) -c $< -o $@

all:	$(NAME)

$(NAME):	$(OBJS_DIR) $(OBJS) $(HEADER)
	make -C $(LIBFT_DIR)
	$(CC) -I$(HEADER_DIR) $(RLFLAG) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT.A)
	@echo "\033[1;32mMANDATORY COMPILED SUCCESFULY!\033[0m"

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)
	mkdir -p $(OBJS_DIR)/builtins
	mkdir -p $(OBJS_DIR)/execute
	mkdir -p $(OBJS_DIR)/init
	mkdir -p $(OBJS_DIR)/parse
	mkdir -p $(OBJS_DIR)/signals
	mkdir -p $(OBJS_DIR)/utils

clean:
	$(RM) $(OBJS_DIR)
	@echo "\033[1;32mCLEAN EXECUTED SUCCESFULY!\033[0m"

fclean:	clean
	make fclean -C $(LIBFT_DIR)
	find -name '$(NAME)' -delete
	@echo "\033[1;32mFCLEAN EXECUTED SUCCESFULY!\033[0m"

re:
	@make fclean && make all
	@echo "\033[1;32mRE EXECUTED SUCCESFULY!\033[0m"

t:	$(NAME)
	@./minishell

# Bonus

# SRCS_B_DIR =   	srcs_b
# OBJS_B_DIR =   	$(SRCS_B_DIR)/.objs_b
# HEADER_B_DIR =  ./srcs_b
# HEADER_B =		$(HEADER_B_DIR)/checker.h
# NAME_B =		checker

# SRCS_B_FILES +=	operations/pa.c \
# 				operations/pb.c \
# 				operations/ra.c \
# 				operations/rb.c \
# 				operations/rr.c \
# 				operations/rra.c \
# 				operations/rrb.c \
# 				operations/rrr.c \
# 				operations/sa.c \
# 				operations/sb.c \
# 				operations/ss.c

# SRCS_B_FILES +=	steps/1_parse_error.c \
# 				steps/2_init.c \
# 				steps/3_execute_ops.c \
# 				steps/4_check_if_ops_sort.c \
# 				steps/5_clear.c

# SRCS_B_FILES +=	utils/ft_dll_op_add_back.c

# SRCS_B_FILES +=	checker.c

# SRCS_B = 		$(addprefix $(SRCS_B_DIR)/, $(SRCS_B_FILES))
# OBJS_B =        $(SRCS_B:$(SRCS_B_DIR)/%.c=$(OBJS_B_DIR)/%.o)
# $(OBJS_B_DIR)/%.o:	$(SRCS_B_DIR)/%.c
# 	$(CC) -I$(HEADER_B_DIR) $(CFLAGS) -c $< -o $@

# bonus:	$(NAME_B)

# $(NAME_B):	$(OBJS_B_DIR) $(OBJS_B) $(HEADER_B)
# 	make -C $(LIBFT_DIR)
# 	$(CC) -I$(HEADER_B_DIR) $(CFLAGS) $(OBJS_B) -o $(NAME_B) $(LIBFT.A)
# 	@echo "\033[1;32mBONUS COMPILED SUCCESFULY!\033[0m"

# $(OBJS_B_DIR):
# 	mkdir -p $(OBJS_B_DIR)
# 	mkdir -p $(OBJS_B_DIR)/operations
# 	mkdir -p $(OBJS_B_DIR)/sort
# 	mkdir -p $(OBJS_B_DIR)/steps
# 	mkdir -p $(OBJS_B_DIR)/utils

# clean_b:
# 	$(RM) $(OBJS_B_DIR)
# 	@echo "\033[1;32mCLEAN_B EXECUTED SUCCESFULY!\033[0m"

# fclean_b:	clean_b
# 	make fclean -C $(LIBFT_DIR)
# 	find -name '$(NAME_B)' -delete
# 	@echo "\033[1;32mFCLEAN_B EXECUTED SUCCESFULY!\033[0m"

# re_b:
# 	@make fclean_b && make bonus
# 	@echo "\033[1;32mRE_B EXECUTED SUCCESFULY!\033[0m"

# fclean_all:	clean clean_b
# 	make fclean -C $(LIBFT_DIR)
# 	find -name '$(NAME)' -delete
# 	find -name '$(NAME_B)' -delete
# 	@echo "\033[1;32mFCLEAN AND FCLEAN_B EXECUTED SUCCESFULY!\033[0m"

# re_all:
# 	@make fclean && make
# 	@make fclean_b && make bonus
# 	@echo "\033[1;32mRE AND RE_B EXECUTED SUCCESFULY!\033[0m"
