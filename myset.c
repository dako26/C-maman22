#include <stdio.h>
#include "set.h"

int main(void) {
    Set SETA, SETB, SETC, SETD, SETE, SETF;
    char input[MAX_SIZE_INPUT],
    char *command = (char *)malloc(MAX_SIZE_NAME_COMMEND + 1); // +1 for null terminator
    char *set1 = (char *)malloc(MAX_SIZE_NAME_INPUT + 1); // +1 for null terminator
    char *set2 = (char *)malloc(MAX_SIZE_NAME_INPUT + 1); // +1 for null terminator
    char *set3 = (char *)malloc(MAX_SIZE_NAME_INPUT + 1); // +1 for null terminator

    if (command == NULL || set1 == NULL || set2 == NULL || set3 == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }
    initializeSet(&SETA);
    initializeSet(&SETB);
    initializeSet(&SETC);
    initializeSet(&SETD);
    initializeSet(&SETE);
    initializeSet(&SETF);
    printf("Hello\n");
    printf("Welcome to use Daniel's program.\n");
    printf("the program has 6 group: SETA, SETB, SETC, SETD, SETE, SETF.\n");
    printf("the program know:\n");
    printf("1.read the numbers you enter and put all the number in the set.\n  to use read you must use with format \"read_set <SET> numbers and finish with -1\".\n"
           "  between number must use for \',\' example \"read_set SETA, 1,2,3,4,5,6,7,8,9,10,-1\".\n");
    printf("2.print the set you want to see.\n  to use print you must use this format \"print_set <SET>\".\n"
           "  example \"print_set SETA\".\n");
    printf("3.union set1 with set2 and put in set3.\n  to use union you must use this format \"union_set <SET1>, <SET2>, <SET3>\".\n");
    printf("  for example \"union_set SETA SETB SETC\".\n");
    printf("4.intersect set1 with set2 and put in set3.\n  to use intersect you must use this format \"intersect_set <SET1>, <SET2>, <SET3>\".\n");
    printf("  for example \"intersect_set SETA, SETB, SETC\".\n");
    printf("5.subtract set2 with set1 and put in set3.\n  to use subtract you must use this format \"sub_set <SET1>, <SET2>, <SET3>\".\n");
    printf("  for example \"sub_set SETA, SETB, SETC\".\n");
    printf("6.symmetric difference set1 with set2 and put in set3.\n  to use symmetric you must use this format \"symdiff_set <SET1>, <SET2>, <SET3>\".\n");
    printf("  for example \"symdiff_set SETA, SETB, SETC\".\n");
    printf("7.to exit the program you must use \"stop\".\n");
    while (fgets(input, sizeof(input), stdin) != NULL) {
//
        checkValidInput(input, command, set1, set2, set3);
    }
    return EXIT;
}

int checkCommand(char *command) {
    if (strcmp(command, "read_set") == 0) {
        return read_set;
    } else if (strcmp(command, "print_set") == 0) {
        return print_set;
    } else if (strcmp(command, "union_set") == 0) {
        return union_set;
    } else if (strcmp(command, "intersect_set") == 0) {
        return intersect_set;
    } else if (strcmp(command, "sub_set") == 0) {
        return sub_set;
    } else if (strcmp(command, "symdiff_set") == 0) {
        return symdiff_set;
    } else if (strcmp(command, "stop") == 0) {
        printf("Goodbye\n");
        return stop;
    } else {
        printf("wrong input\n");
        return WRONG_INPUT;
    }
}

int checkValidInput(char *input, char *command, char *set1, char *set2, char *set3) {
    int commandType;
    if (sscanf(input, "%s", command) != 1) {
        printf("wrong input\n");
        return WRONG_INPUT;
    }
    commandType = checkCommand(command);
    size_t commandLength = strlen(command);
    if (input[commandLength] != ' '&& commandType != stop) {
        printf("wrong input\n");
        return WRONG_INPUT;
    }
    memmove(input, input + commandLength+1, strlen(input) - commandLength + 1);

    switch (commandType) { //todo fix valid 1 set and start 3 set function
        case read_set:
            break;
        case print_set: /*1*/
            checkValidOneSets(&input,&set1);
            break;
        case union_set:
        case intersect_set:
        case sub_set:
        case symdiff_set: /*3*/
            checkValidThreeSets(&input,&set1,&set2 ,&set3)
            break;
        case stop:
            if (strlen(input) != 0) {
                printf("wrong input\n");
                return WRONG_INPUT;
            }
            return stop;

        default:
            printf("wrong input\n");
            return WRONG_INPUT;
    }
}
int checkValidOneSets(char **input,char **set1){ //todo check if memory allocation is needed
    char *inputString = *input;
    char tempSet[MAX_SIZE_NAME_INPUT];
    /* Read the set name from inputString */
    if (sscanf(inputString, "%s", tempSet) != 1) {
        printf("Wrong input format.\n");
        return false;
    }
    /*  Check if the set name is valid*/
    if (!checkValidSetName(tempSet)) {
        printf("Wrong input format.\n");
        return false;
    }
    /*Allocate memory for set1*/
    *set1 = malloc(strlen(tempSet+1));
    if (*set1 == NULL) {
        printf("Memory allocation failed.\n");
        return false;
    }
    /* Copy the set name to set1*/
    strcpy(*set1, tempSet);
    /* Update inputString to point to the character after the extracted set name*/
    inputString += strlen(tempSet); // Adjust inputString to point to the character after the extracted set name
    if (*inputString != '\0'){
        printf("wrong input\n");
        return WRONG_INPUT;
    }

    return true;
}
int checkValidThreeSets(char **input,char **set1, char **set2, char **set3) {
    char *checkInput = *input;
    if (sscanf(checkInput, "%s %s %s", set1, set2, set3) != 3) {
        printf("wrong input\n");
        return WRONG_INPUT;
    }
    return 0;
}

/*check if the element is in the set*/
int containsElement(Set *set, int element) {
    if (element >= 0 && element < SET_SIZE) {
        if (set->elements[element / 8] & (1 << (element % 8)))
            return 1;
    }
    return 0;
}
int checkValidSetName(char *set)
{
    if (strcmp(set, "SETA") == 0 || strcmp(set, "SETB") == 0 || strcmp(set, "SETC") == 0 || strcmp(set, "SETD") == 0 || strcmp(set, "SETE") == 0 || strcmp(set, "SETF") == 0) {
        return true;
    }
    return false;
}

/*add initializeSet function*/

void initializeSet(Set *set) {
    int i;
    for (i = 0; i < SET_SIZE / 8; ++i) {
        set->elements[i] = 0;
    }
}

