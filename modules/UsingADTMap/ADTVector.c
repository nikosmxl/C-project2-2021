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
};

// Ενα Vector είναι pointer σε αυτό το struct
struct vector {
};


Vector vector_create(int size, DestroyFunc destroy_value) {
	return NULL;
}

int vector_size(Vector vec) {
	return 0;
}

Pointer vector_get_at(Vector vec, int pos) {
	return NULL;
}

void vector_set_at(Vector vec, int pos, Pointer value) {
}

void vector_insert_last(Vector vec, Pointer value) {
}

void vector_remove_last(Vector vec) {
}

Pointer vector_find(Vector vec, Pointer value, CompareFunc compare) {
	return NULL;
}

DestroyFunc vector_set_destroy_value(Vector vec, DestroyFunc destroy_value) {
	return NULL;
}

void vector_destroy(Vector vec) {
}


// Συναρτήσεις για διάσχιση μέσω node /////////////////////////////////////////////////////

VectorNode vector_first(Vector vec) {
	return NULL;
}

VectorNode vector_last(Vector vec) {
	return NULL;
}

VectorNode vector_next(Vector vec, VectorNode node) {
	return NULL;
}

VectorNode vector_previous(Vector vec, VectorNode node) {
	return NULL;
}

Pointer vector_node_value(Vector vec, VectorNode node) {
	return NULL;
}

VectorNode vector_find_node(Vector vec, Pointer value, CompareFunc compare) {
	return NULL;
}