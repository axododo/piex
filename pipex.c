
#include "pipex.h"


int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;
	int				x;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	x = 0;
	while ((str1[i] && str2[i] && (str1[i] == str2[i])) && i < n)
	{
		i++;
	}
	if (i == n)
		return (0);
	x = str1[i] - str2[i];
	return (x);
}

char *find_path(char **envp) {
    t_pip util;
    int i = 0;
    while (envp[i]) {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
            util.splited = ft_split(envp[i] + 5, ":");
            return(util.splited);
        i++;
    }
    return (NULL);
}



int verif(int err, char *msg) {
    if (err == -1){
        perror(msg);
        exit(1);
    }
      return(err);
}


int main( int argc, char *argv[], char **envp) {
    t_pip util;

    if (argc != 5) {
        write(2, "bad nb arg", 11);
        return(1);
    }
    util.fd_in = open(argv[1], O_RDONLY);
    util.fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    verif(util.fd_in, "input file");
    verif(util.fd_out, "output file");
    util.splited = find_path(envp);
    printf("%s\n", util.splited);
}
