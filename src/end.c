/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:10:30 by beatde-a          #+#    #+#             */
/*   Updated: 2025/07/09 11:10:30 by beatde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	victory(t_data *data)
{
	ft_printf("You won the game. So long!\n");
	close_game((void *)data);
}

int	close_game(void *param)
{
	free_data((t_data *)param);
	exit(0);
	return (0);
}

void	error_exit(t_data *data, char *error_msg)
{
	if (data)
		free_data(data);
	if (error_msg)
		ft_putstr_fd(error_msg, 2);
	exit(1);
}
