#include <tools.h>
#include <stdlib.h>
#include <unistd.h>

void	*safe_malloc(size_t size)
{
	const char	error[] = "Malloc error\n";
	void		*ret;

	if (!(ret = malloc(size)))
	{
		write(2, error, sizeof(error) - 1);
		exit(1);
	}
	return (ret);
}