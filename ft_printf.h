#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
#include <stdint.h>
# include "libft/libft.h"

int buff_size;////////////////////////////////////////////////////

# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define PURPLE		"\033[35m"
# define CYAN		"\033[36m"
# define EOC		"\033[0m"

typedef struct			s_printf
{
	int					len;
	int 				sharp;
	int 				zero;
	int 				minus;
	int 				space;
	int 				plus;
	int 				point;
	int					width;//ширина
	int					accuracy;//точность
	int					fd;
	int					buff_index;
	char				*buff;//буфер
	va_list				li;
	char				*str;
	int					l;
	int					h;
	int					L;
}						t_printf;

int		ft_printf(const char *format, ...);
void	ft_realloc_buff(t_printf *p);
/*
**ft_add_c_s_d.c
*/
int 	ft_addchar(t_printf *p);
int		ft_addstr(t_printf *p);
int 	ft_addnbr(t_printf *p);
int 	ft_add_buff(t_printf *p);
int 	ft_add_buff_char(t_printf *p, char c);
int		ft_add_buff_str(t_printf *p, char *s);
////////////////////////////////////////////////
int		ft_add_p(t_printf *p);
//char	*ft_itoa_base_c(__int128_t value, int base, char c);
char	*ft_itoa_base_c(__int128_t n, int base, int up);
int		ft_add_ouxX(t_printf *p);
int 	ft_add_f(t_printf *p);
int 	ft_addchar_c(t_printf *p, char ch);
/*
**ft_color.c
*/
int 	ft_color(t_printf *p);

/*
** PARSER
*/
int 	ft_parser(t_printf *p);
void	ft_reset_flags(t_printf *p);
void	ft_get_flags(t_printf *p);
int		is_a_flag(char c);
int		is_a_printf_flag(char c);
int 	ft_tocnost(t_printf *p);
int 	is_a_digit(char c);

#endif