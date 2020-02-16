#include "frmk_libunit.h"
#include "tests.h"
#include "ft_printf.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>

# define ARGS "%-+8.14G|%- 8.14G|%-#8.14G|%-08.14G|%-+#8.14G|%-+ #08.14G", -INFINITY, -INFINITY, -INFINITY, -INFINITY, -INFINITY, -INFINITY

int		conv_cap_g_minus_infinity_various_flags_combined_with_minus(void)
{
	t_test_rslt	test_rslt;
	int			pfd[2];
	int			nbytes_read;
	int			ret_value;
	int			save_out;
	int			err;
	int			fd_trace;

	test_rslt = (t_test_rslt){NULL, NULL, 0, 0};
	fd_trace = get_fd(TRACE_FILE, OUTPUT_MODE, OP_APPEND);
	if ((err = pipe_stdout(pfd, &save_out)))
		return (free_result(&test_rslt, err));
	test_rslt.ref_ret = printf(ARGS);
	if ((err = read_pipe(&test_rslt.ref_str, &nbytes_read, pfd, &save_out)))
		return (free_result(&test_rslt, err));
	if ((err = pipe_stdout(pfd, &save_out)))
		return (free_result(&test_rslt, err));
	test_rslt.user_ret = ft_printf(ARGS);
	if ((err = read_pipe(&test_rslt.user_str, &nbytes_read, pfd, &save_out)))
		return (free_result(&test_rslt, err));
	if ((test_rslt.user_ret != test_rslt.ref_ret)
			|| memcmp(test_rslt.user_str, test_rslt.ref_str, test_rslt.ref_ret))
	{
		print_test_result_values_trace(&test_rslt, fd_trace);
		ret_value = -1;
	}
	else
	{
		print_test_result_values_trace(&test_rslt, fd_trace);
		ret_value = 0;
	}
	return (free_result(&test_rslt, ret_value));
}
