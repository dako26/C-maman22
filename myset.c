#include <stdio.h>
#include "set.h"

int main(void) {
    Set SETA, SETB, SETC, SETD, SETE, SETF;
    int typeCommand;
    char input[MAX_SIZE_INPUT];
    char *command = (char *) malloc(MAX_SIZE_NAME_COMMEND + 1); // +1 for null terminator
    char *set1 = (char *) malloc(MAX_SIZE_NAME_INPUT + 1); // +1 for null terminator
    char *set2 = (char *) malloc(MAX_SIZE_NAME_INPUT + 1); // +1 for null terminator
    char *set3 = (char *) malloc(MAX_SIZE_NAME_INPUT + 1); // +1 for null terminator
    char *tempSet;

    if (command == NULL || set1 == NULL || set2 == NULL || set3 == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }
    initializeSet( &SETA);
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
        typeCommand=checkValidInput(input, command, set1, set2, set3);
        if (typeCommand == WRONG_INPUT) {
            continue;
        }
        if (typeCommand == stop) {
            cleanup(command, set1, set2, set3);
            return EXIT;
        }
    }



    cleanup(command, set1, set2, set3, tempSet);

    return EXIT;
}

void cleanup(char *command, char *set1, char *set2, char *set3, char *tempSet) {
    if (command != NULL) {
        free(command);
    }
    if (set1 != NULL) {
        free(set1);
    }
    if (set2 != NULL) {
        free(set2);
    }
    if (set3 != NULL) {
        free(set3);
    }
    if (tempSet != NULL) {
        free(tempSet);
    }
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
        return stop;
    } else {
        return WRONG_INPUT;
    }
}

int checkValidInput(char *input, char *command, char *set1, char *set2, char *set3) {
    int commandType;
    if (sscanf(input, "%s", command) != 1) {
        printf("wrong name of operand\n");
        return WRONG_INPUT;
    }
    commandType = checkCommand(command);
    size_t commandLength = strlen(command);
    if (input[commandLength] != ' ' && commandType != stop) {
        printf("miss name of the group\n");
        return WRONG_INPUT;
    }
    memmove(input, input + commandLength + 1, strlen(input) - commandLength + 1);

    switch (commandType) {
        case read_set:
            break;
        case print_set: /*1*/
            checkValidOneSets(&input, &set1);
            return commandType;
            break;
        case union_set:
        case intersect_set:
        case sub_set:
        case symdiff_set: /*3*/
            checkValidThreeSets(&input, &set1, &set2, &set3);
            return commandType;
        case stop:
            if (strlen(input) != 0) {
                printf("have input after stop\n");
                return WRONG_INPUT;
            }
            return stop;

        default:
            printf("wrong operant\n");
            return WRONG_INPUT;
    }
}

int checkValidReadSet(char **input, char **set1) {
    int value;
    char *tempSet = (char *)malloc(MAX_SIZE_NAME_INPUT * sizeof(char));
    if (tempSet == NULL) {
        printf("Memory allocation failed.\n");
        return false;
    }
    char *inputString = *input;
    char tempSetName[MAX_SIZE_NAME_INPUT];
    value = 0;
    /* Read the set name from inputString */
    if (sscanf(inputString, "%s", tempSetName) != 1) {
        printf("Wrong input format.\n");
        free(tempSet);
        return false;
    }
    /*  Check if the set name is valid*/
    if (checkValidSetName(tempSetName) == false) {
        printf("Wrong input format.\n");
        free(tempSet);
        return false;
    }
    /* Copy the set name to set1*/
    strcpy(*set1, tempSetName);
    inputString+=strlen(tempSetName);
    if (*inputString != ',') {
        printf("Missing comma.\n");
        free(tempSet);
        return WRONG_INPUT;
    }
    inputString+=2;

    /* Update inputString to point to the character after the extracted set name*/
    inputString += strlen(tempSet+1); // Adjust inputString to point to the character after the extracted set name
    while (sscanf(inputString, "%d", &value) == 1) {

        if (value < 0 || value >= SET_SIZE) {
            printf("Invalid value %d.\n", value);
            free(tempSet);
            return WRONG_INPUT;
        }
        addElementToSet(tempSet, value);
        if (value >=0 && value < 10) {
            inputString++;
        }
        if (value >= 10 && value < 100) {
            inputString+=2;
        }
        if (value >= 100 && value < 128) {
            inputString+=3;
        }
        if (*inputString != ',') {
            printf("Missing comma.\n");
            free(tempSet);
            return WRONG_INPUT;
        }
        inputString++;

    }
    if (*inputString != '\0') {
        printf("have characters after the command\n");
        free(tempSet);
        return WRONG_INPUT;
    }

    free(tempSet);
    return true;
}

int checkValidOneSets(char **input, char **set1) {
    char *inputString = *input;
    char tempSet[MAX_SIZE_NAME_INPUT];
    /* Read the set name from inputString */
    if (sscanf(inputString, "%s", tempSet) != 1) {
        printf("Dont have sets.\n");
        return false;
    }
    /*  Check if the set name is valid*/
    if (checkValidSetName(tempSet) == false) {
        printf("the name of the set wrong.\n");
        return false;
    }
    /* Copy the set name to set1*/
    strcpy(*set1, tempSet);

    /* Update inputString to point to the character after the extracted set name*/
    inputString += strlen(tempSet); // Adjust inputString to point to the character after the extracted set name

    if (*inputString != '\0') {
        printf("have characters after the command over\n");
        return WRONG_INPUT;
    }

    return true;
}

int checkValidThreeSets(char **input, char **set1, char **set2, char **set3) {
    char *inputString = *input;
    char tempSet[MAX_SIZE_NAME_INPUT];
    if (sscanf(inputString, "%[^,],", tempSet) != 1) {
        printf("dont have set\n");
        return false;
    }
    if (checkValidSetName(tempSet) == false) {
        printf("wrong set name.\n");
        return false;
    }
    strcpy(*set1, tempSet);
    inputString += strlen(tempSet);
    if (*inputString != ',') {
        printf("Missing comma.\n");
        return false;
    }
    inputString += 2;
    if (sscanf(inputString, "%[^,],", tempSet) != 1) {
        printf("dont have set.\n");
        return false;
    }
    if (checkValidSetName(tempSet) == false) {
        printf("wrong set name.\n");
        return false;
    }
    strcpy(*set2, tempSet);
    inputString += strlen(tempSet);
    if (*inputString != ',') {
        printf("Missing comma.\n");
        return false;
    }
    inputString += 2;
    if (sscanf(inputString, "%s", tempSet) != 1) {
        printf("dont have set.\n");
        return false;
    }
    if (checkValidSetName(tempSet) == false) {
        printf("wrong set name.\n");
        return false;
    }
    strcpy(*set3, tempSet);
    inputString += strlen(tempSet);
    if (*inputString != '\0') {
        printf("have characters after the command over.\n");
        return false;
    }
    return true;


}
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

int checkValidSetName(char *set) {
    if (strcmp(set, "SETA") == 0 || strcmp(set, "SETB") == 0 || strcmp(set, "SETC") == 0 || strcmp(set, "SETD") == 0 ||
        strcmp(set, "SETE") == 0 || strcmp(set, "SETF") == 0) {
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

