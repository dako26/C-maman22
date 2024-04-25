#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ALWAYS 1
#define SET_SIZE 128
#define MAX_SIZE_INPUT 200
#define MAX_SIZE_NAME_COMMEND 20
#define MAX_SIZE_NAME_INPUT 10
#define EXIT 0
#define WRONG_INPUT (-1)
typedef struct {
    unsigned char elements[SET_SIZE / 8];
} Set;
typedef enum {
    stop,
    read_set,
    print_set,
    union_set,
    intersect_set,
    sub_set,
    symdiff_set
} CommandType;
typedef enum{
    false,
    true
}Boolean;
void initializeSet(Set *set);
int containsElement(Set *set, int element);
int checkCommand(char *command);
int checkValidInput(char *input,char *command ,char *set1,char *set2,char *set3);
int checkValidThreeSets(char **input,char **set1, char **set2, char **set3);
int checkValidSetName(char *set);
int checkValidOneSets(char **input,char **set1);

