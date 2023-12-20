# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/22 16:28:22 by osarsari          #+#    #+#              #
#    Updated: 2023/09/21 12:20:09 by osarsari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================ VARIABLES ================================= #

# The name of the executable
NAME	= libft.a

# Compiler and compiling flags
CC	= gcc
CFLAGS	= -Wall -Werror -Wextra

# Debug, use with`make DEBUG=1`
ifeq ($(DEBUG),1)
CFLAGS	+= -g3 -fsanitize=address
endif

# Folder names
SRCDIR	= ./
OBJDIR	= obj/
GNL = GNL/
PRINTF = Printf/
INCLUDES = ../../includes/

# List of source files (add your *.c files here)
SRCS =\
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	$(PRINTF)ft_c.c \
	$(PRINTF)ft_hex.c \
	$(PRINTF)ft_point.c \
	$(PRINTF)ft_printf.c \
	$(PRINTF)ft_put_un_int.c \
	$(PRINTF)ft_putnbr.c \
	$(PRINTF)ft_str.c \
	$(GNL)get_next_line_utils.c \
	$(GNL)get_next_line.c \
	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_isspace.c

# List of header files (add your *.h files here)
HEADERS =\
	$(INCLUDES)libft.h\

# String manipulation magic
SRC		:= $(notdir $(SRCS))
OBJ		:= $(SRC:.c=.o)
OBJS	:= $(addprefix $(OBJDIR), $(OBJ))

# Colors
GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m

# Implicit rules
VPATH := $(SRCDIR) $(OBJDIR) $(shell find $(SRCDIR) -type d)

# ================================== RULES =================================== #

all : $(OBJDIR) $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Compiling
$(OBJDIR)%.o : %.c $(HEADERS)
	@mkdir -p $(OBJDIR)
	@printf "$(GR)+$(RC)"
	@$(CC) $(CFLAGS) -c $< -o $@


# Linking
$(NAME): $(OBJS)
	@printf "$(GR)=== Archiving $(NAME) ===$(RC)\n"
	@ar rcs $(NAME) $(OBJS)
	@printf "$(YE)=== $(NAME) created ===$(RC)\n"

# Cleaning
clean :
	@printf "$(RE)--- Removing $(OBJDIR)$(RC)\n"
	@rm -rf $(OBJDIR)

fclean : clean
	@printf "$(RE)--- Removing $(NAME)$(RC)\n"
	@rm -f $(NAME)

# Special rule to force to remake everything
re : fclean all

# Special rule to check if files conform to the norm
norm :
	@printf "$(CY)=== Checking norm ===$(RC)\n"
	@norminette $(SRCDIR) $(HEADERS)

# This specifies the rules that does not correspond to any filename
.PHONY	= all run clean fclean re norm
