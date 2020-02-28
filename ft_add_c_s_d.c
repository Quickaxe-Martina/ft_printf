#include "ft_printf.h"
#include <stdlib.h>
#include <math.h>
/*int 	ft_addnbr(t_printf *p)
{
	__int128_t 	nbr;
	__int128_t	k;
	char 		*s;
	char		c;

	//nbr = va_arg(p->li, int);
	nbr = va_arg(p->li, long long);
	nbr = (p->l == 0) ? (int)nbr : nbr;
	nbr = (p->h == 1) ? (short)nbr : nbr;
	nbr = (p->h == 2) ? (char)nbr : nbr;
	s = ft_itoa_base_c(nbr, 10, p->accuracy);
	k = ft_strlen(s);
	if (p->width > 0 && k < p->width)
	{
		c = p->zero ? '0' : ' ';
		if (p->minus == 1)
		{
			ft_add_buff_str(p, s);
			while(p->width - ++k)
				ft_add_buff_char(p, c);
		}
		else if (p->minus == 0)
		{
			while(p->width - ++k)
				ft_add_buff_char(p, c);
			ft_add_buff_str(p, s);
		}
	}
	else
	{
		ft_add_buff_str(p, s);
	}
	free(s);
	return (1);
//	printf("nbr original: %d\n", nbr);
}*/

char	*dtoa(char *s, long double n)
{
	int64_t digit;
	int64_t m;
	int64_t m1;
	char *c = s;
	int neg = (n < 0);
	int useExp;
	long double weight;
	int i, j;
	// handle special case обрабатывать особые случаи
	if (isnan(n))
		ft_strcpy(s, "nan");
	else if (isinf(n))
		ft_strcpy(s, "inf");
	else if (n == 0.0)
		ft_strcpy(s, "0");
	else
	{
		//делваем число поможительным
		if (neg)
			n = -n;
		// calculate magnitude рассчитать величину
		m = ft_log10(n);
		useExp = (m >= 14 || (neg && m >= 10) || m <= -9);
//		printf("\nm: %lld\n", m);
		if (neg)
			*(c++) = '-';
		// set up for scientific notation
		if (useExp)
		{
			if (m < 0)
				m -= 1.0;
			n = n / ft_pow(10.0, m);
			m1 = m;
			m = 0;
		}
//		printf("\nn: %Lf\n", n);
		if (m < 1.0)
			m = 0;
			// convert the number
		while (n >= 0.0000000000000000000001 || m >= 0)
		{
			weight = ft_pow(10.0, m);
			if (weight > 0 && !isinf(weight))
			{
//				write(1, "GHF\n", 4);
				digit = ft_floor(n / weight);
//				printf("dig: %lld", digit);
				n -= (digit * weight);
				*(c++) = '0' + digit;
			}
			if (m == 0 && n > 0)
				*(c++) = '.';
			m--;
		}
		if (useExp)
		{
			// convert the exponent
			*(c++) = 'e';
			if (m1 > 0)
				*(c++) = '+';
			else
			{
				*(c++) = '-';
				m1 = -m1;
			}
			m = 0;
			while (m1 > 0)
			{
				*(c++) = '0' + m1 % 10;
				m1 /= 10;
				m++;
			}
			c -= m;
			i = 0;
			j = m - 1;
			while (i < j)
			{
				// swap without temporary
				c[i] ^= c[j];
				c[j] ^= c[i];
				c[i] ^= c[j];
				i++;
				j--;
			}
			c += m;
		}
//		*(c) = '\0';
	}
	return (s);
}

/*double	ft_pow(double n, int pow)
{
	return (pow ? n * ft_pow(n, pow - 1) : 1);
}

static void		ldtoa_fill(double n, t_printf *p, long value)
{
	int		len;
	int		accuracy;
	char	s[48];

	len = p->printed - 1 - p->precision;
	accuracy = p->printed - 1 - len;
	while (accuracy--)
	{
		s[len + accuracy + 1] = value % 10 + '0';
		value /= 10;
	}
	(p->precision > 0) ? s[len] = '.' : 0;
	value = (long)(ABS(n));
	while (++accuracy < len)
	{
		s[len - accuracy - 1] = value % 10 + '0';
		value /= 10;
	}
	(p->f & F_APP_PRECI && p->f & F_ZERO) ? s[0] = ' ' : 0;
	(p->f & F_SPACE) ? s[0] = ' ' : 0;
	(n < 0) ? s[0] = '-' : 0;
	(p->f & F_PLUS && n >= 0) ? s[0] = '+' : 0;
//	buffer(p, s, len + 1 + 6);
}

void			pf_putdouble(t_printf *p)
{
	double		n;
	long		tmp;
	int			len;
	double		decimal;
	long		value;

	n = (double)va_arg(p->li, double);
	(p->f & F_ZERO) ? p->precision = p->min_length : 0;
	if (!(p->f & F_APP_PRECI))
		p->precision = 6;
	len = (p->precision > 0) ? 1 : 0;
	tmp = (long)(ABS(n));
	while (tmp && ++len)
		tmp /= 10;
	(p->f & F_ZERO) ? p->precision = p->min_length : 0;
	p->printed = p->precision + len + ((n < 0) ? 1 : 0);
	decimal = ((n < 0.0f) ? -n : n);
	decimal = (decimal - (long)(((n < 0.0f) ? -n : n))) *
			  ft_pow(10, p->precision + 1);
	decimal = ((long)decimal % 10 > 4) ? (decimal) / 10 + 1 : decimal / 10;
	value = (int)decimal;
	ldtoa_fill(n, p, value);
}*/

void	ft_okr(char *s, t_printf *p)
{
	int i;
	int j;

	if (p->accuracy == -1)
		p->accuracy = 6;
//	i = -1;
//	while (s[++i])
//		;
	j = -1;
	while (s[++j] && s[j] != '.')
		;
	j++;
	i = j + p->accuracy;
	if (s[i] >= '5')
	{
		s[i] = '0';
		while (s[i - 1] && s[i - 1] == '9')
		{
			s[i - 1] = '0';
			i--;
		}
		if (s[i - 1] != '.')
			s[i - 1]++;
		else
		{
			while (s[i - 2] && s[i - 2] == '9')
			{
				s[i - 2] = '0';
				i--;
			}
			s[i - 2]++;
		}
	}
	s[j + p->accuracy] = '\0';
	if (p->sharp == 1)
		s[j++ - 1] = '.';
	if (p->accuracy == 0)
		s[j - 1] = '\0';
}

int 	is_one(char *str, long double f)
{
	int64_t i;
	int64_t j;

	if (f - (int64_t)f == 0)
	{
		i = (int64_t)f;
		j = 1;
		while (i /= 10)
			j++;
		if (f < 0.0)
			j++;
		str[j] = '.';
	}
	i = 0;
	while (++i < 3999)
	{
		if (str[i] != '0')
			return (0);
	}
	str[1] = '.';
	return (1);
}

int 	ft_add_f(t_printf *p)
{
	long double			f;
	char 			s[4000];
	int				k;
	char 			c;

	k = -1;
	while (++k < 4000)
		s[k] = '0';
	s[k] = '\0';
	if (p->L == 1)
		f = va_arg(p->li, long double);
	else
		f = va_arg(p->li, double);
	dtoa(s, f);
	is_one(s, f);
	ft_okr(s, p);
	k = ft_strlen(s);
	if (p->zero == 1)
		p->minus = 0;
	if (p->space == 1 && (f >= 0.0))
		ft_add_buff_char(p, ' ');
	else
		p->width++;
	if (p->width > 0 && k < p->width)
	{
		c = p->zero ? '0' : ' ';
		if (p->minus == 1)
		{
			k += p->plus && f >= 0.0 ? ft_add_plus(p, 1) : 0;
			ft_add_buff_str(p, s);
			while((p->width - ++k) > 0)
				ft_add_buff_char(p, c);
		}
		else if (p->minus == 0)
		{
			p->width -= f < 0.0 && p->zero ? ft_add_buff_char(p, '-') : 0;
			s[0] = f < 0.0 && p->zero && p->width > k ? '0' : s[0];
			k += p->plus && f >= 0.0 && p->zero ? ft_add_plus(p, 1) : 0;
			while(++k < p->width)
				ft_add_buff_char(p, c);
			if (p->width == (int)ft_strlen(s) - 1)
				p->buff_index--;
			p->plus && f >= 0.0 && !p->zero ? ft_add_plus(p, 1) : 0;
			ft_add_buff_str(p, s);
		}
	}
	else
	{
		p->plus && f >= 0.0 ? ft_add_plus(p, 0) : 0;
		ft_add_buff_str(p, s);
	}
	return (1);
}

char 	*ft_add_accur2(char *str, int acu, t_printf *p)
{
	char 	*s;
	int		i;
	int		len;

	if (!(s = (char *)malloc(sizeof(char) * acu + 1)))
	{
		ft_putstr_fd("malloc error\n", 2);
		exit (1);
	}
	len = (int)ft_strlen(str);
	i = -1;
	if (str[0] == '-')
	{
		s[++i] = '-';
		str[0] = '0';
		len--;
	}
	while (++i < (acu - len))
		s[i] = '0';
	len = -1;
	while (str[++len])
		s[i + len] = str[len];
	s[i + len] = '\0';
	free(str);
	p->zero = p->accuracy > 0 ? 0 : p->zero;
	return (s);
}

int 	is_nul(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '0')
			return (0);
	}
	return (1);
}

int		ft_add_ouxX(t_printf *p)
{
	__int128_t	i;
	char		*s;
	char 		*tmp;
	char 		c;

	s = NULL;
	i = va_arg(p->li, unsigned long long);
	i = (p->l == 0) ? (unsigned)i : i;
	i = (p->h == 1) ? (unsigned short)i : i;
	i = (p->h == 2) ? (unsigned char)i : i;
	if (*p->str == 'o')
		s = ft_itoa_base_c(i, 8, -32);
	else if (*p->str == 'u')
		s = ft_itoa_base_c(i, 10, -32);
	else if (*p->str == 'x')//делать х маленькое
		s = ft_itoa_base_c(i, 16, -32);
	else if (*p->str == 'X')
		s = ft_itoa_base_c(i, 16, 0);
	if (p->accuracy == 0 || (p->accuracy == -1 && p->point == 1))
		ft_bzero(s, ft_strlen(s));
	if (p->sharp == 1 && *p->str == 'o' && (i > 0 || (p->point == 1 && i == 0)))
	{
		tmp = s;
		s = ft_strjoin("0", tmp);
		free(tmp);
	}
	s = ft_add_accur2(s, p->accuracy, p);
	if (p->sharp == 1 && (*p->str == 'X' || *p->str == 'x') && i != 0 && !is_nul(s))
	{
		tmp = s;
		if (*p->str == 'x')
			s = ft_strjoin("0x", tmp);
		else
			s = ft_strjoin("0X", tmp);
		free(tmp);
	}
	i = -1;
//	if (p->accuracy > 0 && p->accuracy < (int)ft_strlen(s))
//		s[p->accuracy] = '\0';//////////////////////возможен инвалид врайт
	if (p->width > 0 && p->width > (int)ft_strlen(s))
	{
		if (p->zero == 1)
			c = '0';
		else
			c = ' ';
		if (p->minus == 1)
		{
			while(s[++i])
				ft_add_buff_char(p, s[i]);
			while(++i <= p->width)
				ft_add_buff_char(p, c);
		}
		else if (p->minus == 0)
		{
//			printf("\nwe: %d\n", p->width);
			if (p->sharp == 1 && (*p->str == 'X' || *p->str == 'x') && c == '0' && !is_nul(s))
			{
				s[1] = '0';
				if (*p->str == 'x')
					ft_add_buff_str(p, "0x");
				if (*p->str == 'X')
					ft_add_buff_str(p, "0X");
				p->width -= 2;
			}
			while(++i < (p->width - (int)ft_strlen(s)))
				ft_add_buff_char(p, c);
			i = (p->buff[p->buff_index - 1] == 'x' || p->buff[p->buff_index - 1] == 'X') && p->sharp == 1 && c == '0' ? 0 : -1;
			while(s[++i])
				ft_add_buff_char(p, s[i]);
		}
	}
	else
	{
		while(s[++i])
			ft_add_buff_char(p, s[i]);
	}
//	ft_add_buff_str(p, s);
	free(s);
	return (1);
}