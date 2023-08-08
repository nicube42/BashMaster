#include "../../includes/bashmaster.h"

int	ft_cd(char **args)
{
    char	*path;

    if (args[1] == NULL)
        path = getenv("HOME");
    else if (args[2] != NULL)
    {
        ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
        return (1);
    }
    else
        path = args[1];
    if (chdir(path) == -1)
    {
        ft_putstr_fd("cd: ", STDERR_FILENO);
        perror(path);
        return (1);
    }
    return (0);
}