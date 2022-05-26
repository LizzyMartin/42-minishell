/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:59:31 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/26 20:25:23 by acapela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<minishell.h>

/*
	validar se tem mais de um =
	pensar no caso: export FOO===BAR
	a key deverá ser FOO e o value ==BAR (somente o primeiro = é válido)
*/
void	ms_parse_env(t_ms *ms)
{
	ms->envs = NULL;
}
