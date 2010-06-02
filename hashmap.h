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
};

struct hashmap *hashmap_create(unsigned int size);
void hashmap_free(struct hashmap *map);
void hashmap_put(struct hashmap *map, const char *key, void *value);
void *hashmap_get(struct hashmap *map, char *key);
void *hashmap_remove(char *key);
int hashmap_size(struct hashmap *map);

#endif /* HASHMAP_H_ */
