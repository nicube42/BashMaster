#include "../../bashmaster.h"

void execute_export(t_bash *sh, t_list *list)
{
    char **args = list->content;
    int i = 1;

    if (args[i] == NULL)
    {
        sort_environ(sh->envp);
        print_env(sh->envp);
        return;
    }
    while (args[i] != NULL)
    {
        if (ft_strchr(args[i], '=') != NULL)
            add_env(sh, args[i]);
        i++;
    }
}

void execute_unset(t_list *list)
{
    char **args = list->content;
    int i = 1;

    while (args[i] != NULL)
    {
        delete_env(args[i]);
        i++;
    }
}
