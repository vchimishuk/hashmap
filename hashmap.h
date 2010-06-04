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

#ifndef HASHMAP_H_
#define HASHMAP_H_

#define HASHMAP_THREAD_SAVE

#ifdef HASHMAP_THREAD_SAVE
#include <pthread.h>
#endif /* HASHMAP_THREAD_SAVE */


struct hashmap_item {
	char *key;
	void *value;
	struct hashmap_item *next;
};

struct hashmap {
	// Size of the table in slots.
	int size;
	// Pointer to the first slot.
	struct hashmap_item **table;
#	ifdef HASHMAP_THREAD_SAVE
	pthread_mutex_t mutex;
#	endif /* HASHMAP_THREAD_SAVE */
};

struct hashmap_iterator {
	struct hashmap *map;
	/* Index of active slot. */
	int index;
	/* Pointer to current item. */
	struct hashmap_item *item;
};

struct hashmap *hashmap_create(unsigned int size);
void hashmap_free(struct hashmap *map);
void hashmap_put(struct hashmap *map, const char *key, void *value);
void *hashmap_get(struct hashmap *map, const char *key);
void *hashmap_remove(struct hashmap *map, const char *key);
int hashmap_size(struct hashmap *map);
struct hashmap_iterator *hashmap_get_iterator(struct hashmap *map);
int hashmap_has_next(struct hashmap_iterator *iterator);
void *hashmap_get_next(struct hashmap_iterator *iterator);

#endif /* HASHMAP_H_ */
