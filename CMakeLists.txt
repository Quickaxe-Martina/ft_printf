cmake_minimum_required(VERSION 3.14)
project(ft_printf C)

set(CMAKE_C_STANDARD 99)

add_executable(ft_printf
        ft_printf.h
        libft/libft.h
        main.c
        ft_printf.c
        ft_color.c
        ft_add_c_s_d.c
        add_char.c
        add_str.c
        add_buff.c
        add_d.c
        ft_itoa_base_c.c
        ft_pointer.c
        ft_math.c)