#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define ALWAYS 1
#define SET_SIZE 128
#define MAX_SIZE_INPUT 200
#define MAX_SIZE_NAME_COMMEND 20
#define MAX_SIZE_NAME_INPUT 10
#define EXIT 0
#define WRONG_INPUT (-1)
#define SET_NAME_SIZE 4
#define NUM_SETS 6
#define SETA 0
#define SETB 1
#define SETC 2
#define SETD 3
#define SETE 4
#define SETF 5
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
/*myset.c functions*/
void initializeSet(Set *set);
int checkCommand(char *command);
int checkValidInput(char *input,char *command ,char *set1,char *set2,char *set3);
int checkValidThreeSets(char *input,char *set1, char *set2, char *set3);
int checkValidSetName(char *set);
int checkValidOneSets(char *input,char *set1);
void cleanup(char *command, char *set1, char *set2, char *set3);
void removeSpaces(char *inputString);
int checkValidReadSet(char *input, char *set1);
void setSetForOneSetCommand(int commend, char *input, char *set, Set (*sets)[NUM_SETS]);
void setSetForThreeSetCommand(int commend, char *set1, char *set2, char *set3, Set (*sets)[NUM_SETS]) ;
/*set.c functions*/
void readSet(Set *set, char *input);
void addElementToSet(Set *set, int value);
int containsElement(Set *set, int element);
void printSet(Set *set);
int checkNumberOfDigit(int num);
void unionSet(Set *set1, Set *set2, Set *result);
