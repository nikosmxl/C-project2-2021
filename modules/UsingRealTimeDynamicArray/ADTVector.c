///////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT Vector μέσω Dynamic Array.
//
///////////////////////////////////////////////////////////

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "ADTVector.h"


// Το αρχικό μέγεθος που δεσμεύουμε
#define VECTOR_MIN_CAPACITY 10

// Ένα VectorNode είναι pointer σε αυτό το struct. (το struct περιέχει μόνο ένα στοιχείο, οπότε θα μπροούσαμε και να το αποφύγουμε, αλλά κάνει τον κώδικα απλούστερο)
struct vector_node {
	Pointer value;				// Η τιμή του κόμβου.
};

// Ενα Vector είναι pointer σε αυτό το struct
struct vector {
	VectorNode array;			// Τα δεδομένα, πίνακας από struct vector_node
    VectorNode array2;
	int size;					// Πόσα στοιχεία έχουμε προσθέσει
	int capacity;				// Πόσο χώρο έχουμε δεσμεύσει (το μέγεθος του array). Πάντα capacity >= size, αλλά μπορεί να έχουμε
	DestroyFunc destroy_value;	// Συνάρτηση που καταστρέφει ένα στοιχείο του vector.
    int start;
    int size2;
    int capacity2;
};


Vector vector_create(int size, DestroyFunc destroy_value) {
	// Δημιουργία του struct
	Vector vec = malloc(sizeof(*vec));
    
	vec->size2 = size;
	vec->destroy_value = destroy_value;

	// Δέσμευση μνήμης για τον πίνακα. Αρχικά το vector περιέχει size
	// μη-αρχικοποιημένα στοιχεία, αλλά εμείς δεσμεύουμε xώρο για τουλάχιστον
	// VECTOR_MIN_CAPACITY για να αποφύγουμε τα πολλαπλά resizes.
	//
	vec->capacity2 = size < VECTOR_MIN_CAPACITY ? VECTOR_MIN_CAPACITY : size;
	vec->start = vec->capacity2;
	vec->array2 = calloc(vec->capacity2, sizeof(*vec->array2));		// αρχικοποίηση σε 0 (NULL)
	vec->array = NULL;
	vec->capacity = vec->capacity2 / 2 + vec->capacity2 % 2;
	vec->start = vec->capacity2;
	vec->size = 0;
	return vec;
}

int vector_size(Vector vec) {
	return vec->size + vec->size2;
}

Pointer vector_get_at(Vector vec, int pos) {
	assert(pos >= 0 && pos < vec->size + vec->size2);	// LCOV_EXCL_LINE (αγνοούμε το branch από τα coverage reports, είναι δύσκολο να τεστάρουμε το false γιατί θα κρασάρει το test)

	if (pos >= vec->start && pos < vec->capacity && vec->array != NULL){
		return vec->array[pos].value;
	}
	else{
		return vec->array2[pos].value;
	}
	
}

void vector_set_at(Vector vec, int pos, Pointer value) {
	assert(pos >= 0 && pos < vec->size + vec->size2);	// LCOV_EXCL_LINE

	if (pos >= vec->start && pos < vec->capacity && vec->array != NULL){
		if (value != vec->array[pos].value && vec->destroy_value != NULL)
			vec->destroy_value(vec->array[pos].value);

		vec->array[pos].value = value;
	}
	else{
		if (value != vec->array2[pos].value && vec->destroy_value != NULL)
			vec->destroy_value(vec->array2[pos].value);

		vec->array2[pos].value = value;
	}

}

void vector_insert_last(Vector vec, Pointer value) {
	// Μεγαλώνουμε τον πίνακα (αν χρειαστεί), ώστε να χωράει τουλάχιστον size στοιχεία
	// Διπλασιάζουμε κάθε φορά το capacity (σημαντικό για την πολυπλοκότητα!)

    if (vec->size2 == vec->capacity2){
		if (vec->array != NULL){
			free(vec->array);
		}
        vec->array = vec->array2;
        vec->size = vec->size2;
        vec->capacity = vec->capacity2;
        vec->size2 = 0;
        vec->capacity2 = 2*vec->capacity;
        vec->start = 0;
    }

	if (vec->capacity == vec->size + vec->start) {
		if (vec->capacity == vec->size){
			vec->array2 = calloc(vec->capacity2, sizeof(*vec->array2));
		}
		vec->array2[vec->capacity + vec->start].value = value;
		vec->array2[vec->start].value = vec->array[vec->start].value;
        vec->start++;
        vec->size2 += 2;
        vec->size--;
        return;
	}
	

	// Μεγαλώνουμε τον πίνακα και προσθέτουμε το στοιχείο
	vec->array2[vec->size2].value = value;
	vec->size2++;
	
}

void vector_remove_last(Vector vec) {
	assert(vec->size + vec->size2 != 0);		// LCOV_EXCL_LINE

	// Αν υπάρχει συνάρτηση destroy_value, την καλούμε για το στοιχείο που αφαιρείται
	if (vec->size2 == 0){
		free(vec->array2);
		vec->array2 = vec->array;
		vec->capacity2 = vec->capacity2 / 2 + vec->capacity2 % 2;
		vec->capacity = vec->capacity2 / 2 - vec->capacity2 % 2;
		vec->size2 = vec->size;
		vec->size = 0;
		vec->start = vec->capacity;
		if (vec->capacity > VECTOR_MIN_CAPACITY){
			vec->array = calloc(vec->capacity, sizeof(*vec->array));
		}
		else{
			vec->array = NULL;
		}
	}

	if (vec->size2 == 1){
		if (vec->array != NULL){
			vec->start--;
			vec->array[vec->start].value = vec->array2[vec->start].value;
		}
		vec->size2--;
		return;
	}

	if (vec->destroy_value != NULL){
		vec->destroy_value(vec->array2[vec->size2 + vec->size - 1].value);
	}
	
	if (vec->array == NULL && vec->capacity > VECTOR_MIN_CAPACITY){
		vec->array = calloc(vec->capacity, sizeof(*vec->array));
		vec->start = vec->capacity;
	}

	if (vec->array != NULL){
		vec->start--;
		vec->array[vec->start].value = vec->array2[vec->start].value;
		vec->size++;
		vec->size2 -= 2;
		return;
	}
	vec->size2--;
	
}

Pointer vector_find(Vector vec, Pointer value, CompareFunc compare) {
	VectorNode node = vector_find_node(vec, value, compare);

	if (node == VECTOR_EOF){
		return NULL;
	}
	return vector_node_value(vec, node);
}

DestroyFunc vector_set_destroy_value(Vector vec, DestroyFunc destroy_value) {
	DestroyFunc old = vec->destroy_value;
	vec->destroy_value = destroy_value;
	return old;
}

void vector_destroy(Vector vec) {
	// Αν υπάρχει συνάρτηση destroy_value, την καλούμε για όλα τα στοιχεία
	if (vec->destroy_value != NULL)
		for (int i = 0; i < vec->size + vec->size2; i++){
			if (i >= vec->start && i < vec->capacity && vec->array != NULL){
				vec->destroy_value(vec->array[i].value);
			}
			else{
				vec->destroy_value(vec->array2[i].value);
			}
		}
			

	// Πρέπει να κάνουμε free τόσο τον πίνακα όσο και το struct!
	free(vec->array);
	free(vec->array2);
	free(vec);			// τελευταίο το vec!
}


// Συναρτήσεις για διάσχιση μέσω node /////////////////////////////////////////////////////

VectorNode vector_first(Vector vec) {
	if (vec->size == 0)
		return VECTOR_BOF;
	else{
		if (vec->start > 0){
			return &vec->array2[0];
		}
		else{
			return &vec->array[0];
		}
	}
		
}

VectorNode vector_last(Vector vec) {
	if (vec->size == 0)
		return VECTOR_EOF;
	else{
		if (vec->size + vec->size2 - 1 > vec->capacity){
			return &vec->array2[vec->size + vec->size2-1];
		}
		else{
			return &vec->array[vec->size + vec->size2-1];
		}
	}
}

VectorNode vector_next(Vector vec, VectorNode node) {
	if (vec->start > 0){
		if (node == &vec->array2[vec->size + vec->size2-1]){
			return VECTOR_EOF;
		}
		if (vec->start != vec->capacity){
			if (node == &vec->array2[vec->start - 1]){
				return &vec->array[vec->start];
			}
			else if (node == &vec->array[vec->capacity - 1]){
				return &vec->array2[vec->capacity];
			}
		}
	}
	else{
		if (node == &vec->array[vec->size + vec->size2 - 1]){
			return VECTOR_EOF;
		}
	}
	
	return node + 1;
}

VectorNode vector_previous(Vector vec, VectorNode node) {
	if (vec->start > 0){
		if (node == &vec->array2[0]){
			return VECTOR_BOF;
		}
		if (vec->start != vec->capacity){
			if (node == &vec->array2[vec->capacity]){
				return &vec->array[vec->capacity - 1];
			}
			else if (node == &vec->array[vec->start]){
				return &vec->array2[vec->start - 1];
			}
		}
	}
	else{
		if (node == &vec->array[0]){
			return VECTOR_BOF;
		}
	}

	return node - 1;
}

Pointer vector_node_value(Vector vec, VectorNode node) {
	return node->value;
}

VectorNode vector_find_node(Vector vec, Pointer value, CompareFunc compare) {
	// Διάσχιση του vector
	for (int i = 0; i < vec->size + vec->size2; i++){
		if (i >= vec->start && i < vec->capacity){
			if (compare(vec->array[i].value, value) == 0)
				return &vec->array[i];		// βρέθηκε
		}
		else{
			if (compare(vec->array2[i].value, value) == 0)
				return &vec->array2[i];		// βρέθηκε
		}
	}

	return VECTOR_EOF;				// δεν υπάρχει
}