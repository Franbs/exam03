/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:23:39 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/12/05 16:51:43 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>

int match_space(FILE *f)
{
    int c;
    int skipped = 0;

    c = fgetc(f);
    while (c != EOF && isspace(c))
    {
        skipped = 1;
        c = fgetc(f);
    }
    ungetc(c, f); 
    if (c == EOF && skipped == 0)
        return (-1);
    return (1); 
}

int match_char(FILE *f, char c)
{
    int read_char = fgetc(f);

    if (read_char == EOF)
        return (-1);
    if (read_char == c)
        return (1);
    else
    {
        ungetc(read_char, f);
        return (0);
    }
}

int scan_char(FILE *f, va_list ap)
{
    char *target = va_arg(ap, char *);

    int c = fgetc(f);
    
    if (c == EOF)
        return (0);
    
    *target = (char)c;
    return (1);
}

int scan_int(FILE *f, va_list ap)
{
    int *target = va_arg(ap, int *);
    long num = 0;
    int sign = 1;
    int c;
    int digits_read = 0;

    c = fgetc(f);
    if (c == '-')
    {
        sign = -1;
        c = fgetc(f);
    }
    else if (c == '+')
    {
        c = fgetc(f);
    }
    while (c >= '0' && c <= '9')
    {
        num = num * 10 + (c - '0');
        digits_read++;
        c = fgetc(f);
    }
    if (c != EOF)
        ungetc(c, f);
    if (digits_read == 0)
        return (0);
    *target = (int)(num * sign); 
    return (1);
}

int scan_string(FILE *f, va_list ap)
{
    char *target = va_arg(ap, char *);
    int c;
    int i = 0;
    
    c = fgetc(f);
    while (c != EOF && !isspace(c))
    {
        target[i++] = (char)c;
        c = fgetc(f);
    }
    if (c != EOF)
        ungetc(c, f); 
    if (i == 0)
    {
        return (0);
    }
    target[i] = '\0';
    return (1);
}

int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
            (*format)++;
			return scan_char(f, ap);
		case 'd':
            (*format)++;
			return scan_int(f, ap);
		case 's':
            (*format)++;
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return 0; 
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;
	int ret_val;
	int c = fgetc(f);

	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			ret_val = match_conv(f, &format, ap);
			if (ret_val == 1)
				nconv++;
			else if (ret_val == 0)
				break ;
			else
				return (EOF);
		}
		else if (isspace(*format))
		{
			ret_val = match_space(f);
            if (ret_val == -1)
				return (EOF);
		}
		else 
		{
			ret_val = match_char(f, *format);
			if (ret_val != 1)
				break ;
		}
		format++;
	}
	if (ferror(f))
		return EOF;
	return (nconv);
}

int ft_scanf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}
