/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 02:53:55 by qmartina          #+#    #+#             */
/*   Updated: 2020/03/02 02:53:57 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "ft_printf.h"
#include <math.h>
#include <limits.h>

int	main(void)
{
	ft_printf("test:\n");
	printf("*TEST*%d***\n", ft_printf("{RED}%#08.3o{EOC}", 8375));
	ft_printf("\n");
	printf("orig:\n");
	printf("*ORIG*%d***\n", printf("{RED}%#08.3o{EOC}", 8375));
	return (6);
}
