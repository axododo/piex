#include "pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s) - start;
	if (size > len)
		size = len;
	if (start >= ft_strlen(s))
	{
		dest = malloc(sizeof(char));
		if (!dest)
			return (0);
		dest[0] = 0;
		return (dest);
	}
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (0);
	ft_strlcpy(dest, &s[start], (size + 1));
	return (dest);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;
	size_t	size2;

	size2 = size;
	len = 0;
	i = 0;
	while (src[len])
	{
		len++;
	}
	if (size == 0)
	{
		return (len);
	}
	while (src[i] && i < size2 - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

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

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	s3 = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s3)
		return (NULL);
	while (s1[i])
	{
		s3[i] = s1[j];
		i++;
		j++;
	}
  s3[i] = '/';
  i++;
	j = 0;
	while (s2[j])
	{
		s3[i + j] = s2[j];
		j++;
	}
	s3[i + j] = '\0';
	return (s3);
}
