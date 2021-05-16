///////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT Deque μέσω ADT Map.
//
///////////////////////////////////////////////////////////


#include <stdlib.h>
#include <assert.h>

#include "ADTDeque.h"
#include "ADTMap.h"

struct deque {
	Map deqmap;
	DestroyFunc destroy_func;
    int start;
};

int* create_int(int value) {
    int* pointer = malloc(sizeof(int));			// δέσμευση μνήμης     
	*pointer = value;							// αντιγραφή του value στον νέο ακέραιο
	return pointer;
}

static int compare_ints(Pointer a, Pointer b){
	return *(int*)a - *(int*)b;
}

Deque deque_create(int size, DestroyFunc destroy_value){
    assert(size >= 0);
    Deque deque = malloc(sizeof(*deque));
    deque->destroy_func = destroy_value;
    deque->start = 0;

    deque->deqmap = map_create(compare_ints, free, deque->destroy_func);

    if (size != 0){
		for (int i = 0 ; i < size ; i++){
			int* cr_int = create_int(i);
			map_insert(deque->deqmap, cr_int, NULL);
		}
	}
	return deque;
}

int deque_size(Deque deque){
    return map_size(deque->deqmap);
}

void deque_insert_first(Deque deque, Pointer value){
    deque->start++;
    int* p = create_int(-deque->start);
    map_insert(deque->deqmap, p, value);
}

void deque_insert_last(Deque deque, Pointer value){
    int* p = create_int(map_size(deque->deqmap) - deque->start);
	map_insert(deque->deqmap, p, value);
}

void deque_remove_first(Deque deque){
    int* p = create_int(-deque->start);
	map_remove(deque->deqmap, p);
	free(p);
    deque->start--;
}

void deque_remove_last(Deque deque){
    int* p = create_int(map_size(deque->deqmap) - 1 - deque->start);
	map_remove(deque->deqmap, p);
	free(p);
}

Pointer deque_get_at(Deque deque, int pos){
    int* p = create_int(pos - deque->start);
	Pointer val = map_find(deque->deqmap, p);
	free(p);
	return val;
}


void deque_set_at(Deque deque, int pos, Pointer value){
    int* p = create_int(pos - deque->start);
	map_insert(deque->deqmap, p, value);
}


Pointer deque_find(Deque deque, Pointer value, CompareFunc compare){
    DequeNode node = deque_find_node(deque, value, compare);
	if (node != DEQUE_EOF){
		return map_node_value(deque->deqmap, (MapNode)node);
	}
	return NULL;
}

DestroyFunc deque_set_destroy_value(Deque deque, DestroyFunc destroy_value){
    deque->destroy_func = destroy_value;
	return map_set_destroy_value(deque->deqmap, destroy_value);
}

void deque_destroy(Deque deque){
    map_set_destroy_value(deque->deqmap, deque->destroy_func);
	map_destroy(deque->deqmap);
	free(deque);
}

DequeNode deque_first(Deque deque){
    return ((DequeNode)(map_first(deque->deqmap)));
}

DequeNode deque_last(Deque deque){
    int* p = create_int(map_size(deque->deqmap) - 1 - deque->start);
	MapNode last = map_find_node(deque->deqmap, p);
	free(p);
	return (DequeNode)last;
}

DequeNode deque_next(Deque deque, DequeNode node){
    return ((DequeNode)(map_next(deque->deqmap, (MapNode)node)));
}

DequeNode deque_previous(Deque deque, DequeNode node){
    int* i = map_node_key(deque->deqmap, (MapNode)node);
	int* j = create_int(*i - 1 - deque->start);
	DequeNode found = ((DequeNode)(map_find_node(deque->deqmap, j)));
	free(j);
	return found;
}

Pointer deque_node_value(Deque deque, DequeNode node){
    return map_node_value(deque->deqmap, (MapNode)node);
}

DequeNode deque_find_node(Deque deque, Pointer value, CompareFunc compare){
    if (map_first(deque->deqmap) == MAP_EOF){
		return NULL;
	}
	for (MapNode node = map_first(deque->deqmap) ; node != MAP_EOF ; node = map_next(deque->deqmap, node)){
		Pointer found = map_node_value(deque->deqmap, node);
		if (compare(found, value) == 0){
			return (DequeNode)node;
		}
	}
	return DEQUE_EOF;
}
