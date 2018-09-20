// Popescu Flavia-Alexandra 311CD
#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// List element for Dictionary lists.
typedef struct ListNode {
	struct ListNode *next;
	struct ListNode *prev;
	char *key;
	char *value;
	int frequency;
} ListNode;

// Dictionary structure that includes the lists of elements and their number.
typedef struct Dictionary {
	ListNode **lists;		// lists of elements.
	int N;					// number of lists.
} Dictionary;


// Initializes an empty Dictionary structure.
Dictionary* createDictionary(int N);

// Adds an element to the Dictionary structure.
void addElement(Dictionary *dictionary, char *key, char *value, int frequency);

// Removes an element from the Dictionary structure.
void removeElement(Dictionary *dictionary, char *key, char *value);

// Prints all the elements from all the lists of the Dictionary structure.
void printDictionary(FILE *f, Dictionary *dictionary);

// Gets all the elements with the specified key and increments the frequencies.
ListNode* get(Dictionary *dictionary, char *key);

// Prints all the elements with the specified value.
void printValue(FILE *f, Dictionary *dictionary , char *value);

// Prints all the elements with the specified frequency.
void printFrequency(FILE *f, Dictionary *dictionary , int frequency);

// Returns a list containing the elements with the specified value.
ListNode* unionValues(Dictionary *dictionary, char *value);

// Returns a list containing the elements with maximum frequency in each list.
ListNode* unionMaxFrequencies(Dictionary *dictionary);

// Returns a new Dictionary with reversed lists of the input structure.
Dictionary* reverseLists(Dictionary *dictionary);

// Prints a double-linked non-circular list.
void printList(FILE *f, ListNode *list);

// Frees all the memory allocated for the Dictionary.
void freeDictionary(Dictionary *dictionary);

// Frees all the memory allocated for a double-linked non-circular list.
void freeList(ListNode *list);

//------------------------------------------------------------------------------

// Initializes an empty Dictionary structure.
Dictionary* createDictionary(int N) {
    int i;

	Dictionary *dictionary = (Dictionary*)malloc(sizeof(Dictionary));
	if(dictionary == NULL){
		printf("EROARE LA ALOCARE\n");
		return NULL;
	}
	dictionary->N = N;
	dictionary->lists = (ListNode**)malloc(sizeof(ListNode*)*N);

	for(i = 0; i < N; i++) {
		dictionary->lists[i] = NULL;
	}

	return dictionary;
}

// Initialize an element (key, value, frequency).
ListNode* newElement(char *key, char *value, int frequency) {
	ListNode *t = (ListNode*)malloc(sizeof(ListNode));
	if(t == NULL){
		printf("EROARE LA ALOCARE\n");
		return NULL;
	}
	t->next = NULL;
	t->prev = NULL;
	t->key = strdup(key);       
	t->value = strdup(value);
	t->frequency = frequency;

	return t;
}

// Checks if a list is empty 1-empty / 0-not empty.
int isEmptyList(ListNode *list) {
	if(list == NULL) {
		return 1;
	}
	return 0;
}

// Calculates the number of elements in one list.
int noElementsList(ListNode *list) {
    ListNode *first, *last, *crt;
    int n;
	if(isEmptyList(list))
		return 0;

	first = list;
	last = list->prev;
	crt = first;
	n = 1;
	while(crt != last) {
		crt = crt->next;
		n++;
	}
	return n;
}

// Receives an unordered circular list and sorts it.
ListNode *orderList(ListNode *list) {
	ListNode *first, *last, *crt;
    char *keyAux, *valueAux;
	int frequencyAux, ind = 1;

	first = list;
	last = list->prev;

	// Bubble sort.
	while(ind) {
		ind = 0;
		crt = first;
		while(crt != last) {
			// Descendent sort after frequency.
			if(crt->frequency < crt->next->frequency) {
				keyAux = strdup(crt->key);
				valueAux = strdup(crt->value);
				frequencyAux = crt->frequency;

				crt->key = strdup(crt->next->key);
				crt->value = strdup(crt->next->value);
				crt->frequency = crt->next->frequency;

				crt->next->key = strdup(keyAux);
				crt->next->value = strdup(valueAux);
				crt->next->frequency = frequencyAux;

				if(keyAux) {
                    free(keyAux);
                }
                if(valueAux) {
                    free(valueAux);
                }

				ind = 1;
			}
			// Alfabetical order for value.
			else if(crt->frequency == crt->next->frequency){
				if(strcmp(crt->value, crt->next->value) > 0) {
					keyAux = strdup(crt->key);
					valueAux = strdup(crt->value);
					frequencyAux = crt->frequency;

					crt->key = strdup(crt->next->key);
					crt->value = strdup(crt->next->value);
					crt->frequency = crt->next->frequency;

					crt->next->key = strdup(keyAux);
					crt->next->value = strdup(valueAux);
					crt->next->frequency = frequencyAux;

                    if(keyAux) {
                        free(keyAux);
                    }
                    if(valueAux) {
                        free(valueAux);
                    }

					ind = 1;
				}
				// Alfabetical order for key.
				else if(strcmp(crt->value, crt->next->value) == 0
					&& strcmp(crt->key, crt->next->key) > 0 ) {
					keyAux = strdup(crt->key);
					valueAux = strdup(crt->value);
					frequencyAux = crt->frequency;

					crt->key = strdup(crt->next->key);
					crt->value = strdup(crt->next->value);
					crt->frequency = crt->next->frequency;

					crt->next->key = strdup(keyAux);
					crt->next->value = strdup(valueAux);
					crt->next->frequency = frequencyAux;

					if(keyAux) {
                        free(keyAux);
                    }
                    if(valueAux) {
                        free(valueAux);
                    }

					ind = 1;
				}
			}
			crt = crt->next;
		}
	}

	return list;
}

// Calculates the index in the array where the element will be placed.
int computeIndex(char *key, int N){
    int index = 0, i;

	for(i = 0; i < strlen(key); i++) {
		index += key[i];
    }
	index %= N;

	return index;
}

// Deletes a given element and frees the memory.
void deleteElement(ListNode *elem){
    if (elem != NULL) {
        if (elem->key != NULL) {
            free(elem->key);
            elem->key = NULL;
        }
        if (elem->value != NULL) {
            free(elem->value);
            elem->value = NULL;
        }
        elem->prev = NULL;
        elem->next = NULL;
        free(elem);
        elem = NULL;
    }
}

// Removes an element from the Dictionary structure.
void removeElement(Dictionary *dictionary, char *key, char *value) {
    ListNode *first, *last, *crt, *toDel;
    int index;

	if(dictionary == NULL){
		return;
    }

    index = computeIndex(key, dictionary->N);

	if(dictionary->lists[index] == NULL)
		return;

	first = dictionary->lists[index];
	last = dictionary->lists[index]->prev;
	crt = first;

	// If the element to be deleted is the first in the list.
	if(strcmp(first->key, key) == 0 && strcmp(first->value, value) == 0) {
		
		// If the list has 1 element.
		if (first == last){
			deleteElement(first);
			dictionary->lists[index] = NULL;
			return;
		}
		// If the list has more than 1 element
		else {
			dictionary->lists[index] = first->next;
			dictionary->lists[index]->prev->next = first->next;
			dictionary->lists[index]->prev = first->prev;
			deleteElement(first);
			return;
		}
	}

	// If the element to be deleted is neither the first nor the last in the list.
	while(crt != last) {
		if(strcmp(crt->key, key) == 0 && strcmp(crt->value, value) == 0) {
			crt->prev->next = crt->next;
			crt->next->prev = crt->prev;
			deleteElement(crt);
			crt = NULL;
			return;
		}
		crt = crt->next;
	}
	// If the element to be deleted is the last in the list.
	if(strcmp(last->key, key) == 0 && strcmp(last->value, value) == 0) {
		last->prev->next = last->next;
		first->prev = last->prev;
		deleteElement(last);
	}
}

// Adds an element to the Dictionary structure.
void addElement(Dictionary *dictionary, char *key, char *value, int frequency) {
    ListNode *first, *last, *crt, *newEl;
    int index, i;

    // Finds the index (the number of the list).
	index = computeIndex(key, dictionary->N);

	// Finds the total number of elements in dictionary.
	int dictionarySize = 0;
	for (i = 0; i < dictionary->N; i++) {
		dictionarySize += noElementsList(dictionary->lists[i]);
	}
	// Checks if the total number of elements is greater than 2*N.
	if(dictionarySize >= 2*dictionary->N) {
		for(i = 0; i < dictionary->N; i++) {
			if (!isEmptyList(dictionary->lists[i])){
                removeElement(dictionary, dictionary->lists[i]->prev->key,
				dictionary->lists[i]->prev->value);
            }
		}
	}

	// If the list is empty.
	if(isEmptyList(dictionary->lists[index])) {
		// Creates a new element.
		newEl = newElement(key, value, frequency);
        if (newEl == NULL){
            return;
		}
		dictionary->lists[index] = newEl;
		dictionary->lists[index]->next = newEl;
		dictionary->lists[index]->prev = newEl;
	}
	// If the list is not empty.
	else {
		first = dictionary->lists[index];
		last = dictionary->lists[index]->prev;
		crt = first;

		while(crt != last) {
			// If the key and value are already in my list.
			if(strcmp(crt->key, key) == 0 && strcmp(crt->value, value) == 0) {
				crt->frequency += frequency;
				first = orderList(first);
				dictionary->lists[index] = first;
				return;
			}
			crt = crt->next;
		}
		// If the key and value are already in my list - checking the last element. 
		if(strcmp(last->key, key) == 0 && strcmp(last->value, value) == 0) {
			last->frequency += frequency;
			first = orderList(first);
			dictionary->lists[index] = first;
			return;
		}

		// If there are N elements in the list.
		if(noElementsList(first) == dictionary->N) {
			if(!isEmptyList(first)) {
				removeElement(dictionary, last->key, last->value);
				last = first->prev;
			}
		}

		// Creates a new element.
		newEl = newElement(key, value, frequency);
		if (newEl == NULL){
            return;
		}
		if (dictionary->lists[index] == NULL){
			dictionary->lists[index] = newEl;
			dictionary->lists[index]->prev = dictionary->lists[index];
			dictionary->lists[index]->next = dictionary->lists[index];
		}
		else {
			newEl->next = first;
			newEl->prev = last;

			last->next = newEl;
			first->prev = newEl;
			last = newEl;

			first = orderList(first);

			dictionary->lists[index] = first;
		}
	}
}

// Prints all the elements from all the lists of the Dictionary structure.
void printDictionary(FILE *f, Dictionary *dictionary) {
	ListNode *first, *last, *crt;
	int i;
	if(dictionary == NULL)
		return;
	// For each list in the dictionary.
	for(i = 0; i < dictionary->N; i++) {
		fprintf(f, "List %d: ", i);

		// The actual list.
		if(!isEmptyList(dictionary->lists[i])) {

			first = dictionary->lists[i];
			last = first->prev;
			crt = first;
			while(crt != last) {
				fprintf(f, "(%s, %s, %d) ", crt->key, crt->value, crt->frequency);
				crt = crt->next;
			}
			// The last element from the list
			fprintf(f, "(%s, %s, %d) ", last->key, last->value, last->frequency);
		}
		fprintf(f, "\n");
	}
}

// Gets all the elements with the specified key and increments the frequencies.
ListNode* get(Dictionary *dictionary, char *key) {
    ListNode *first, *last, *crt, *simpleList = NULL, *crtSimpleList = NULL, *newEl;
	int i, sign = 0;

	// Search in each list of the dictionary.
	for(i = 0; i < dictionary->N; i++) {
		if(isEmptyList(dictionary->lists[i])) {
			continue;
        }
		first = dictionary->lists[i];
		last = first->prev;
		crt = first;
		// Search the key in one list.
		while(crt != last) {
			// If found, adds the element in the double-linked list.
			if(strcmp(crt->key, key) == 0) {
				sign = 1;
				newEl = newElement(crt->key, crt->value, crt->frequency);
				if(newEl == NULL) {
                    return NULL;
                }
				if(isEmptyList(simpleList)) {
					crtSimpleList = newEl;
					simpleList = newEl;
				}
				else {
					crtSimpleList->next = newEl;
					newEl->prev = crtSimpleList;
					crtSimpleList = crtSimpleList->next;
				}
			}
			crt = crt->next;
		}
		// Checks for the last element as well
		if(strcmp(last->key, key) == 0) {
			sign = 1;
			newEl = newElement(last->key, last->value, last->frequency);
			if(newEl == NULL) {
				return NULL;
			}
			if(isEmptyList(simpleList)) {
				crtSimpleList = newEl;
				simpleList = newEl;
			}
			else {
				crtSimpleList->next = newEl;
				newEl->prev = crtSimpleList;
				crtSimpleList = crtSimpleList->next;
			}
		}
	}

	// For each element that was found increments the frequency.
	for (i = 0; i < dictionary->N; i++) {
		if(isEmptyList(dictionary->lists[i])) {
			continue;
        }
		first = dictionary->lists[i];
		last = first->prev;
		crt = first;
		while(crt != last) {
			if(strcmp(crt->key, key) == 0) {
				crt->frequency++;
			}
			crt = crt->next;
		}
		if(strcmp(last->key, key) == 0) {
			last->frequency++;
		}
		dictionary->lists[i] = orderList(first);
	}

	// If no element was found
	if(sign == 0) {
		return NULL;
	}
 	return simpleList;
}

// Prints all the elements with the specified value.
void printValue(FILE *f, Dictionary *dictionary , char *value) {
	ListNode *first, *last, *crt;
	int i;

	if(dictionary == NULL) {
		fprintf(f, "\n");
		return;
	}
	// For each list in the dictionary.
	for(i = 0; i < dictionary->N; i++) {
		if(isEmptyList(dictionary->lists[i])) {
			continue;
		}

		// Searches in the list.
		first = dictionary->lists[i];
		last = dictionary->lists[i]->prev;
		crt = first;
		while(crt != last) {
			// If the value is found.
			if(strcmp(crt->value, value) == 0) {
				fprintf(f, "(%s, %s, %d) ", crt->key, crt->value, crt->frequency);
			}
			crt = crt->next;
		}
		// Checks for the last as well.
		if(strcmp(last->value, value) == 0) {
			fprintf(f, "(%s, %s, %d) ", last->key, last->value, last->frequency);
		}
	}
	fprintf(f, "\n");
}

// Prints all the elements with the specified frequency.
void printFrequency(FILE *f, Dictionary *dictionary , int frequency) {
	ListNode *first, *last, *crt;
	int i;

	if(dictionary == NULL) {
		fprintf(f, "\n");
		return;
	}
	// For each list in the dictionary.
	for(i = 0; i < dictionary->N; i++) {
		if(isEmptyList(dictionary->lists[i])) {
			continue;
		}

		// Searches in the list.
		first = dictionary->lists[i];
		last = dictionary->lists[i]->prev;
		crt = first;
		while(crt != last) {
			// If the frequency is found.
			if(crt->frequency == frequency) {
				fprintf(f, "(%s, %s, %d) ", crt->key, crt->value, crt->frequency);
			}
			crt = crt->next;
		}
		// Checks for the last as well.
		if(last->frequency == frequency) {
			fprintf(f, "(%s, %s, %d) ", last->key, last->value, last->frequency);
		}
	}
	fprintf(f, "\n");
}

// Returns a list containing the elements with the specified value.
ListNode* unionValues(Dictionary *dictionary, char *value){
	ListNode *first, *last, *crt, *simpleList = NULL, *crtSimpleList = NULL, *newEl;
	int i, sign = 0;

	// For each list in the dictionary.
	for(i = 0; i < dictionary->N; i++) {
		if(isEmptyList(dictionary->lists[i])) {
			continue;
        }

        // Searches in the list.
		first = dictionary->lists[i];
		last = first->prev;
		crt = first;
		while(crt != last) {
			// If the value is found.
			if(strcmp(crt->value, value) == 0) {
				sign = 1;

				// Creates a new element.
				newEl = newElement(crt->key, crt->value, crt->frequency);
				if(newEl == NULL) {
					return NULL;
				}
				// Adds the element in the double-linked list.
				if(isEmptyList(simpleList)) {
					crtSimpleList = newEl;
					simpleList = newEl;
				}
				else {
					crtSimpleList->next = newEl;
					newEl->prev = crtSimpleList;
					crtSimpleList = crtSimpleList->next;
				}
			}
			crt = crt->next;
		}

		// Checks for the last element as well. 
		if(strcmp(last->value, value) == 0) {
			sign = 1;
			// Creates a new element.
			newEl = newElement(last->key, last->value, last->frequency);
			if(newEl == NULL) {
				return NULL;
			}
			// Adds the element in the double-linked list.
			if(isEmptyList(simpleList)) {
				crtSimpleList = newEl;
				simpleList = newEl;
			}
			else {
				crtSimpleList->next = newEl;
				newEl->prev = crtSimpleList;
				crtSimpleList = crtSimpleList->next;
			}
		}
	}

	// If no element was found.
	if(sign == 0) {
		return NULL;
	}
 	return simpleList;
}

// Returns a list containing the elements with maximum frequency in each list.
ListNode* unionMaxFrequencies(Dictionary *dictionary) {
    ListNode *first, *last, *crt, *simpleList = NULL, *crtSimpleList = NULL, *newEl;
    int i, sign = 0;

	if(dictionary == NULL) {
		return NULL;
	}

	// For each list in dictionary.
	for(i = 0; i < dictionary->N; i++) {
		// If the list is empty goes to next one.
		if(isEmptyList(dictionary->lists[i])) {
			continue;
        }

        // Search in list.
		first = dictionary->lists[i];
		last = first->prev;
		crt = first;
		while(crt != last) {
			// The first element in the list has the max frequency.
			if(crt->frequency == first->frequency) {
                newEl = newElement(crt->key, crt->value, crt->frequency);
		   		if(newEl == NULL) {
					return NULL;
				}
				if(isEmptyList(simpleList)) {
					crtSimpleList = newEl;
					simpleList = newEl;
				}
				else {
					crtSimpleList->next = newEl;
					newEl->prev = crtSimpleList;
					crtSimpleList = crtSimpleList->next;
				}
				sign = 1;
			}
			crt = crt->next;
		}
		// Checks for the last as well.
		if(last->frequency == first->frequency) {
				newEl = newElement(last->key, last->value, last->frequency);
				if(newEl == NULL) {
					return NULL;
				}
				if(isEmptyList(simpleList)) {
					crtSimpleList = newEl;
					simpleList = newEl;
				}
				else {
					crtSimpleList->next = newEl;
					newEl->prev = crtSimpleList;
					crtSimpleList = crtSimpleList->next;
				}
				sign = 1;
			}
	}

	// If no element was found.
	if(sign == 0) {
		return NULL;
	}
 	return simpleList;
}

// Adds an element to the Dictionary structure without sorting the elements in the lists.
void addElementNoSort(Dictionary *dictionary, char *key, char *value, int frequency) {
	ListNode *first, *last, *crt, *newEl;
	int index = 0, i, dictionarySize = 0;

	// Finds the index (the number of the list).
	index = computeIndex(key, dictionary->N);

	// Finds the total number of elements in dictionary.
	for (i = 0; i < dictionary->N; i++) {
		dictionarySize += noElementsList(dictionary->lists[i]);
	}
	// Checks if the total number of elements is greater than 2*N.
	if(dictionarySize > 2*dictionary->N) {
		for(i = 0; i < dictionary->N; i++) {
			if (!isEmptyList(dictionary->lists[i])){
                removeElement(dictionary, dictionary->lists[i]->prev->key,
				dictionary->lists[i]->prev->value);
            }
		}
	}

	// If the list is empty.
	if(isEmptyList(dictionary->lists[index])) {
		// Creates a new element.
		newEl = newElement(key, value, frequency);
        if (newEl == NULL){
            return;
		}
		dictionary->lists[index] = newEl;
		dictionary->lists[index]->next = newEl;
		dictionary->lists[index]->prev = newEl;
		//deleteElement(newEl);
	}
	// If the list is not empty.
	else {
		first = dictionary->lists[index];
		last = dictionary->lists[index]->prev;
		crt = first;

		while(crt != last) {
			// If the key and value are already in my list.
			if(strcmp(crt->key, key) == 0 && strcmp(crt->value, value) == 0) {
				crt->frequency += frequency;
				first = orderList(first);
				//dictionary->lists[index] = first;
				return;
			}
			crt = crt->next;
		}
		// If the key and value are already in my list - checking the last element. 
		if(strcmp(last->key, key) == 0 && strcmp(last->value, value) == 0) {
			last->frequency += frequency;
			dictionary->lists[index] = first;
			return;
		}
		
		// If there are N elements in the list.
		if(noElementsList(first) == dictionary->N) {
			if(!isEmptyList(first)) {
				removeElement(dictionary, last->key, last->value);
				last = first->prev;
			}
		}

		// Creates a new element.
		newEl = newElement(key, value, frequency);
        if (newEl == NULL){
            return;
		}
		if (dictionary->lists[index] == NULL){
			dictionary->lists[index] = newEl;
			dictionary->lists[index]->prev = dictionary->lists[index];
			dictionary->lists[index]->next = dictionary->lists[index];
		}
		else {
			newEl->next = first;
			newEl->prev = last;

			last->next = newEl;
			first->prev = newEl;
			last = newEl;

			dictionary->lists[index] = first;
		}
	}
}

// Returns a new Dictionary with reversed lists of the input structure.
Dictionary* reverseLists(Dictionary *dictionary) {
	Dictionary *newDictionary;
	ListNode *first, *last, *crt;

	if(dictionary == NULL) {
		return NULL;
    }

    // Creates a new dictionary.
	newDictionary = createDictionary(dictionary->N);
	int i;
	for(i = 0; i < dictionary->N; i++) {
		if(!isEmptyList(dictionary->lists[i])) {
			// Adds the element.
			first = dictionary->lists[i];
			last = dictionary->lists[i]->prev;
			crt = last;

			// Traverse in reversed order.
			while(crt != first) {
				addElementNoSort(newDictionary, crt->key, crt->value, crt->frequency);
				crt = crt->prev;
			}
			// For the first element to be added.
			addElementNoSort(newDictionary, first->key, first->value, first->frequency);
		}
		else {
			newDictionary->lists[i] = NULL;
		}
	}

	return newDictionary;
}

// Prints a double-linked non-circular list.
void printList(FILE *f, ListNode *list) {
	ListNode *crt;

	if(isEmptyList(list)) {
		fprintf(f,"\n");
		return;
	}

	crt = list;
	while(crt != NULL) {
		fprintf(f, "(%s, %s, %d) ", crt->key, crt->value, crt->frequency);
		crt = crt->next;
	}
	fprintf(f, "\n");
}

// Frees all the memory allocated for a double-linked circular list.
void freeListCirc(ListNode *list) {
    ListNode *first, *crt, *last, *toDel;

    if(isEmptyList(list)) {
		return;
    }

	first = list;
	last = first->prev;
	crt = first;
	if(first == last){
		deleteElement(first);
		return;
	}

	while(crt != last) {
		toDel = crt;
		crt = crt->next;
        deleteElement(toDel);
	}
	deleteElement(last);
}

// Frees all the memory allocated for the Dictionary.
void freeDictionary(Dictionary *dictionary) {
	int i;

	if(dictionary == NULL) {
		return;
    }

	for(i = 0; i < dictionary->N; i++) {
		if(!isEmptyList(dictionary->lists[i])) {
			freeListCirc(dictionary->lists[i]);
		}
	}
	free(dictionary);
	dictionary = NULL;
}

// Frees all the memory allocated for a double-linked non-circular list.
void freeList(ListNode *list) {
	ListNode *crt, *toDel;

	if(isEmptyList(list)) {
		return;
    }

    crt = list;
	while(crt != NULL) {
		toDel = crt;
		crt = crt->next;
		deleteElement(toDel);
	}
}
#endif
