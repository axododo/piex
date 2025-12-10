#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
    int i = 0;

    printf("Variables d'environnement:\n");
    while (envp[i] != NULL)  // Parcours jusqu'à NULL
    {
        printf("%s\n", envp[i]);
        i++;
    }
    return (0);
}
