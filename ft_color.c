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
//	p->str++;
	col[i] = '\0';
	if (strcmp(col, "red") == 0 || strcmp(col, "RED") == 0)///////////////////////
		ft_add_buff_str(p, RED);
	else if (strcmp(col, "green") == 0 || strcmp(col, "GREEN") == 0)///////////////////////
		ft_add_buff_str(p, GREEN);
	else if (strcmp(col, "yellow") == 0 || strcmp(col, "YELLOW") == 0)///////////////////////
		ft_add_buff_str(p, YELLOW);
	else if (strcmp(col, "blue") == 0 || strcmp(col, "BLUE") == 0)///////////////////////
		ft_add_buff_str(p, BLUE);
	else if (strcmp(col, "purple") == 0 || strcmp(col, "PURPLE") == 0)///////////////////////
		ft_add_buff_str(p, PURPLE);
	else if (strcmp(col, "cyan") == 0 || strcmp(col, "CYAN") == 0)///////////////////////
		ft_add_buff_str(p, CYAN);
	else if (strcmp(col, "eoc") == 0 || strcmp(col, "EOC") == 0)///////////////////////
		ft_add_buff_str(p, EOC);
	else
	{
		p->str = tmp;
		ft_add_buff_char(p, '{');
	}
	return (1);
}
