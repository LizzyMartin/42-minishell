.PHONY: all clean fclean re

CC =            clang
CFLAGS = 		-Wall -Wextra -Werror -ggdb3
RLFLAG =		-lreadline
AR =            ar -rcs
RM =            rm -rfd

LIBFT_DIR = 	libs/libft
LIBFT.A =       $(LIBFT_DIR)/libft.a

# Mandatory

SRCS_DIR =   	srcs
OBJS_DIR =   	$(SRCS_DIR)/.objs
HEADER_DIR =   ./srcs/0_includes
HEADER =		$(HEADER_DIR)/minishell.h
NAME =			minishell

SRCS_FILES +=	1_design/ms_print_banner.c

SRCS_FILES +=	2_init/ms_init.c		


SRCS_FILES +=	2_init/env/ms_add_env.c \
				2_init/env/ms_delete_env.c \
				2_init/env/ms_find_env_value.c \
				2_init/env/ms_free_env.c \
				2_init/env/ms_is_in_env.c \
				2_init/env/ms_parse_env.c \
				2_init/env/ms_init_env.c

SRCS_FILES +=	2_init/history/ms_add_history.c   \
				2_init/history/ms_print_history.c \
				2_init/history/ms_last_history.c \
				2_init/history/ms_init_history.c

SRCS_FILES +=	3_read_input/ms_read_input.c \
				3_read_input/ms_here_doc.c \
				3_read_input/ms_signals.c \
				3_read_input/ms_signals_ctrl.c

SRCS_FILES +=	4_tokenizer/ms_tokenizer.c \
				4_tokenizer/ms_wildcard.c \
				4_tokenizer/ms_check_quotes.c

SRCS_FILES +=	5_parse/ms_parse.c \
				5_parse/ms_if_there_is_commands_prepare_them_to_be_executed.c \
				5_parse/ms_append_path_in_front.c \
				5_parse/ms_parse_input.c \
				5_parse/ms_parse_output.c \
				5_parse/cmd/ms_dll_cmd_last.c

SRCS_FILES +=	6_execute/ms_execute_commands.c \
				6_execute/ms_execute_commands_utils.c 

SRCS_FILES +=	6_execute/builtins/ms_cd.c \
				6_execute/builtins/ms_echo.c \
				6_execute/builtins/ms_env.c \
				6_execute/builtins/ms_exit.c \
				6_execute/builtins/ms_export.c \
				6_execute/builtins/ms_pwd.c \
				6_execute/builtins/ms_unset.c

SRCS_FILES +=	utils/ms_free.c \
				utils/ms_finish.c

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
	mkdir -p $(OBJS_DIR)/1_design
	mkdir -p $(OBJS_DIR)/2_init
	mkdir -p $(OBJS_DIR)/2_init/env
	mkdir -p $(OBJS_DIR)/2_init/history
	mkdir -p $(OBJS_DIR)/3_read_input
	mkdir -p $(OBJS_DIR)/5_tokenizer
	mkdir -p $(OBJS_DIR)/6_parse
	mkdir -p $(OBJS_DIR)/6_parse/cmd
	mkdir -p $(OBJS_DIR)/7_execute
	mkdir -p $(OBJS_DIR)/7_execute/builtins
	mkdir -p $(OBJS_DIR)/utils
	mkdir -p $(OBJS_DIR)/utils/dll_cmd

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

tv:	$(NAME)
	@valgrind --suppressions=srcs/supression.supp --track-origins=yes ./minishell

add_supp: $(NAME)
	@valgrind --gen-suppressions=yes ./minishell


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
