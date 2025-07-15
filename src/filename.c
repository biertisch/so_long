/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:17:07 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/10 17:17:07 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	build_char_filename(char *dest, int idx)
{
	const char	*prefix;
	const char	*suffix;
	int			i;

	prefix = "textures/text/char_";
	suffix = ".xpm";
	i = 0;
	while (*prefix)
		dest[i++] = *prefix++;
	if (idx >= 10)
		dest[i++] = '0' + (idx / 10);
	dest[i++] = '0' + (idx % 10);
	while (*suffix)
		dest[i++] = *suffix++;
	dest[i] = '\0';
}

void	build_env_filename(char *dest, char *base, int frame)
{
	const char	*prefix;
	const char	*suffix;
	int			i;

	prefix = "textures/";
	suffix = ".xpm";
	i = 0;
	while (*prefix)
		dest[i++] = *prefix++;
	while (*base)
		dest[i++] = *base++;
	dest[i++] = '_';
	if (frame >= 10)
		dest[i++] = '0' + (frame / 10);
	dest[i++] = '0' + (frame % 10);
	while (*suffix)
		dest[i++] = *suffix++;
	dest[i] = '\0';
}

void	build_ent_filename(char *dest, char *base, int dir, int frame)
{
	char	*prefix;
	char	*extension;
	int		i;
	int		j;

	prefix = "textures/";
	extension = ".xpm";
	i = 0;
	while (*prefix)
		dest[i++] = *prefix++;
	while (*base)
		dest[i++] = *base++;
	dest[i++] = '_';
	dest[i++] = '0' + dir;
	dest[i++] = '_';
	dest[i++] = '0' + frame;
	j = 0;
	while (extension[j])
		dest[i++] = extension[j++];
	dest[i] = '\0';
}
