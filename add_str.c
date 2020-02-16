/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 21:12:12 by qmartina          #+#    #+#             */
/*   Updated: 2020/02/16 21:12:15 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_addstr(t_printf *p)
{
	char	*s;
	int		i;
	char	c;

	i = -1;
	s = ft_strdup(va_arg(p->li, char*));
	if (s == NULL)
		s = ft_strdup("(null)");
//	printf("point: %d\n", p->point);
	if ((p->accuracy > 0 || p->point == 1) && p->accuracy < (int)ft_strlen(s))
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
