#ifndef ERRORS_H
# define ERROR_H

/* cd */
# define EACCES "cd: permission denied: "
# define ELOOP "cd: %s: too many levels of symbolic links"
# define ENAMETOOLONG "cd: file name too long: "
# define ENOENT "cd: no such file or directory: "
# define ENOTDIR "cd: not a directory: "

/* unset */
# define EINVAL "unset: %s: invalid parameter name"

/* export */
# define EXINVAL "export: %s: not a valid identifier"

/* exit */
# define NUMERIC_ARG ": numeric argument required\n"
# define MANY_ARG "exit: too many arguments\n"


#endif