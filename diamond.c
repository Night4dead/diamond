#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char *TITLE="  _____  _                                 _                   \n" 
            " |  __ \\(_)                               | |                  \n" 
            " | |  | |_  __ _ _ __ ___   ___  _ __   __| |                  \n" 
            " | |  | | |/ _` | '_ ` _ \\ / _ \\| '_ \\ / _` |                  \n" 
            " | |__| | | (_| | | | | | | (_) | | | | (_| |                  \n" 
            " |_____/|_|\\__,_|_| |_| |_|\\___/|_| |_|\\__,_|                  \n" 
            "   _____                           _                           \n" 
            "  / ____|                         | |                          \n" 
            " | |  __  ___ _ __   ___ _ __ __ _| |_ ___  _ __               \n" 
            " | | |_ |/ _ \\ '_ \\ / _ \\ '__/ _` | __/ _ \\| '__|              \n"
            " | |__| |  __/ | | |  __/ | | (_| | || (_) | |                 \n"
            "  \\_____|\\___|_| |_|\\___|_|  \\__,_|\\__\\___/|_|                 \n";

const char *TAB="";

int DEBUG=0;

/**
 * UTILS
 */

int isAlpha(char c){
    int ascii = (int) c;
    if( ascii > 64 && ascii < 91 ){
        return 0;
    }
    if( ascii > 96 & ascii < 123 ){
        return 0;
    }
    return 1;
}

char sendMaj(char c){
    int ascii = (int) c;
    if( ascii > 96 && ascii < 123 ){
        char maj = ascii - 32;
        return maj;
    }
    return c;
}

int spaces(char c){
    int start = c - 64;
    return start;
}

/** 
 * DIAMOND
*/

void triangle(int space, char wide, char *diamond){
    char *top;
    int inner = 0;
    while( space > 0 ){
        char letter = 65 + inner;
        int loop = (letter - 65)*2 - 1;
        char *line;
        line = malloc(sizeof(char) * (strlen(TAB) + space + 1));
        strcpy(line, TAB);
        for(int i = 0; i < space; i++){
            strcat(line," ");
        }
        strcat(line,&letter);
        if( inner > 0 ){
            for( int i = 0; i < (letter - 65)*2 - 1; i++){
                strcat(line," ");
            }
            strcat(line, &letter);
        }
        strcat(line,"\n");
        printf("%s\n",line);
        space = space - 1;
        inner = inner + 1;
        strcat(diamond,line);
        free(line);
    }
}

void reverseTriangle(int maxspace, char wide, char *diamond){
    char *bottom;
    int inner = (wide - 65) - 1;
    int front = 1;
    while( maxspace > 0 ) {
        char letter = 65 + inner;
        int loop = (letter - 65)*2 - 1;
        char *line;
        line = malloc(sizeof(char) * (strlen(TAB) + maxspace + 1));
        strcpy(line, TAB);
        for(int i = 0; i < front+1; i++){
            strcat(line," ");
        }
        strcat(line, &letter);
        if(inner > 0){
            for( int i = 0; i < loop; i++){
                strcat(line," ");
            }
            strcat(line, &letter);
        }
        strcat(line,"\n");
        printf("%s\n",line);
        inner = inner - 1;
        maxspace = maxspace - 1;
        front = front + 1;
        strcat(diamond,line);
        free(line);
    }
}

char *getDiamond(char wide){
    char *diamond;
    int space = spaces(wide);
    diamond = malloc(sizeof(char) * ((strlen(TAB) + space + 1)*2*wide));
    triangle(space, wide, diamond);
    reverseTriangle(space-1, wide, diamond);
    return diamond;
}


/** 
 * INIT APP
*/

char readInput(int argc, const char *argv[]){
    if(argc < 2){
        printf("Error : invalid number of arguments");
        exit(EXIT_FAILURE);
    } 
    char c = argv[1][0];
    int isValid = isAlpha(c);
    if(isValid == 1){
        printf("Error : character is not a letter");
        exit(EXIT_FAILURE);
    }
    return sendMaj(c);
}

int main(int argc, char const *argv[]) {
    printf("%s \n", TITLE);
    char letter = readInput(argc, argv);
    char *diamond;
    diamond = getDiamond(letter);
    printf("\n%s\n",diamond);
    return 0;
}