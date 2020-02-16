/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_whtsp_start.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 18:12:48 by mbrella           #+#    #+#             */
/*   Updated: 2019/09/11 18:12:49 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_count_whtsp_start(char const *s)
{
	unsigned int cn;

	cn = 0;
	while ((*s == '\t' || *s == '\n' || *s == ' ') && *s)
	{
		cn++;
		s++;
	}
	return (cn);
}