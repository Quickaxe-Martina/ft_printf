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


# define RED		"\x1B[31m"
# define GREEN		"\x1B[32m"
# define YELLOW		"\x1B[33m"
# define BLUE		"\x1B[34m"
# define PURPLE		"\x1B[35m"
# define CYAN		"\x1B[36m"
# define EOC		"\x1B[0m"

# define MAX(a, b)		b & ((a - b) >> 31) | a & (~(a - b) >> 31)
# define MIN(a, b)		a & ((a - b) >> 31) | b & (~(a - b) >> 31)
# define ABS(a)			(a < 0) ? -a : a
# define DABS(a)		(a < 0.0f) ? -a : a
# define STRERR			strerror
# define DEC "0x"

# define F_SHARP		(1 << 0)
# define F_SPACE		(1 << 1)
# define F_PLUS			(1 << 2)
# define F_MINUS		(1 << 3)
# define F_ZERO			(1 << 4)
# define F_WILDCARD		(1 << 5)
# define F_UPCASE		(1 << 6)
# define F_SHORT		(1 << 7)
# define F_SHORT2		(1 << 8)
# define F_LONG			(1 << 9)
# define F_LONG2		(1 << 10)
# define F_INTMAX		(1 << 11)
# define F_SIZE_T		(1 << 12)
# define F_MIN_LEN		(1 << 13)
# define F_APP_PRECI	(1 << 14)
# define F_POINTER		(1 << 15)

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
	int 				buff_size;
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
int		ft_add_p(t_printf *p);
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
//////////
int64_t ft_floor(long double base);
long double	ft_pow(long double base, long double exp);
int64_t ft_log10(long double base);
int 	ft_add_plus(t_printf *p, int flag);
char 	*ft_add_accur(char *str, int acu, t_printf *p);

#endif