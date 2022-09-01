.PHONY: all clean fclean re

CC =            clang
CFLAGS = 		-Wall -Wextra -Werror -ggdb3
RLFLAG =		-lreadline -ltinfo
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
				2_init/env/ms_last_env.c \
				2_init/env/ms_init_env.c \
				2_init/env/ms_update_env_value.c

SRCS_FILES +=	2_init/history/ms_add_history.c   \
				2_init/history/ms_print_history.c \
				2_init/history/ms_last_history.c \
				2_init/history/ms_init_history.c \
				2_init/history/ms_free_history.c

SRCS_FILES +=	3_read_input/ms_read_input.c \
				3_read_input/ms_here_doc.c \
				3_read_input/ms_signals.c \
				3_read_input/ms_signals_ctrl.c

SRCS_FILES +=	4_tokenizer/ms_tokenizer.c \
				4_tokenizer/ms_wildcard.c \
				4_tokenizer/ms_wildcard_utils.c \
				4_tokenizer/ms_check_quotes.c \
				4_tokenizer/ms_expand_dolar.c \
				4_tokenizer/ms_expand_dolar_utils.c \
				4_tokenizer/ms_sintax.c \
				4_tokenizer/ms_connectors_vs_quotes.c \
				4_tokenizer/ms_connectors_vs_quotes_utils.c

SRCS_FILES +=	5_parse/ms_parse.c \
				5_parse/ms_parse_prompts.c \
				5_parse/ms_parse_commands.c \
				5_parse/ms_parse_commands_utils.c \
				5_parse/ms_parse_commands_utils2.c \
				5_parse/ms_append_path_in_front.c \
				5_parse/ms_parse_input.c \
				5_parse/ms_parse_output.c \
				5_parse/cmd/ms_dll_cmd_last.c \
				5_parse/cmd/ms_dll_cmd_free.c \
				5_parse/prompt/ms_free_prompt.c

SRCS_FILES +=	6_execute/ms_execute_commands.c \
				6_execute/ms_execute_commands_utils_1.c \
				6_execute/ms_execute_commands_utils_2.c

SRCS_FILES +=	6_execute/builtins/ms_cd.c \
				6_execute/builtins/ms_echo.c \
				6_execute/builtins/ms_env.c \
				6_execute/builtins/ms_exit.c \
				6_execute/builtins/ms_export.c \
				6_execute/builtins/ms_export_utils.c \
				6_execute/builtins/ms_pwd.c \
				6_execute/builtins/ms_unset.c

SRCS_FILES +=	utils/ms_reinit.c \
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
	mkdir -p $(OBJS_DIR)/4_tokenizer
	mkdir -p $(OBJS_DIR)/5_parse
	mkdir -p $(OBJS_DIR)/5_parse/prompt
	mkdir -p $(OBJS_DIR)/5_parse/cmd
	mkdir -p $(OBJS_DIR)/6_execute
	mkdir -p $(OBJS_DIR)/6_execute/builtins
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


# TEST
SUPP="../../42-minishell-capela-tester/tests/suppression.supp"

run:	$(NAME)
	@./minishell

runs:	$(NAME)
	@valgrind  --suppressions=$(SUPP) --track-origins=yes ./minishell

runl:	$(NAME)

	@valgrind  --suppressions=$(SUPP) --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes ./minishell

runr:	$(NAME)
	make re
	@./minishell

runrl:	$(NAME)
	make re
	@valgrind  --suppressions=$(SUPP) --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes ./minishell

n:
	norminette *

t:
	bash test.sh