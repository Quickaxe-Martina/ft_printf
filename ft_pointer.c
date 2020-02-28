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

int		ft_add_p(t_printf *p)
{
	void	*pointer;
	char	*s;
	char 	*tmp;
	int 	i;

	pointer = va_arg(p->li, void *);
	s = ft_itoa_base_c((uintmax_t)pointer, 16, -32);
	tmp = s;
	s = ft_strjoin("0x", tmp);
	free(tmp);
	i = -1;
	if (p->width > 0 && p->width > (int)ft_strlen(s))
	{
		if (p->minus == 1)
		{
			while(s[++i])
				ft_add_buff_char(p, s[i]);
			while(++i <= p->width)
				ft_add_buff_char(p, ' ');
		}
		else if (p->minus == 0)
		{
			while(++i < (p->width - (int)ft_strlen(s)))
				ft_add_buff_char(p, ' ');
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
