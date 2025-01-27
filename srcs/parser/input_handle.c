#include "../cube.h"

int	input_handle(int argc, char **argv)
{
	if (argc != 2)
		return(call_error());
	if (check_file_name(argv[1]) < 0)
		return(bad_map_file());
}