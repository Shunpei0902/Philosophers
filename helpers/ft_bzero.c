/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:15:23 by sasano            #+#    #+#             */
/*   Updated: 2024/09/30 23:07:12 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_bzero(void *dest, size_t n)
{
	while (n--)
		*(unsigned char *)dest++ = 0;
}

/* int	main(void)
{
	char	buf[20];

	strcpy(buf, "ABCDEFGHIJK");
	ft_bzero(buf + 5, 0);
	bzero(buf, 0);
	printf("%s\n", buf);
	return (0);
} */
