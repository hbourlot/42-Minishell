/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:40:28 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/21 13:54:40 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_pattern_done(const char *pattern, int p)
{
	while (pattern[p] == '*')
		p++;
	return (pattern[p] == '\0');
}

static int	match_wd_aux(const char *pattern, const char *filename, int p,
		int f)
{
	int	sm_pos[2];

	ft_memset(sm_pos, -1, 8);
	while (filename[f])
	{
		if (pattern[p] == filename[f])
		{
			p++;
			f++;
		}
		else if (pattern[p] == '*')
		{
			sm_pos[0] = p++;
			sm_pos[1] = f;
		}
		else if (sm_pos[0] != -1)
		{
			p = sm_pos[0] + 1;
			f = ++sm_pos[1];
		}
		else
			return (0);
	}
	return (is_pattern_done(pattern, p));
}

int	match_wildcard(const char *pattern, const char *filename)
{
	int	p;
	int	f;

	p = 0;
	f = 0;
	if (match_wd_aux(pattern, filename, p, f))
		return (1);
	return (0);
}
