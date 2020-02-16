#include "ft_printf.h"

int 	ft_tocnost(t_printf *p)
{
	if (p->point == 0)
	{
		p->width = ft_atoi(p->str);
//		printf("WWaccur: %d\n", p->width);
		while (*p->str >= '0' && *p->str <= '9')
			p->str++;
		if (*p->str == '.')
		{
			p->str++;
			p->accuracy = ft_atoi(p->str);
			p->point = 1;
//			printf("TTaccur: %d\n", p->accuracy);
		}
	}
	else
		p->accuracy = ft_atoi(p->str);
	while (*p->str >= '0' && *p->str <= '9')
		p->str++;
	//printf("p->shir= %d\np->toc= %d\n", p->width, p->accuracy);
	return (1);
}

int		is_a_printf_flag(char c)
{
	if (c == '#' || c == '0' || c == '-' || c == ' ' || c == '+' || c == '.')
		return (1);
	return (0);
}

int 	is_a_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int		is_a_flag(char c)
{
	if (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' || c == 'i' ||
		c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'x' || c == 'X' ||
		c == 'c' || c == 'C' || c == '.' || c == '%' || c == 'h' || c == 'l' ||
		c == 'j' || c == 'z' || c == 'f' || is_a_digit(c))
		return (1);
	return (0);
}

void	ft_get_flags(t_printf *p)
{
	while (is_a_printf_flag(*p->str))
	{
		if (*p->str == '#')
			p->sharp = 1;
		else if (*p->str == '0' && *(p->str + 1) != '.')
			p->zero = 1;
		else if (*p->str == '-')
			p->minus = 1;
		else if (*p->str == ' ')
			p->space = 1;
		else if (*p->str == '+')
			p->plus = 1;
		else if (*p->str == '.')
		{
			p->zero = 0;
			p->point = 1;
			p->str++;
			break ;
		}
		p->str++;
	}
}

void	ft_reset_flags(t_printf *p)
{
	p->sharp = 0;
	p->zero = 0;
	p->minus = 0;
	p->space = 0;
	p->plus = 0;
	p->point = 0;
	p->width = 0;
	p->accuracy = 0;
	p->l = 0;
	p->h = 0;
	p->L = 0;
}

void	ft_cheak_lhL(t_printf *p)
{
	while(*p->str == 'l' || *p->str == 'h' || *p->str == 'L')
	{
		if (*p->str == 'l')
			p->l++;
		else if (*p->str == 'h')
			p->h++;
		else if (*p->str == 'L')
			p->L++;
		p->str++;
	}
}

int 	ft_parser(t_printf *p)
{
	ft_reset_flags(p);
	ft_get_flags(p);
	if (!is_a_flag(*p->str))
	{
		p->str--;
		return (-1);
	}
	p->space = (p->plus == 1 && p->space == 1) ? 0 : p->space;
	p->zero = (p->zero == 1 && p->minus == 1) ? 0 : p->zero;
	if (is_a_digit(*p->str))
		ft_tocnost(p);
	ft_cheak_lhL(p);
	if (*p->str == 's')
		ft_addstr(p);
	else if (*p->str == 'c')
		ft_addchar(p);
	else if (*p->str == '%')
	{
		ft_addchar_c(p, '%');
	}
	else if (*p->str == 'd' || *p->str == 'i')
		ft_addnbr(p);
	else if (*p->str == 'f')
	{
//		ft_add_f(p);
		;
	}
	else if (*p->str == 'p')
		ft_add_p(p);
	else if (*p->str == 'o' || *p->str == 'u' || *p->str == 'x' || *p->str == 'X')
		ft_add_ouxX(p);
	return (1);
}

int		ft_printf(const char *format, ...)
{
	t_printf p;

	p.fd = 1;
	buff_size = 64;////////////////////////////////////////////////
	p.buff = (char *)malloc(sizeof(char) * buff_size);
	p.buff_index = 0;
	p.len = 0;
	p.str = (char *)format;
	va_start(p.li, format);
	while (*p.str)
	{
		if (*p.str == '%')
		{
			if (!(++p.str))
				break ;
			ft_parser(&p);
		}
		else if (*p.str == '{')
			ft_color(&p);
		else
			ft_add_buff(&p);
		p.str++;
	}
	write(p.fd, p.buff, p.buff_index);
	va_end(p.li);
	return (p.buff_index);/////////////////////////////////
}