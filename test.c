#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"


void hashmap_dump(struct hashmap *map)
{
	struct hashmap_item *p;
	int i;

	for (i = 0; i < map->size; i++) {
		p = map->table[i];

		printf("%4d:", i);

		for (; p != NULL; p = p->next) {
			printf(" \"%s\"", p->key);
		}

		printf("\n");
	}
}

void my_assert(int cond)
{
	if (!cond) {
		printf("Test failed!");

		exit(EXIT_FAILURE);
	}
}

int main()
{
	struct hashmap *map;

	map = (struct hashmap *) hashmap_create(16);

	hashmap_put(map, "one", (void *) 1);
	hashmap_put(map, "two", (void *) 2);
	hashmap_put(map, "three", (void *) 3);
	hashmap_put(map, "four", (void *) 4);
	hashmap_put(map, "five", (void *) 5);
	hashmap_put(map, "six", (void *) 6);
	hashmap_put(map, "seven", (void *) 7);
	hashmap_put(map, "eight", (void *) 8);
	hashmap_put(map, "nine", (void *) 9);
	hashmap_put(map, "ten", (void *) 10);

	/* hashmap_dump(map); */

	my_assert(4 == (long) hashmap_get(map, "four"));
	my_assert(4 == (long) hashmap_remove(map, "four"));
	my_assert(NULL == hashmap_get(map, "four"));

	/* hashmap_dump(map); */

	my_assert(9 == hashmap_size(map));

	printf("Tests passed!\n");

	return EXIT_SUCCESS;
}
