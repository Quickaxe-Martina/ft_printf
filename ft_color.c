#include "ft_printf.h"

int 	ft_color(t_printf *p)
{
	int		i;
	char 	col[8];
	char 	*tmp;

	i = 0;
	tmp = p->str;
	p->str++;
	while (*p->str && *p->str != '}' && i < 7)
	{
		col[i] = *p->str;
		i++;
		p->str++;
	}
	p->str++;
	col[i] = '\0';
	if (strcmp(col, "red") == 0 || strcmp(col, "RED") == 0)///////////////////////
		printf("ITS RED\n");
	else if (strcmp(col, "green") == 0 || strcmp(col, "GREEN") == 0)///////////////////////
		printf("ITS GREEN\n");
	else if (strcmp(col, "yellow") == 0 || strcmp(col, "YELLOW") == 0)///////////////////////
		printf("ITS YELLOW\n");
	else if (strcmp(col, "blue") == 0 || strcmp(col, "BLUE") == 0)///////////////////////
		printf("ITS BLUE\n");
	else if (strcmp(col, "purple") == 0 || strcmp(col, "PURPLE") == 0)///////////////////////
		printf("ITS PURPLE\n");
	else if (strcmp(col, "cyan") == 0 || strcmp(col, "CYAN") == 0)///////////////////////
		printf("ITS CYAN\n");
	else if (strcmp(col, "eoc") == 0 || strcmp(col, "EOC") == 0)///////////////////////
		printf("ITS END OF COLOR\n");
	else
	{
		p->str = tmp;
		ft_add_buff_char(p, '{');
	}
	return (1);
}
