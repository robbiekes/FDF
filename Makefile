NAME 			= 	valentine
FCARD			= 	f
SCARD			= 	s
TCARD			=	t
FIRST			=	"./valentine test_maps/card1.fdf"
SEC				=	"./valentine test_maps/card2.fdf"
THIRD			=	"./valentine test_maps/card3.fdf"
GREETINGS		=	"		ПРИВЕТ, МОЁ СОЛНЫШКО!!"
					
				#	Я нарисила для тебя смешно-романтишно-эротишные валентинки
				#	Их всего 3, и лучше их открывать по порядку";

#		printf("Usage: make [options] [target]\n");
#	printf("Options:\n");
# printf("\t-f\tdisplays first valentine card


CC 				= 	gcc
RM 				= 	rm -rf

SRCDIR 			= 	./srcs/
OBJDIR 			= 	./obj/
INCDIR 			= 	./includes/

SRCS 			= 	valentine.c \
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
					@echo ""
					@echo ""
					@echo "	✿✿✿✿ ПРИВЕТ, МОЁ СОЛНЫШКО!! ✿✿✿✿ "
					@echo "Я нарисила для тебя смешно-романтишно-эротишные валентинки"
					@echo "Их всего 3, и лучше их открывать по порядку";
					@echo "А также можешь полюбоваться на наши милые портретики"
					@echo ""
					@echo ""
					@echo "		Команды:"
					@echo "make f   ->  первая открытка"
					@echo "make s   ->  вторая открытка"
					@echo "make t   ->  третья открытка (осторожно!! хорни)"
					@echo "open d   ->  портрет моего любимого котика"
					@echo "open z   ->  портрет одной хорошей девочки"
					@echo ""
					@echo ""
					@echo "Я люблю тебя, мой самый красивый, ласковый, нежный, верный мальчик ♥♥♥♥♥♥♥♥"

clean			:
					$(RM) $(OBJDIR)

fclean			: 	clean
					$(RM) $(NAME)

re				: 	fclean all

$(FCARD)		:	
					bash -c $(FIRST)

$(SCARD)		:	
					bash -c $(SEC)

$(TCARD)		:	
					bash -c $(THIRD)

$(OBJDIR)		:
					mkdir -p $(OBJDIR)
