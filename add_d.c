/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 22:47:19 by qmartina          #+#    #+#             */
/*   Updated: 2020/02/16 22:47:20 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char 	*ft_add_accur(char *str, int acu, t_printf *p)
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
	p->zero = 0;
	return (s);
}

int 	ft_add_plus(t_printf *p)
{
	if (p->buff_index != 0)
		p->buff_index--;
	ft_add_buff_char(p, '+');
	return (1);
}

int 	ft_addnbr(t_printf *p)
{
	__int128_t 	nbr;
	char 		*s;
	__int128_t	k;
	char		c;

	nbr = va_arg(p->li, long long);
	nbr = (p->l == 0) ? (int)nbr : nbr;
	nbr = (p->h == 1) ? (short)nbr : nbr;
	nbr = (p->h == 2) ? (char)nbr : nbr;
	s = ft_itoa_base_c(nbr, 10, 0);
	if (p->accuracy > (int)ft_strlen(s) || (nbr < 0 && p->accuracy > (int)ft_strlen(s) - 1))
		s = ft_add_accur(s, p->accuracy, p);
	p->zero = p->accuracy > 0 ? 0 : p->zero;
	k = ft_strlen(s) - 1;
//	printf("PLUS: %s",s);
	if (p->width > 0 && k < p->width)
	{
		c = p->zero ? '0' : ' ';
		if (p->minus == 1)
		{
//			p->buff[p->buff_index - 1] = p->plus == 1 && nbr >= 0 ? '+' : p->buff[p->buff_index - 1];
			k += p->plus && nbr >= 0 ? ft_add_plus(p) : 0;
			ft_add_buff_str(p, s);
			while(p->width - ++k)
				ft_add_buff_char(p, c);
		}
		else if (p->minus == 0)
		{
			p->width -= nbr < 0 && p->zero ? ft_add_buff_char(p, '-') : 0;
			s[0] = nbr < 0 && p->zero && p->width > k ? '0' : s[0];
//			printf("PLUS: %s",s);
			k += p->plus && nbr >= 0 && p->zero ? ft_add_plus(p) : 0;
			while(++k < p->width)
				ft_add_buff_char(p, c);
			if (p->width == (int)ft_strlen(s) - 1)
				p->buff_index--;
			p->plus && nbr >= 0 && !p->zero ? ft_add_plus(p) : 0;
			ft_add_buff_str(p, s);
		}
	}
	else
	{
		p->plus && nbr >= 0 ? ft_add_plus(p) : 0;
		ft_add_buff_str(p, s);
	}
	free(s);
	return (1);
}