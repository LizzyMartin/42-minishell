/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argel <argel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:06:31 by acapela-          #+#    #+#             */
/*   Updated: 2022/05/27 07:33:19 by argel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

/* all */
# define E_CMDNOTFOUND ": command not found\n"
# define E_BADSINTAX ": syntax error near unexpected token "
# define E_NOTDIR ": No such file or directory\n"

/* cd */
# define EACCES "cd: permission denied\n"
# define ELOOP "cd: %s: too many levels of symbolic links\n"
# define ENAMETOOLONG "cd: file name too long\n"
# define ENOENT "cd: no such file or directory\n"
# define ENOTDIR "cd: not a directory\n"

/* unset */
# define EINVAL "unset: %s: invalid parameter name"

/* export */
# define EXINVAL "export: %s: not a valid identifier"

/* exit */
# define NUMERIC_ARG ": numeric argument required\n"
# define MANY_ARG "exit: too many arguments\n"

#endif