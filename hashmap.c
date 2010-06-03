/*
 * This file is part of hashmap library.
 *
 * This is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Foobar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "hashmap.h"

#define HASHMAP_DEFAULT_SIZE 128


/*
 * Returns hash for the given key.
 */
static unsigned int hash_function(const char *key, int size)
{
	int i;
	unsigned int h = 0;
	int key_len = strlen(key);

	for (i = 0; i < key_len; i++) {
		h = 31 * h + key[i];
	}

	return h % size;
}

/*
 * Create new hashmap.
 * Size is the size of the number of map slots. Leave it 0
 * if you want to use a default value.
 */
struct hashmap *hashmap_create(unsigned int size)
{
	struct hashmap *map;

	if (size == 0)
			size = HASHMAP_DEFAULT_SIZE;

	map = (struct hashmap *) malloc(sizeof(struct hashmap));
	if (map == NULL)
		return NULL;

	int table_size = sizeof(struct hashmap_item *) * size;

	map->size = size;
	map->table = (struct hashmap_item **) malloc(table_size);
	if (map->table == NULL) {
		free(map);
		return NULL;
	}
	bzero(map->table, table_size);

	return map;
}

/*
 * Destroy hashmap.
 */
void hashmap_free(struct hashmap *map)
{
	struct hashmap_item *p, *q;
	int i;

	for (i = 0; i < map->size; i++) {
		p = map->table[i];

		while (p) {
			q = p;
			p = p->next;
			free(q->key);
			free(q);
		}
	}

	free(map->table);
	free(map);
}

/*
 * Add value to the  map.
 * If value assigned to the given key already exist it will be replaced with
 * new value.
 */
void hashmap_put(struct hashmap *map, const char *key, void *value)
{
	unsigned int index;
	struct hashmap_item *new_item;

	if (key == NULL)
		return;

	new_item = (struct hashmap_item *) malloc(sizeof(struct hashmap_item));
	new_item->key = strdup(key);
	new_item->value = value;
	new_item->next = NULL;

	index = hash_function(key, map->size);

	if (map->table[index] == NULL) {
		map->table[index] = new_item;
	} else {
		struct hashmap_item *p = map->table[index];

		do {
			if (strcmp(p->key, key) == 0) {
				p->value = value;
				return;
			}
		} while(p->next && (p = p->next));

		p->next = new_item;
	}
}

/*
 * Returns value from map by its key, or NULL if value assigned to this key
 * not found.
 */
void *hashmap_get(struct hashmap *map, char *key)
{
	unsigned int index;
	struct hashmap_item *p;

	if (key == NULL)
		return NULL;

	index = hash_function(key, map->size);
	p = map->table[index];

	// Value was not setted.
	if (p == NULL)
		return NULL;

	do {
		if (strcmp(p->key, key) == 0)
			return p->value;
	} while ((p = p->next) != NULL);

	return NULL;
}

/*
 * Remove key assigned value from the map.
 * Returns value assigned for the deleted key.
 */
void *hashmap_remove(char *key)
{
	// TODO: Implement.

	return NULL;
}

/*
 * Returns number of elements presented in the map.
 */
int hashmap_size(struct hashmap *map)
{
	int i;
	int size = 0;
	struct hashmap_item *p;

	for (i = 0; i < map->size; i++) {
		p = map->table[i];

		while (p) {
			size++;
			p = p->next;
		}
	}

	return size;
}
