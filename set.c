////
//// Created by dako6 on 25/04/2024.
////
#include "set.h"

void readSet(Set *set, char *input) {
    int value;
    char *temp = input;
    removeSpaces(input);
    temp += strlen("read_set") + SET_NAME_SIZE + 1;
    while (sscanf(temp, "%d", &value) == 1) {
        if (value == -1) {
            break;
        } else if (containsElement(set, value)) {
            temp += checkNumberOfDigit(value) + 1;
            continue;
        } else {
            addElementToSet(set, value);
            temp += checkNumberOfDigit(value);
        }
        temp++;
    }
}
int isSetEmpty(Set *set) {
    int i;
    for (i = 0; i < SET_SIZE / 8; i++) {
        if (set->elements[i] != 0)
            return false; // Set is not empty
    }
    return true; // Set is empty
}
void printSet(Set *set) {
    int i;
    if ( isSetEmpty(set)) {
        printf("The set is empty.\n");
        return;
    }
    for (i = 0; i < SET_SIZE; i++) {
        if (containsElement(set, i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
}
void unionSet(Set *set1, Set *set2, Set *result) {
    int i;
    Set temp;
    for (i = 0; i < SET_SIZE / 8; i++) {
        temp.elements[i] = set1->elements[i] | set2->elements[i];
    }
    // Now temp contains the union of set1 and set2
    memcpy(result, &temp, sizeof(Set)); // Copy temp to result
}


/*add element to the set*/
void addElementToSet(Set *set, int value) {
    if (value >= 0 && value < SET_SIZE) {
        set->elements[value / 8] |= (1 << (value % 8));
    } else {
        printf("Invalid element value.\n");
    }
}

/*check if the element is in the set*/
int containsElement(Set *set, int element) {
    if (element >= 0 && element < SET_SIZE) {
        if (set->elements[element / 8] & (1 << (element % 8)))
            return 1;
    }
    return 0;
}

void removeSpaces(char *inputString) {
    char *dst = inputString;
    char *src = inputString;

    // Skip leading spaces
    while (isspace((unsigned char) *src)) {
        src++;
    }

    while (*src) {
        if (!isspace((unsigned char) *src)) {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0'; // Null-terminate the modified string
}

int checkNumberOfDigit(int num) {
    if (num >= 0 && num <= 9) {
        return 1;
    } else if (num >= 10 && num <= 99) {
        return 2;
    } else if (num >= 100 && num <= 127) {
        return 3;

    }
    return 0;
}