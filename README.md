![run-tests](../../workflows/run-tests/badge.svg)

## 2021 Project 2

Εκφώνηση: https://k08.chatzi.org/projects/project2/


### Προσωπικά στοιχεία

__Όνομα__: Νικος Μιχαλουτσος

__Α.Μ.__: sdi2000133

### Ασκήσεις που παραδίδονται

Συμπληρώστε εδώ τις ασκήσεις (και τυχόν bonus) που παραδίδετε. Αν κάποια άσκηση
βρίσκεται σε μη αναμενόμενα αρχεία αναφέρετε και τα αρχεία αυτά.

- Ασκηση 1
- Ασκηση 2
- Ασκηση 3
- Ασκηση 4
- Ασκηση 5

### Documentation

Συμπληρώστε εδώ __όσο documentation χρειάζεται__ ώστε οι βαθμολογητές να
κατανοήσουν πλήρως τις λύσεις σας και να τις βαθμολογήσουν ανάλογα. Αυτό θα
πρέπει να γίνει ανεξάρτητα με το αν ο κώδικάς σας είναι καλά σχολιασμένος,
πράγμα που συνιστάται.

Υποθετοντας οτι ΟΛΕΣ οι συναρτησεις map ειναι O(logn) πολ/τητας
Ασκηση 1 διαφορες πολυπλοκοτητας:
Dynamic Array:
vector_create: O(n)
vector_size: O(1)
vector_get_at = O(1)
vector_set_at = O(1)
vector_insert_last = O(n) worst case
vector_remove_last = O(n) worst case
vector_find = O(n)
vector_set_destroy_value = O(1)
vector_destroy = O(n)
vector_first = O(1)
vector_last = O(1)
vector_next = O(1)
vector_previous = O(1)
vector_node_value = O(1)
vector_find_node = O(n)

MAP:
vector_create: O(nlogn)
vector_size: O(logn)
vector_get_at = O(logn)
vector_set_at = O(logn)
vector_insert_last = O(logn)
vector_remove_last = O(logn)
vector_find = O(nlogn)
vector_set_destroy_value = O(logn)
vector_destroy = O(n)
vector_first = O(logn)
vector_last = O(logn)
vector_next = O(logn)
vector_previous = O(logn)
vector_node_value = O(logn)
vector_find_node = O(nlogn)

Ασκηση 3 διαφορες πολυπλοκοτητας:
MAP:
deque_create: O(nlogn)
deque_size: O(logn)
deque_get_at = O(logn)
deque_set_at = O(logn)
deque_insert_last = O(logn)
deque_remove_last = O(logn)
deque_insert_first = O(logn)
deque_remove_first = O(logn)
deque_find = O(nlogn)
deque_set_destroy_value = O(logn)
deque_destroy = O(logn)
deque_first = O(logn)
deque_last = O(logn)
deque_next = O(logn)
deque_previous = O(logn)
deque_node_value = O(logn)
deque_find_node = O(nlogn)

Dynamic Array:
deque_create: O(n)
deque_size: O(1)
deque_get_at = O(1)
deque_set_at = O(1)
deque_insert_last = O(n) worst case
deque_remove_last = O(n) worst case
deque_insert_first = O(n) worst case
deque_remove_first = O(n) worst case
deque_find = O(n)
deque_set_destroy_value = O(1)
deque_destroy = O(1)
deque_first = O(1)
deque_last = O(1)
deque_next = O(1)
deque_previous = O(1)
deque_node_value = O(1)
deque_find_node = O(n)

Πολυ πιο απλος ο κωδικας κι η υλοποιηση του MAP version στην ασκηση 2-3

Η διαφορα της ασκησης 4 με το απλο vector ειναι οτι το insert και το remove ειναι Ο(1). Παρολα αυτα υπαρχει μερικη σπαταλη μνημης αφου χρησιμοποιουμε 2 arrays.

Ο κυριος Χατζηκοκολακης ειπε (στο piazza) να μην φτιαξουμε τεστ για την set_set_at στην ασκηση 5..εφτιαξα ενα απλα για να δειτε εσεις οτι δουλευει αν και δεν ειναι τεστ "της προκοπης" και δουλευει με printfs.