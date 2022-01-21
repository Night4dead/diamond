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
    int start = c - 65;
    return start;
}

int midspaces(int alpha){
    return alpha + ( alpha > 1 ? alpha - 1 : 0);
}

void genLine(char *diamond, char c, int space){
    int mid = midspaces(spaces(c));
    char *spacer = " ";
    char ch[1] = " "; 
    ch[0] = c;
    char *line;
    line = malloc(sizeof(char)*( strlen(TAB) + mid + 1));

    strcpy(line, TAB);
    for(int i=0; i < space; i++){
        strcat(line, spacer);
    }
    strcat(line, ch);
    if(mid > 0){
        for(int i=0; i < mid; i++){
            strcat(line, spacer);
        }
        strcat(line, ch);
    }
    strcat(line, "\n");
    strcat(diamond, line);

    free(line);
}

/** 
 * DIAMOND
*/

void triangle(int space, char wide, char *diamond){
    int inner = 0;
    while( space > 0 ){
        char letter = 65 + inner;
        genLine(diamond, letter, space);
        space = space - 1;
        inner = inner + 1;
    }
}

void reverseTriangle(int space, char wide, char *diamond){
    int inner = spaces(wide) - 1;
    int front = 1;
    while( front < space + 1 ) {
        char letter = 65 + inner;
        genLine(diamond, letter, front + 1);
        inner = inner - 1;
        front = front + 1;
    }
}

void getDiamond(char wide){
    char *diamond;
    int space = spaces(wide) + 1;
    int mid = midspaces(space-1);

    diamond = malloc(sizeof(char) * (strlen(TAB) + 2 + mid + strlen("\n")) * mid );

    triangle(space, wide, diamond);
    reverseTriangle(space-1, wide, diamond);

    int res = printf("\n%s\n",diamond);

    if(res == 0){
        free(diamond);
    }
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
    getDiamond(letter);
    return 0;
}