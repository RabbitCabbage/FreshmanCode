/*
    bcci.c -- Brainfuck Component Competition interpreter :)
    Version 1.2, 12/19/04
    Daniel B Cristofani
    email cristofdathevanetdotcom
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ARRAYSIZE 65536
#define CODESIZE 65536

unsigned long stackp = CODESIZE,   // stack pointer used in [] analyze
targets[CODESIZE];   // jump targets (in this simulator, '[' and ']' are treated as conditional jump)
unsigned char array[ARRAYSIZE],    // brainfuck memory
raw_code[CODESIZE],  // raw code, include # comment and empty char
code[CODESIZE];      // code for execute
unsigned long p = 0,               // the pointer of brainfuck memory
q = 0,               // the pointer of brainfuck code, like pc in riscv simulator
length,              // of code
max,                 // max.b memory position used
count = 0,           // of command executed
new_q;               // used only in preprocess
long c;                            // char variable for fgetc() / getchar()
char * filename = "";              // filename for err()
FILE * prog,                       // FILE * for brainfuck code
* input,
        * cycle;                      // FILE * for program input

void err(char * s) {
    fprintf(stderr, "Error detected at byte %lu of %s: %s!\n", q, filename, s);
    fclose(input);
    exit(1);
}

bool empty_char(unsigned char ch) {
    return ch == ' ' || ch == '\r' || ch == '\t' || ch == '\n';
}

bool valid_code_char(unsigned char ch) {
    return ch == '+' || ch == '-' || ch == '<' || ch == '>' || ch == ',' || ch == '.' || ch == '[' || ch == ']';
}

void initialize() {
    // preprocess, remove # comment and empty char, report any syntax error
    for (q = new_q = 0; q < length; q++) {
        if (raw_code[q] == '#') while (raw_code[q] != '\n' && raw_code[q] != '\0') q++; // skip all comments
        else if (empty_char(raw_code[q])) continue;
        else if (!valid_code_char(raw_code[q])) err("Syntax Error");
        else code[new_q++] = raw_code[q]; // copy to code[]
    }
    length = new_q;
    // analyze [] pair and initialize jump target, using a stack
    // you should be familiar with this since we've studied this in Data Structure course
    for (q = 0; q < length; q++) {
        if (code[q] == '[') targets[--stackp] = q;
        else if (code[q] == ']') {
            if (stackp < CODESIZE) targets[targets[q] = targets[stackp++]] = q;
            else err("Unmatched ']'");
        }
    }
    if (stackp < CODESIZE) q = targets[stackp], err("Unmatched '['");
}

int main(int argc, char ** argv) {
    if (argc > 3) err("Too many arguments");
    if (argc < 3) err("I need a program filename");
    if (!(prog  = fopen(argv[1], "r"))) err("Can't open that file");
    if (!(input = fopen(argv[2], "r"))) err("Can't open that file");
    filename = argv[1];
    length = fread(raw_code, 1, CODESIZE, prog);
    fclose(prog);
    initialize();
    for (q = p = 0; q < length; q++, count++, max = p > max ? p : max) {
        if (count == 1e9) err ("TLE") ;
        switch (code[q]) {
            case '+': ++array[p];                                      break;
            case '-': --array[p];                                      break;
            case '<': if (--p < 0)          err("Too far left");    break;
            case '>': if (++p >= ARRAYSIZE) err("Too far right");   break;
            case ',': if ((c = fgetc(input)) != EOF) array[p] = c;     break;
            case '.': putchar(array[p]);                               break;
            case '[': if (!array[p]) q = targets[q];                   break;
            case ']': if ( array[p]) q = targets[q];                   break;
            default:                        err("Syntax Error");    break;
        }
    }
    printf("Pointer: %ld\n", p);
    printf("Final memory state:\n");
    for (p = 0; p <= max; ++p) printf(" %3d", array[p]);
    printf("\n\n");
    printf("Program length: %ld.\n", length);
    printf("Commands executed: %lu.\n", count);
    printf("Memory used: %ld.\n", max + 1);

    fclose(input);
    exit(0);
}