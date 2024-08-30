/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:48:05 by rpandipe          #+#    #+#             */
/*   Updated: 2024/03/09 12:13:59 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
void	format_sorter(char c, va_list *ap, int *count, const char **format);
void	ft_putchar_count(char c, int *count);
void	ft_putstr_count(char *str, int *count);
void	ft_putnbr_count(int nbr, int *count);
void	ft_putnbr_u_count(unsigned int nbr, int *count);
void	ft_putnbr_base(unsigned int nbr, char *base, int *count);
void	ft_putmem_count(void *ptr, int *count);
void	ft_leftjust(va_list *ap, int *count, const char **format, char prev);
void	ft_zeropad(va_list *ap, int *count, const char **format, char flag);
void	ft_precision(va_list *ap, int *count, const char **format, char prev);
void	ft_printspaces(va_list *ap, int *count, const char **format);
int		get_width(const char **format);
char	*b_format_sorter(char c[2], va_list *ap, int *wc[2], \
						const char **format);
char	*ft_putchar_str(char c, int width);
char	*ft_putstr_str(char *str, int width);
char	*ft_putnbr_str(int nbr, int width);
char	*ft_putnbr_u_str(unsigned int nbr, int width);
void	ft_savebase(unsigned int size, char *b, unsigned long nbr, char *ans);
char	*ft_pb_str(unsigned int nbr, char *base, int width, char x);
char	*ft_putmem_str(void *ptr, int width);
size_t	int_counter(int n);
int		flag_sorter(char c[2], va_list *ap, const char **format);
char	*ft_u_itoa(unsigned int n);
int		check_negative(char *ans);
void	ft_plussign(va_list *ap, int *count, const char **format, char prev);
void	ft_hashsign(va_list *ap, int *count, const char **format, char prev);
char	*add_x(char *ans, int len, int width, char *base);
char	*padzeros(char *ans, int width, int len, char flag);
char	*p_str_special(char *p_ans, int width);
char	*deal_plus(char *ans, int width, const char *dup);
char	get_prev(char prev, const char *dup);
char	*add_plus(char *ans, int len, int width);
char	*add_space(char *ans, int len, int width);
int		get_prev_width(const char *format);
char	*deal_spcomb(char *ans, const char *dup, char c);
char	*deal_hscomb(char *ans, const char *dup, char c);
char	*deal_bonuscomb(char flag, char *ans, const char *dup, char prev);
#endif
