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

//////////////////////////////////////////////
char	*ft_itoa_base_c(__int128_t value, int base, int up)
{
	char	*s;
	long	n;
	int		sign;
	int		i;

	n = (value < 0) ? -(long)value : value;
	sign = (value < 0 && base == 10) ? -1 : 0;
	i = (sign == -1) ? 2 : 1;
	while ((n /= base) >= 1)
		i++;
	if (base == 10 && up > i)
		i += up - i;
	s = (char*)malloc(sizeof(char) * (i + 1));
	s[i] = '\0';
	n = (value < 0) ? -(long)value : value;
	while (i-- + sign)
	{
		s[i] = (n % base < 10) ? n % base + '0' : n % base + ('A' + (-1 * up)) - 10;
		//printf("s[%d]: %s\n", i, s[i]);
		n /= base;
	}
	(i == 0) ? s[i] = '-' : 0;
	return (s);
}


//////////////////////////////////////////////
//////////////////////////////////////////////
/////////////////////////////////////////////////
int		ft_add_p(t_printf *p)
{
	int		i;
	char	*s;

	i = va_arg(p->li, int);
	s = ft_itoa_base_c(i, 16, 'A');
	if (p->sharp == 1)
		ft_add_buff_str(p, "0x");
	ft_add_buff_str(p, s);
	free(s);
	return (1);
}

char	*dtoa(char *s, double n)
{
	int digit, m, m1;
	char *c = s;
	int neg = (n < 0);
	int useExp;
	double weight;
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
		m = log10(n);///////////////////////////////
		useExp = (m >= 14 || (neg && m >= 9) || m <= -9);
		if (neg)
			*(c++) = '-';
		// set up for scientific notation
		if (useExp)
		{
			if (m < 0)
				m -= 1.0;
			n = n / pow(10.0, m);//////////////
			m1 = m;
			m = 0;
		}
		if (m < 1.0)
			m = 0;
			// convert the number
		while (n > 0.00000000000001 || m >= 0)
		{
			weight = pow(10.0, m);////////////////
			if (weight > 0 && !isinf(weight))
			{
				digit = floor(n / weight);
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
			else {
				*(c++) = '-';
				m1 = -m1;
			}
			m = 0;
			while (m1 > 0) {
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
		*(c) = '\0';
	}
	return s;
}

int 	ft_add_f(t_printf *p)
{
	double			f;
	char 			s[4000];


	f = va_arg(p->li, double);
//	printf("%f\n", f);
	dtoa(s, f);
	ft_add_buff_str(p, s);
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
	if (p->sharp == 1 && (*p->str == 'X' || *p->str == 'x'))
	{
		tmp = s;
		if (*p->str == 'x')
			s = ft_strjoin("0x", tmp);
		else
			s = ft_strjoin("0X", tmp);
		free(tmp);
	}
	i = -1;
	if (p->accuracy > 0 && p->accuracy < (int)ft_strlen(s))
		s[p->accuracy] = '\0';//////////////////////возможен инвалид врайт
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
			while(++i < (p->width - (int)ft_strlen(s)))
				ft_add_buff_char(p, c);
			i = -1;
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