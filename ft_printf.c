/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 23:28:12 by qmartina          #+#    #+#             */
/*   Updated: 2020/03/01 23:28:17 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			cheak_zvezd(t_printf *p)
{
	if (*p->str == '*')
	{
		p->accuracy = -4242;
		p->str++;
	}
}

void			init_printf(t_printf *p, const char *format)
{
	p->fd = 1;
	p->buff_size = 64;
	if (!(p->buff = ft_strnew(p->buff_size)))
		exit(1);
	p->buff_index = 0;
	p->str = (char *)format;
}

int				return_print(t_printf *p)
{
	write(p->fd, p->buff, p->buff_index);
	free(p->buff);
	return (p->buff_index);
}

int				ft_printf(const char *format, ...)
{
	t_printf	p;
	char		*s;

	init_printf(&p, format);
	s = NULL;
	va_start(p.li, format);
	while (*p.str)
	{
		if (*p.str == '%')
		{
			if (*(++p.str) == '\0')
				break ;
			s = p.str;
			if (ft_parser(&p) == -1)
			{
				p.str = s;
				ft_add_buff(&p);
			}
		}
		else
			ft_add_buff(&p);
		p.str++;
	}
	va_end(p.li);
	return (return_print(&p));
}
