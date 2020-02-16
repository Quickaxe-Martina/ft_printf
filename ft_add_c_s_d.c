#include "ft_printf.h"

int 	ft_addchar(t_printf *p)
{
	int 		c;
	int			i;

	i = 0;
	if (p->width > 0)
	{
		if (p->minus == 1)
			ft_add_buff_char(p, va_arg(p->li, int));
		if (p->zero == 1)
			c = '0';
		else
			c = ' ';
		while(++i < p->width)
			ft_add_buff_char(p, c);
		if (p->minus == 0)
			ft_add_buff_char(p, va_arg(p->li, int));
	}
	else
		ft_add_buff_char(p, va_arg(p->li, int));
	return (1);
}

int		ft_addstr(t_printf *p)
{
	char	*s;
	int		i;
	char	c;

	i = -1;
	s = strdup(va_arg(p->li, char*));
	if (s == NULL)
		s = strdup("(null)");///////////////////////////////////////////
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
	free(s);
	return (1);
}

int 	ft_addnbr(t_printf *p)
{
	__int128_t 	nbr;
	__int128_t	i;
	__int128_t 	t;
	__int128_t	k;
	char		c;

	//nbr = va_arg(p->li, int);
	nbr = va_arg(p->li, long long);
	nbr = (p->l == 0) ? (int)nbr : nbr;
	nbr = (p->h == 1) ? (short)nbr : nbr;
	nbr = (p->h == 2) ? (char)nbr : nbr;
	t = nbr;
	i = 1;
	k = 1;
	while (t > 9)
	{
		t /= 10;
		i *= 10;
		k++;
	}
	t = -1;
	if (p->width > 0 && k < p->width)
	{
		if (p->zero == 1)
			c = '0';
		else
			c = ' ';
		if (p->minus == 1)
		{
			while (i > 0)
			{
				ft_add_buff_char(p, (nbr / i) % 10 + 48);
				i /= 10;
			}
			while(++t < (p->width - k))
				ft_add_buff_char(p, c);
		}
		else if (p->minus == 0)
		{
			while(++t < (p->width - k))
				ft_add_buff_char(p, c);
			while (i > 0)
			{
				ft_add_buff_char(p, (nbr / i) % 10 + 48);
				i /= 10;
			}
		}
	}
	else
	{
		while (i > 0)
		{
			ft_add_buff_char(p, (nbr / i) % 10 + 48);
			i /= 10;
		}
	}
	return (1);
//	printf("nbr original: %d\n", nbr);
}

int 	ft_add_buff(t_printf *p)
{
	if (p->buff_index == buff_size)
		ft_realloc_buff(p);
	p->buff[p->buff_index++] = *p->str;
	return (1);
}

int 	ft_add_buff_char(t_printf *p, char c)
{
	if (p->buff_index == buff_size)
		ft_realloc_buff(p);
	p->buff[p->buff_index++] = c;
	return (1);
}

int		ft_add_buff_str(t_printf *p, char *s)
{
	int	i;

	i = -1;
	while(s[++i])
		ft_add_buff_char(p, s[i]);
	return (i);
}

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
	s = (char*)malloc(sizeof(char) * (i + 1));
	s[i] = '\0';
	n = (value < 0) ? -(long)value : value;
	while (i-- + sign)
	{
		s[i] = (n % base < 10) ? n % base + '0' : n % base + ('A' + up) - 10;
		//printf("s[%d]: %s\n", i, s[i]);
		n /= base;
	}
	(i == 0) ? s[i] = '-' : 0;
	return (s);
}

/*int		ft_countdigits_base(__int128_t n, int base)
{
	int		res;

	if (n == 0)
		return (1);
	res = 0;
	while (n != 0)
	{
		res++;
		n /= base;
	}
	return (res);
}

char	*ft_itoa_base(__int128_t n, int base, int up)
{
	int		d;
	char	*res;
	char	*array;

	array = (up == 0) ? "0123456789abcdef" : "0123456789ABCDEF";
	d = ft_countdigits_base(n, base);
	d = (n < 0) ? ++d : d;
	//res = strnew(d);
	res = (char*)malloc(sizeof(char) * d + 1);
	if (res == NULL)
		return (NULL);
	if (n < 0)
	{
		if (n == INT64_MIN)
			return (strcpy(res, "-9223372036854775808"));///////////////
		res[0] = '-';
		n = -n;
	}
	res = (n == 0) ? strcpy(res, "0") : res;///////////////////////
	while (n != 0)
	{
		res[d - 1] = array[n % base];
		d--;
		n /= base;
	}
	return (res);
}*/

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

int 	ft_add_f(t_printf *p)
{
	int a;

	a = p->len;
	return (1);
}

int		ft_add_ouxX(t_printf *p)
{
	__int128_t	i;
	char		*s;

	//i = va_arg(p->li, int);
	//printf("i= %d\n", i);
	s = NULL;
	i = va_arg(p->li, unsigned long long);
	i = (p->l == 0) ? (unsigned)i : i;
	i = (p->h == 1) ? (unsigned short)i : i;
	i = (p->h == 2) ? (unsigned char)i : i;
	//printf("p->h= %d\n", p->h);
	//printf("orig2: u:%hhu;o:%hho;x:%hhx;X:%hhX;\n", i, i, i, i);
	/*else
	{
		i = va_arg(li, long long);
		i = (p->l == 0) ? (int)i : i;
	}*/
	if (*p->str == 'o')
		s = ft_itoa_base_c(i, 8, 32);
	else if (*p->str == 'u')
		s = ft_itoa_base_c(i, 10, 32);
	else if (*p->str == 'x')//делать х маленькое
		s = ft_itoa_base_c(i, 16, 32);
	else if (*p->str == 'X')
		s = ft_itoa_base_c(i, 16, 0);
	ft_add_buff_str(p, s);
	free(s);
	return (1);
}