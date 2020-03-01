/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:51:43 by qmartina          #+#    #+#             */
/*   Updated: 2020/02/28 06:51:45 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		width_point(t_printf *p, char *s, int i)
{
	if (p->width > 0 && p->width > (int)ft_strlen(s))
	{
		if (p->minus == 1)
		{
			while (s[++i])
				ft_add_buff_char(p, s[i]);
			while (++i <= p->width)
				ft_add_buff_char(p, ' ');
		}
		else if (p->minus == 0)
		{
			while (++i < (p->width - (int)ft_strlen(s)))
				ft_add_buff_char(p, ' ');
			i = -1;
			while (s[++i])
				ft_add_buff_char(p, s[i]);
		}
	}
	else
	{
		while (s[++i])
			ft_add_buff_char(p, s[i]);
	}
}

void		accur_point(t_printf *p, char **s, int i)
{
	char 	*tmp;

//	printf("\n\naccur: %d\nstr: %s\n\n", p->accuracy, *s);
	if (p->accuracy > 0 && p->accuracy > (int)ft_strlen(*s))
	{
		p->accuracy -= (int)ft_strlen(*s);
		while (++i < (p->accuracy))
		{
			tmp = *s;
			*s = ft_strjoin("0", tmp);
			free(tmp);
		}
	}
//	printf("\n\naccur: %d\nstr: %s\n\n", p->accuracy, *s);
	tmp = *s;
	*s = ft_strjoin(DEC, tmp);
	free(tmp);
}

int			ft_add_p(t_printf *p)
{
	void	*pointer;
	char	*s;
//	char	*tmp;
//	int     i;

	pointer = va_arg(p->li, void *);
	s = ft_itoa_base_c((uintmax_t)pointer, 16, -32);
	if ((p->accuracy == 0 || (p->accuracy == -1 && p->point == 1)))
		s[0] = '\0';
	accur_point(p, &s, -1);
//	tmp = s;
//	s = ft_strjoin("0x", tmp);
//	free(tmp);
	width_point(p, s, -1);
//	if ((uintmax_t)pointer == 0 && p->point == 1 && p->accuracy > 0)
//    {
//		i = 0;
//		while (++i < p->accuracy)
//			ft_add_buff_char(p, '0');
//    }
	free(s);
	return (1);
}
