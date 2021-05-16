///////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT Deque μέσω ADT Map.
//
///////////////////////////////////////////////////////////

#define VECTOR_MIN_CAPACITY 10

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "ADTDeque.h"

#include "ADTMap.h"

struct deque_node {
    Pointer value;              // Η τιμή του κόμβου.
};

struct deque {
	DequeNode array;			// Τα δεδομένα, πίνακας από struct vector_node
	int size;					// Πόσα στοιχεία έχουμε προσθέσει
	int capacity;				// Πόσο χώρο έχουμε δεσμεύσει (το μέγεθος του array). Πάντα capacity >= size, αλλά μπορεί να έχουμε
	DestroyFunc destroy_value;	// Συνάρτηση που καταστρέφει ένα στοιχείο του vector.
    int start;
};

Deque deque_create(int size, DestroyFunc destroy_value){
    Deque deque = malloc(sizeof(*deque));

	deque->size = size;
	deque->destroy_value = destroy_value;
    deque->start = 0;

	deque->capacity = size < VECTOR_MIN_CAPACITY ? VECTOR_MIN_CAPACITY : size;
	deque->array = calloc(deque->capacity, sizeof(*deque->array));		// αρχικοποίηση σε 0 (NULL)

	return deque;
}

int deque_size(Deque deque){
    return deque->size;
}

void deque_insert_first(Deque deque, Pointer value){
	int oldcapacity = deque->capacity;
    if (deque->capacity == deque->size) {
		// Προσοχή: δεν πρέπει να κάνουμε free τον παλιό pointer, το κάνει η realloc
		deque->capacity *= 2;
		deque->array = realloc(deque->array, deque->capacity * sizeof(*deque->array));
        for (int i = 0 ; i < deque->start ; i++){
            deque->array[deque->capacity - i - 1].value = deque->array[oldcapacity - i - 1].value;
            deque->array[oldcapacity - i - 1].value = 0;
        }
    }

    deque->start++;
    deque->array[(deque->capacity - deque->start)%deque->capacity].value = value;
    
    deque->size++;
}

void deque_insert_last(Deque deque, Pointer value){
	int oldcapacity = deque->capacity;
    if (deque->capacity == deque->size) {
		// Προσοχή: δεν πρέπει να κάνουμε free τον παλιό pointer, το κάνει η realloc
		deque->capacity *= 2;
		deque->array = realloc(deque->array, deque->capacity * sizeof(*deque->array));
        for (int i = 0 ; i < deque->start ; i++){
            deque->array[deque->capacity - i - 1].value = deque->array[oldcapacity - i - 1].value;
            deque->array[oldcapacity - i - 1].value = 0;
        }
    }

    deque->array[deque->size - deque->start].value = value;
	deque->size++;
}

void deque_remove_first(Deque deque){
    assert(deque->size != 0);		// LCOV_EXCL_LINE
	// Αν υπάρχει συνάρτηση destroy_value, την καλούμε για το στοιχείο που αφαιρείται
	if (deque->destroy_value != NULL)
		deque->destroy_value(deque->array[(deque->capacity - deque->start)%deque->capacity].value);

	// Αφαιρούμε στοιχείο οπότε ο πίνακας μικραίνει
	deque->size--;
    deque->start--;
	// Μικραίνουμε τον πίνακα αν χρειαστεί, ώστε να μην υπάρχει υπερβολική σπατάλη χώρου.
	// Για την πολυπλοκότητα είναι σημαντικό να μειώνουμε το μέγεθος στο μισό, και μόνο
	// αν το capacity είναι τετραπλάσιο του size (δηλαδή το 75% του πίνακα είναι άδειος).
	//
	if (deque->capacity > deque->size * 4 && deque->capacity > 2*VECTOR_MIN_CAPACITY) {
		
		int new_capacity = deque->capacity / 2 + deque->capacity % 2;
		
		if (deque->start < 0){
			
			int new_start = deque->start % (new_capacity - deque->capacity % 2);
			
			for (int i = 0 ; i < deque->size ; i++){
				deque->array[new_capacity - i - 1].value = deque->array[deque->size - i - 1 - deque->start].value;
				deque->array[deque->size - i - 1 - deque->start].value = 0;
			}
			deque->start = new_start;
			
		}
		else{
			
			for (int i = 0 ; i < deque->start ; i++){
				deque->array[new_capacity - i - 1].value = deque->array[deque->capacity - i - 1].value;
				deque->array[deque->capacity - i - 1].value = 0;
			}
		}
		deque->capacity = new_capacity;
        deque->array = realloc(deque->array, deque->capacity * sizeof(*deque->array));
		
	}
}

void deque_remove_last(Deque deque){
    assert(deque->size != 0);		// LCOV_EXCL_LINE
	int oldcapacity = deque->capacity;
	// Αν υπάρχει συνάρτηση destroy_value, την καλούμε για το στοιχείο που αφαιρείται
	if (deque->destroy_value != NULL)
		deque->destroy_value(deque->array[deque->size - 1 - deque->start].value);

	// Αφαιρούμε στοιχείο οπότε ο πίνακας μικραίνει
	deque->size--;

	// Μικραίνουμε τον πίνακα αν χρειαστεί, ώστε να μην υπάρχει υπερβολική σπατάλη χώρου.
	// Για την πολυπλοκότητα είναι σημαντικό να μειώνουμε το μέγεθος στο μισό, και μόνο
	// αν το capacity είναι τετραπλάσιο του size (δηλαδή το 75% του πίνακα είναι άδειος).
	//
	if (deque->capacity > deque->size * 4 && deque->capacity > 2*VECTOR_MIN_CAPACITY) {
		deque->capacity /= 2;
		deque->array = realloc(deque->array, deque->capacity * sizeof(*deque->array));
        for (int i = 0 ; i < deque->start ; i++){
            deque->array[deque->capacity - i - 1].value = deque->array[oldcapacity - i - 1].value;
            deque->array[oldcapacity - i - 1].value = 0;
        }
	}
}

Pointer deque_get_at(Deque deque, int pos){
    assert(pos >= 0 && pos < deque->size);	// LCOV_EXCL_LINE (αγνοούμε το branch από τα coverage reports, είναι δύσκολο να τεστάρουμε το false γιατί θα κρασάρει το test)
    int i = (deque->capacity - deque->start + pos)%deque->capacity;
    
	return deque->array[i].value;
}


void deque_set_at(Deque deque, int pos, Pointer value){
    assert(pos >= 0 && pos < deque->size);	// LCOV_EXCL_LINE

    int i = (deque->capacity - deque->start + pos)%deque->capacity;

	// Αν υπάρχει συνάρτηση destroy_value, την καλούμε για το στοιχείο που αντικαθίσταται
	if (value != deque->array[i].value && deque->destroy_value != NULL)
		deque->destroy_value(deque->array[i].value);

	deque->array[i].value = value;
}


Pointer deque_find(Deque deque, Pointer value, CompareFunc compare){
	DequeNode node = deque_find_node(deque, value, compare);
	if (node == DEQUE_EOF){
		return NULL;
	}
	return deque_node_value(deque, node);
}

DestroyFunc deque_set_destroy_value(Deque deque, DestroyFunc destroy_value){
    DestroyFunc old = deque->destroy_value;
	deque->destroy_value = destroy_value;
	return old;
}

void deque_destroy(Deque deque){
    // Αν υπάρχει συνάρτηση destroy_value, την καλούμε για όλα τα στοιχεία
	if (deque->destroy_value != NULL)
		for (int i = (deque->capacity - deque->start)%deque->capacity ; i < deque->size; i = (i+1)%deque->capacity)
			deque->destroy_value(deque->array[i].value);

	// Πρέπει να κάνουμε free τόσο τον πίνακα όσο και το struct!
	free(deque->array);
	free(deque);
}

DequeNode deque_first(Deque deque){
    if (deque->size == 0)
		return DEQUE_BOF;
	else	
		return &deque->array[(deque->capacity - deque->start)%deque->capacity];
}

DequeNode deque_last(Deque deque){
    if (deque->size == 0)
		return DEQUE_EOF;
	else
		return &deque->array[deque->size - 1 - deque->start];
}

DequeNode deque_next(Deque deque, DequeNode node){
    if (node == &deque->array[deque->size - 1 - deque->start])
		return DEQUE_EOF;
	else if (node == &deque->array[deque->capacity - 1] && deque->start > 0){
        return &deque->array[0];
    }
	
	return node + 1;
}

DequeNode deque_previous(Deque deque, DequeNode node){
    if (node == &deque->array[(deque->capacity - deque->start)%deque->capacity])
		return DEQUE_BOF;
	else if (node == &deque->array[0] && deque->start > 0){
        return &deque->array[deque->capacity - 1];
    }
	
	return node - 1;
}

Pointer deque_node_value(Deque deque, DequeNode node){
	return node->value;
}

DequeNode deque_find_node(Deque deque, Pointer value, CompareFunc compare){
	int i = (deque->capacity - deque->start)%deque->capacity;
	while(1){
		if (compare(deque->array[i].value, value) == 0)
            return &deque->array[i];        // βρέθηκε

		if (i == deque->size - deque->start - 1){
			break;
		}
		i = (i+1)%deque->capacity;
	}
	
	return DEQUE_EOF;				// δεν υπάρχει
}
