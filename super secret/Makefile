NAME 			= 	fdf
#BONUSNAME 		= 	checker

CC 				= 	gcc
RM 				= 	rm -rf

SRCDIR 			= 	./srcs/
OBJDIR 			= 	./obj/
INCDIR 			= 	./includes/

SRCS 			= 	fdf.c \
					main.c \
					utils.c \
					utils2.c \
					ft_split.c \
					draw_func.c \
					draw_func2.c \
					ft_atoi_base.c \
					get_next_line.c \
					get_next_line_utils.c \

OBJ 			= 	$(addprefix $(OBJDIR), $(SRCS:.c=.o))

BONUSOBJ 		= 	$(addprefix $(OBJDIR), $(BONUSSRCS:.c=.o))

all				: 	$(NAME)

$(OBJDIR)%.o 	: 	$(SRCDIR)%.c $(INCDIR)/fdf.h $(INCDIR)/get_next_line.h
					$(CC) $(CFLAGS) -Imlx -c $< -o $@ -I$(INCDIR) 

$(NAME)			: 	$(OBJDIR) $(OBJ) $(INCDIR) 
					$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean			:
					$(RM) $(OBJDIR)

fclean			: 	clean
					$(RM) $(NAME)

re				: 	fclean all

bonus			: 	$(BONUSNAME)

$(BONUSNAME)	: 	$(OBJDIR) $(BONUSOBJ)
					$(CC) $(CFLAGS)  $(BONUSOBJ) -o $(BONUSNAME)

$(OBJDIR)		:
					mkdir -p $(OBJDIR)
