#include <ft_engine.h>


void	eng_print_light(char *str, t_light light)
{
	if (str)
		printf("%s\n", str);
	printf("origin:\n");
	print_t(1, light.origin);
	print_fcolor("color:\n", light.intensity);
}

//TODO: this only prints the lights right now
void	eng_print_world(t_world world)
{
	printf("****world*****\n");
	for (size_t i = 0; i < world.light_count; i++)
	{
		printf(" light %lu:\n", i);
		eng_print_light(0, world.lights[i]);
	}
	printf("****end world*****\n");
}
