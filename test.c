#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
    int i = 0;
    char *args[] = {"ls", "-la", NULL};
    execve("/usr/bin/ls", args, envp);
}
