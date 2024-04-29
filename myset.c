
#include "set.h"

int main(void) {
    Set sets[NUM_SETS];

    int typeCommand, i;
    char input[MAX_SIZE_INPUT];
    char command[MAX_SIZE_NAME_COMMEND];
    char set1[MAX_SIZE_NAME_COMMEND];
    char set2[MAX_SIZE_NAME_COMMEND];
    char set3[MAX_SIZE_NAME_COMMEND];
    Set (*setsPtr)[NUM_SETS] = &sets;
    for (i = 0; i < NUM_SETS; i++) {
        initializeSet(&sets[i]);
    }

    printf("Hello\n");
    printf("Welcome to use Daniel's program.\n");
    printf("the program has 6 group: SETA, SETB, SETC, SETD, SETE, SETF.\n");
    printf("the program know:\n");
    while (ALWAYS) {
//        printf("1.read the numbers you enter and put all the number in the set.\n  to use read you must use with format \"read_set <SET> numbers and finish with -1\".\n"
//               "  between number must use for \',\' example \"read_set SETA, 1,2,3,4,5,6,7,8,9,10,-1\".\n");
//        printf("2.print the set you want to see.\n  to use print you must use this format \"print_set <SET>\".\n"
//               "  example \"print_set SETA\".\n");
//        printf("3.union set1 with set2 and put in set3.\n  to use union you must use this format \"union_set <SET1>, <SET2>, <SET3>\".\n");
//        printf("  for example \"union_set SETA SETB SETC\".\n");
//        printf("4.intersect set1 with set2 and put in set3.\n  to use intersect you must use this format \"intersect_set <SET1>, <SET2>, <SET3>\".\n");
//        printf("  for example \"intersect_set SETA, SETB, SETC\".\n");
//        printf("5.subtract set2 with set1 and put in set3.\n  to use subtract you must use this format \"sub_set <SET1>, <SET2>, <SET3>\".\n");
//        printf("  for example \"sub_set SETA, SETB, SETC\".\n");
//        printf("6.symmetric difference set1 with set2 and put in set3.\n  to use symmetric you must use this format \"symdiff_set <SET1>, <SET2>, <SET3>\".\n");
//        printf("  for example \"symdiff_set SETA, SETB, SETC\".\n");
//        printf("7.to exit the program you must use \"stop\".\n");
        fgets(input, sizeof(input), stdin);
        printf("you enter: %s\n", input);
        typeCommand = checkValidInput(input, command, set1, set2, set3);
        if (typeCommand == WRONG_INPUT) {
            continue;
        }
        switch (typeCommand) {
            case read_set :
            case print_set:
                setSetForOneSetCommand(typeCommand, input, set1, setsPtr);
                break;
            case union_set:
            case intersect_set:
            case sub_set:
            case symdiff_set:
                setSetForThreeSetCommand(typeCommand, set1, set2, set3, setsPtr);
                break;
            default:
                printf("stop\n");
                break;
        }

    }
}

void setSetForOneSetCommand(int commend, char *input, char *set, Set (*sets)[NUM_SETS]) {
    int index = -1;
    if (strcmp(set, "SETA") == 0) {
        index = 0;
    } else if (strcmp(set, "SETB") == 0) {
        index = 1;
    } else if (strcmp(set, "SETC") == 0) {
        index = 2;
    } else if (strcmp(set, "SETD") == 0) {
        index = 3;
    } else if (strcmp(set, "SETE") == 0) {
        index = 4;
    } else if (strcmp(set, "SETF") == 0) {
        index = 5;
    }

    if (index != -1) {
        if (commend == print_set) {
            printSet(&(*sets)[index]); // Pass the address of the set
        } else if (commend == read_set) {
            readSet(&(*sets)[index], input); // Pass the address of the set
        }
    }
}
int findIndexSet(char *set) {
    if (strcmp(set, "SETA") == 0) {
        return SETA;
    } else if (strcmp(set, "SETB") == 0) {
        return SETB;
    } else if (strcmp(set, "SETC") == 0) {
        return SETC;
    } else if (strcmp(set, "SETD") == 0) {
        return SETD;
    } else if (strcmp(set, "SETE") == 0) {
        return SETE;
    } else if (strcmp(set, "SETF") == 0) {
        return SETF;
    }
    return WRONG_INPUT;
}

void setSetForThreeSetCommand(int commend, char *set1, char *set2, char *set3, Set (*sets)[NUM_SETS]) {
    int index1 = findIndexSet(set1);
    int index2 = findIndexSet(set2);
    int index3 = findIndexSet(set3);
    if (index1 == WRONG_INPUT || index2 == WRONG_INPUT || index3 == WRONG_INPUT) {
        return;
    }
    if (commend == union_set) {
        unionSet(&(*sets)[index1], &(*sets)[index2], &(*sets)[index3]);
//    } else if (commend == intersect_set) {
//        intersectSet(&(*sets)[index1], &(*sets)[index2], &(*sets)[index3]);
//    } else if (commend == sub_set) {
//        subSet(&(*sets)[index1], &(*sets)[index2], &(*sets)[index3]);
//    } else if (commend == symdiff_set) {
//        symdiffSet(&(*sets)[index1], &(*sets)[index2], &(*sets)[index3]);
//    }

}}


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
    char tempInput[MAX_SIZE_INPUT];
    strcpy(tempInput, input);
    int commandType;
    if (sscanf(input, "%s", command) != 1) {
        printf("wrong command name\n");
        return WRONG_INPUT;
    }
    commandType = checkCommand(command);
    strcpy(tempInput, tempInput + strlen(command));
    removeSpaces(tempInput);
    switch (commandType) {
        case read_set:
            if (checkValidReadSet(tempInput, set1) == WRONG_INPUT) {
                return WRONG_INPUT;
            }
            return commandType;
        case print_set: /*1*/
            if (checkValidOneSets(tempInput, set1) == -1) {
                return WRONG_INPUT;
            }
            return commandType;

        case union_set:
        case intersect_set:
        case sub_set:
        case symdiff_set: /*3*/
            if (checkValidThreeSets(tempInput, set1, set2, set3) == -1) {
                return WRONG_INPUT;
            }
            return commandType;
        case stop:
            if (strlen(tempInput) != 0) {
                printf("Extraneous text after end of command\n");
                return WRONG_INPUT;
            }
            return commandType;
        default:
            printf("wrong command name\n");
            return WRONG_INPUT;
    }
}

int checkValidReadSet(char *input, char *set1) {
    int value;
    char *inputString = input;
    char tempSetName[MAX_SIZE_NAME_INPUT];
    char *endptr;
    value = 0;
    /* Read the set name from inputString */
    if (sscanf(inputString, "%4[^,]", tempSetName) != 1) {
        printf("missing set.\n");
        return WRONG_INPUT;
    }
    /*  Check if the set name is valid*/
    if (checkValidSetName(tempSetName) == false) {
        printf("Wrong set name.\n");
        return WRONG_INPUT;
    }
    /* Copy the set name to set1*/
    strcpy(set1, tempSetName);
    inputString += strlen(tempSetName);


    /* Update inputString to point to the character after the extracted set name*/
    if (*inputString != ',') {
        printf("Missing comma.\n");
        return WRONG_INPUT;
    }
    inputString++;
    while (ALWAYS) {
        value = strtol(inputString, &endptr, 10);
        if (inputString == endptr || (*endptr != ',' && *endptr != '\0')) {
            printf("Invalid set member - not a integer.\n");
            return WRONG_INPUT;
        }
        if (value == -1) {
            inputString += 2;
            break;
        }
        if (*(endptr) == '\0') {
            printf("List of set members must end with -1.\n");
            return WRONG_INPUT;
        }

        if (value < 0 || value >= SET_SIZE) {
            printf("Invalid set member - value out of range %d.\n", value);
            return WRONG_INPUT;
        }
        inputString += checkNumberOfDigit(value);
        if (*inputString != ',') {
            printf("Missing comma.\n");
            return WRONG_INPUT;
        }
        inputString++;


    }
    if (*inputString != '\0') {
        printf("Extraneous text after end of command\n");
        return WRONG_INPUT;
    }
    return true;
}

int checkValidOneSets(char *input, char *set1) {
    char *inputString = input;
    char tempSet[MAX_SIZE_NAME_INPUT];
    /* Read the set name from inputString */
    if (sscanf(inputString, "%4s", tempSet) != 1) {
        printf("Dont have sets.\n");
        return false;
    }
    /*  Check if the set name is valid*/
    if (checkValidSetName(tempSet) == false) {
        printf("the name of the set wrong.\n");
        return false;
    }
    /* Copy the set name to set1*/
    strcpy(set1, tempSet);

    /* Update inputString to point to the character after the extracted set name*/
    inputString += strlen(tempSet); // Adjust inputString to point to the character after the extracted set name

    if (*inputString != '\0') {
        printf("Extraneous text after end of command\n");
        return WRONG_INPUT;
    }

    return true;
}

int checkValidThreeSets(char *input, char *set1, char *set2, char *set3) {
    char *inputString = input;
    char tempSet[MAX_SIZE_NAME_INPUT];
    if (sscanf(inputString, "%4s", tempSet) != 1) {
        printf("dont have set\n");
        return WRONG_INPUT;
    }
    if (checkValidSetName(tempSet) == false) {
        printf("wrong set name.\n");
        return WRONG_INPUT;
    }
    strcpy(set1, tempSet);
    inputString += strlen(tempSet);
    if (*inputString == '\0') {
        printf("Missing parameter.\n");
        return WRONG_INPUT;
    }
    if (*inputString != ',') {
        printf("Missing comma.\n");
        return WRONG_INPUT;
    }

    inputString++;
    if (*inputString == '\0') {
        printf("Missing parameter.\n");
        return WRONG_INPUT;
    }
    if (sscanf(inputString, "%4s", tempSet) != 1) {
        printf("dont have set.\n");
        return WRONG_INPUT;
    }

    if (checkValidSetName(tempSet) == false) {
        printf("wrong set name.\n");
        return WRONG_INPUT;
    }
    strcpy(set2, tempSet);
    inputString += strlen(tempSet);
    if (*inputString == '\0') {
        printf("Missing parameter.\n");
        return WRONG_INPUT;
    }
    if (*inputString != ',') {
        printf("Missing comma.\n");
        return WRONG_INPUT;
    }
    inputString++;
    if (*inputString == '\0') {
        printf("Missing parameter.\n");
        return WRONG_INPUT;
    }
    if (sscanf(inputString, "%4s", tempSet) != 1) {
        printf("dont have set.\n");
        return WRONG_INPUT;
    }
    if (checkValidSetName(tempSet) == false) {
        printf("wrong set name.\n");
        return WRONG_INPUT;
    }
    strcpy(set3, tempSet);
    inputString += strlen(tempSet);
    if (*inputString != '\0') {
        printf("Extraneous text after end of command.\n");
        return WRONG_INPUT;
    }
    return true;


}


int checkValidSetName(char *set) {
    if (strcmp(set, "SETA") == 0 || strcmp(set, "SETB") == 0 || strcmp(set, "SETC") == 0 ||
        strcmp(set, "SETD") == 0 ||
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

// Inside the while loop of checkValidReadSet function

