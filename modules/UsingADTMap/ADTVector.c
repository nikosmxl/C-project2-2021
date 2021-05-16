///////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT Vector μέσω ADT Map.
//
///////////////////////////////////////////////////////////

#include <stdlib.h>
#include <assert.h>

#include "ADTVector.h"
#include "ADTMap.h"


// Ένα VectorNode είναι pointer σε αυτό το struct.
struct vector_node {
	MapNode nodemap;
};

// Ενα Vector είναι pointer σε αυτό το struct
struct vector {
	Map vecmap;
	DestroyFunc destroy_func;
};

int* create_int(int value) {
    int* pointer = malloc(sizeof(int));			// δέσμευση μνήμης     
	*pointer = value;							// αντιγραφή του value στον νέο ακέραιο
	return pointer;
}

static int compare_ints(Pointer a, Pointer b){
	return *(int*)a - *(int*)b;
}

Vector vector_create(int size, DestroyFunc destroy_value) {
	assert(size >= 0);
	Vector vec = malloc(sizeof(*vec));
	vec->destroy_func = destroy_value;
	vec->vecmap = map_create(compare_ints, free, vec->destroy_func);

	if (size != 0){
		for (int i = 0 ; i < size ; i++){
			int* cr_int = create_int(i);
			map_insert(vec->vecmap, cr_int, NULL);
		}
	}
	return vec;
}

int vector_size(Vector vec) {
	return map_size(vec->vecmap);
}

Pointer vector_get_at(Vector vec, int pos) {
	int* p = create_int(pos);
	Pointer val = map_find(vec->vecmap, p);
	free(p);
	return val;
}

void vector_set_at(Vector vec, int pos, Pointer value) {
	map_insert(vec->vecmap, create_int(pos), value);
}

void vector_insert_last(Vector vec, Pointer value) {
	map_insert(vec->vecmap, create_int(map_size(vec->vecmap)), value);
}

void vector_remove_last(Vector vec) {
	assert(map_size(vec->vecmap) != 0);

	int* p = create_int(map_size(vec->vecmap) - 1);
	map_remove(vec->vecmap, p);
	free(p);
}

Pointer vector_find(Vector vec, Pointer value, CompareFunc compare) {
	VectorNode node = vector_find_node(vec, value, compare);
	if (node != VECTOR_EOF){
		return map_node_value(vec->vecmap, (MapNode)node);
	}
	return NULL;
}

DestroyFunc vector_set_destroy_value(Vector vec, DestroyFunc destroy_value) {
	vec->destroy_func = destroy_value;
	return map_set_destroy_value(vec->vecmap, destroy_value);
}

void vector_destroy(Vector vec) {
	map_set_destroy_value(vec->vecmap, vec->destroy_func);
	map_destroy(vec->vecmap);

	free(vec);
}


// Συναρτήσεις για διάσχιση μέσω node /////////////////////////////////////////////////////

VectorNode vector_first(Vector vec) {
	return ((VectorNode)(map_first(vec->vecmap)));
}

VectorNode vector_last(Vector vec) {
	int* p = create_int(map_size(vec->vecmap) - 1);
	MapNode last = map_find_node(vec->vecmap, p);
	free(p);
	return (VectorNode)last;
}

VectorNode vector_next(Vector vec, VectorNode node) {
	return ((VectorNode)(map_next(vec->vecmap, (MapNode)node)));
}

VectorNode vector_previous(Vector vec, VectorNode node) {
	int* i = map_node_key(vec->vecmap, (MapNode)node);
	int* j = create_int(*i - 1);
	VectorNode found = ((VectorNode)(map_find_node(vec->vecmap, j)));
	free(j);
	return found;
}

Pointer vector_node_value(Vector vec, VectorNode node) {
	return map_node_value(vec->vecmap, (MapNode)node);
}

VectorNode vector_find_node(Vector vec, Pointer value, CompareFunc compare) {
	if (map_first(vec->vecmap) == MAP_EOF){
		return NULL;
	}
	for (MapNode node = map_first(vec->vecmap) ; node != MAP_EOF ; node = map_next(vec->vecmap, node)){
		Pointer found = map_node_value(vec->vecmap, node);
		if (compare(found, value) == 0){
			return (VectorNode)node;
		}
	}
	return VECTOR_EOF;
}