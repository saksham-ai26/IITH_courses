#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct instruction {
    char opcode[16];
    char destination[16];
    char source1[16];
    char source2[16];
};

void change_alias(char* alias){
    if (strcmp(alias, "zero") == 0) {
        strcpy(alias, "x0");
    }
    else if (strcmp(alias, "ra") == 0) {
        strcpy(alias, "x1");
    }
    else if (strcmp(alias, "sp") == 0) {
        strcpy(alias, "x2");
    }
    else if (strcmp(alias, "gp") == 0) {
        strcpy(alias, "x3");
    }
    else if (strcmp(alias, "tp") == 0) {
        strcpy(alias, "x4");
    }
    else if (strcmp(alias, "t0") == 0) {
        strcpy(alias, "x5");
    }
    else if (strcmp(alias, "t1") == 0) {
        strcpy(alias, "x6");
    }
    else if (strcmp(alias, "t2") == 0) {
        strcpy(alias, "x7");
    }
    else if (strcmp(alias, "s0") == 0 || strcmp(alias, "fp") == 0) {
        strcpy(alias, "x8");
    }
    else if (strcmp(alias, "s1") == 0) {
        strcpy(alias, "x9");
    }
    else if (strcmp(alias, "a0") == 0) {
        strcpy(alias, "x10");
    }
    else if (strcmp(alias, "a1") == 0) {
        strcpy(alias, "x11");
    }
    else if (strcmp(alias, "a2") == 0) {
        strcpy(alias, "x12");
    }
    else if (strcmp(alias, "a3") == 0) {
        strcpy(alias, "x13");
    }
    else if (strcmp(alias, "a4") == 0) {
        strcpy(alias, "x14");
    }
    else if (strcmp(alias, "a5") == 0) {
        strcpy(alias, "x15");
    }
    else if (strcmp(alias, "a6") == 0) {
        strcpy(alias, "x16");
    }
    else if (strcmp(alias, "a7") == 0) {
        strcpy(alias, "x17");
    }
    else if (strcmp(alias, "s2") == 0) {
        strcpy(alias, "x18");
    }
    else if (strcmp(alias, "s3") == 0) {
        strcpy(alias, "x19");
    }
    else if (strcmp(alias, "s4") == 0) {
        strcpy(alias, "x20");
    }
    else if (strcmp(alias, "s5") == 0) {
        strcpy(alias, "x21");
    }
    else if (strcmp(alias, "s6") == 0) {
        strcpy(alias, "x22");
    }
    else if (strcmp(alias, "s7") == 0) {
        strcpy(alias, "x23");
    }
    else if (strcmp(alias, "s8") == 0) {
        strcpy(alias, "x24");
    }
    else if (strcmp(alias, "s9") == 0) {
        strcpy(alias, "x25");
    }
    else if (strcmp(alias, "s10") == 0) {
        strcpy(alias, "x26");
    }
    else if (strcmp(alias, "s11") == 0) {
        strcpy(alias, "x27");
    }
    else if (strcmp(alias, "t3") == 0) {
        strcpy(alias, "x28");
    }
    else if (strcmp(alias, "t4") == 0) {
        strcpy(alias, "x29");
    }
    else if (strcmp(alias, "t5") == 0) {
        strcpy(alias, "x30");
    }
    else if (strcmp(alias, "t6") == 0) {
        strcpy(alias, "x31");
    }
}

bool load_type(struct instruction instructions){
        if (strcmp(instructions.opcode, "ld") == 0 ||
            strcmp(instructions.opcode, "lb") == 0 ||
            strcmp(instructions.opcode, "lw") == 0 ||
            strcmp(instructions.opcode, "lbu") == 0 ||
            strcmp(instructions.opcode, "lhu") == 0 ||
            strcmp(instructions.opcode, "lwu") == 0 ||
            strcmp(instructions.opcode, "lh") == 0){
                return true;
            }
        return false;
}

bool store_type(struct instruction instructions){
        if (strcmp(instructions.opcode, "sd") == 0 ||
            strcmp(instructions.opcode, "sw") == 0 ||
            strcmp(instructions.opcode, "sh") == 0 ||
            strcmp(instructions.opcode, "sb") == 0){
                return true;
            }
        return false;
}

int main() {
    int cycles = 0;
    int count1 = 0;
    int count2 = 0;
    int final = 0;
    int flag = 0;
    char inputFileName[] = "input.txt";
    char outputFileName[] = "output.txt";

    FILE* inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("Error opening the input file.\n");
        return 1;

    }

    FILE* outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Error opening the output file.\n");
        fclose(inputFile);
        return 1;
    }
    struct instruction instructions[100];
    memset(instructions, 0, sizeof(instructions));
    int nops[100] = {0};                     
    struct instruction dummy[50];
    int numInstructions = 0;

    while (1) {
        if(final == 1){
            break;
        }
        if (fscanf(inputFile, "%s", instructions[numInstructions].opcode) == EOF) {
            break;
        }

        if (load_type(instructions[numInstructions]))
            {
                count1 = 1;
            if (fscanf(inputFile, "%s %s", instructions[numInstructions].destination, instructions[numInstructions].source1) != 2) {
                printf("Error parsing load instruction.\n");
                break;
            }
        }
        else if(store_type(instructions[numInstructions])){
            count2 = 1;
            if (fscanf(inputFile, "%s %s", instructions[numInstructions].source1, instructions[numInstructions].destination) != 2) {
                printf("Error parsing load instruction.\n");
                break;
            }
            }
        else if (fscanf(inputFile, "%s %s %s", instructions[numInstructions].destination, instructions[numInstructions].source1, instructions[numInstructions].source2) != 3) {
                printf("%d\n", numInstructions);
                printf("Error parsing other instruction.\n");
                break;
            }
        dummy[numInstructions] = instructions[numInstructions];


    int len = strlen(instructions[numInstructions].destination);
        if (len > 0 && instructions[numInstructions].destination[len - 1] == ',') {
            instructions[numInstructions].destination[len - 1] = '\0';
        }
        len = strlen(instructions[numInstructions].source1);
        if (len > 0 && instructions[numInstructions].source1[len - 1] == ',') {
            instructions[numInstructions].source1[len - 1] = '\0';
        }
        len = strlen(instructions[numInstructions].source2);
        if (len > 0 && instructions[numInstructions].source2[len - 1] == ',') {
            instructions[numInstructions].source2[len - 1] = '\0';
        }
        char dummy[20];
        if (load_type(instructions[numInstructions]) && sscanf(instructions[numInstructions].source1, "%[^(](%[^)])",
                   dummy, instructions[numInstructions].source1) == 2) {
        }
        else if(store_type(instructions[numInstructions]) && sscanf(instructions[numInstructions].destination, "%[^(](%[^)])",
                   dummy, instructions[numInstructions].destination) == 2) {
        }
    if(instructions[numInstructions].destination[0] != 'x'){
        change_alias(instructions[numInstructions].destination);
    }
    if(instructions[numInstructions].source1[0] != 'x'){
        change_alias(instructions[numInstructions].source1);
    }
    if(instructions[numInstructions].source2[0] != 'x') {
        change_alias(instructions[numInstructions].source2);
    }


        numInstructions++;

    }

    for(int j = 0; j<=numInstructions + 1; j++){
        if (j > 1) {
            int i = j - 2; 


            if(store_type(instructions[i]) || strcmp(instructions[i].destination, "x0") == 0){
                continue;
            }
            if(store_type(instructions[i+1]) && (strcmp(instructions[i].destination, instructions[i+1].source1) == 0 || strcmp(instructions[i].destination, instructions[i+1].destination) == 0 )){
                if(nops[i] == 0){
                    if(flag == 0){
                nops[i] += 2;}
                else if(flag ==1 && load_type(instructions[i])){
                    nops[i] += 1;
                }
                }
                else{
                    if(flag == 0){
                        nops[i] += 1;}
                }               
            }
            else if (strcmp(instructions[i].destination, instructions[i + 1].source1) == 0 || strcmp(instructions[i].destination, instructions[i + 1].source2) == 0){
                if(nops[i] == 0){
                    if(flag == 0){
                nops[i] += 2;}
                else if(flag ==1 && load_type(instructions[i])){
                    nops[i] += 1;
                }
                }
                else{
                    if(flag == 0){
                        nops[i] += 1;}
                }
            }
            else if (strcmp(instructions[i].destination, instructions[i+2].source1) == 0 || strcmp(instructions[i].destination, instructions[i+2].source2) == 0  ) {
                if(flag == 0){
                    nops[i+1] += 1;}
            }
        }
    }
    fprintf(outputFile, "%s\n", "Output without Data Forwarding: ");
    for (int i = 0; i < numInstructions; i++) {
        if(store_type(dummy[i])){
        fprintf(outputFile, "%s %s %s %s\n", dummy[i].opcode, dummy[i].source1, dummy[i].destination, dummy[i].source2); // Output the instruction
        }
        else{
        fprintf(outputFile, "%s %s %s %s\n", dummy[i].opcode, dummy[i].destination, dummy[i].source1, dummy[i].source2); // Output the instruction
    }
        for (int j = 0; j < nops[i]; j++) {
            fprintf(outputFile, "nop\n");
        }
    }
    for(int i = 0; i < 100; i++){
        cycles += nops[i];
    }
    cycles = cycles + numInstructions + 4;
    fprintf(outputFile, "%s %d\n", "Total Cycles:", cycles);
    cycles = 0;
    fprintf(outputFile, "%s\n", "*******************************************************************************");

    flag = 1;
    for(int i = 0; i< 100; i++){
        nops[i] = 0;
    }
    fprintf(outputFile, "%s\n", "Output With Data Forwarding: ");


 for(int j = 0; j<=numInstructions + 1; j++){
        if (j > 1) {
            int i = j - 2; 


            if(store_type(instructions[i]) || strcmp(instructions[i].destination, "x0") == 0){
                continue;
            }
            if(store_type(instructions[i+1]) && (strcmp(instructions[i].destination, instructions[i+1].source1) == 0 || strcmp(instructions[i].destination, instructions[i+1].destination) == 0 )){
                if(nops[i] == 0){
                    if(flag == 0){
                nops[i] += 2;}
                else if(flag ==1 && load_type(instructions[i])){
                    nops[i] += 1;
                }
                }
                else{
                    if(flag == 0){
                        nops[i] += 1;}
                }               
            }
            else if (strcmp(instructions[i].destination, instructions[i + 1].source1) == 0 || strcmp(instructions[i].destination, instructions[i + 1].source2) == 0){
                if(nops[i] == 0){
                    if(flag == 0){
                nops[i] += 2;}
                else if(flag ==1 && load_type(instructions[i])){
                    nops[i] += 1;
                }
                }
                else{
                    if(flag == 0){
                        nops[i] += 1;}
                }
            }
            else if (strcmp(instructions[i].destination, instructions[i+2].source1) == 0 || strcmp(instructions[i].destination, instructions[i+2].source2) == 0  ) {
                if(flag == 0){
                    nops[i+1] += 1;}
            }
        }
    }

    for (int i = 0; i < numInstructions; i++) {
        if(store_type(dummy[i])){
        fprintf(outputFile, "%s %s %s %s\n", dummy[i].opcode, dummy[i].source1, dummy[i].destination, dummy[i].source2); // Output the instruction
        }
        else{
        fprintf(outputFile, "%s %s %s %s\n", dummy[i].opcode, dummy[i].destination, dummy[i].source1, dummy[i].source2); // Output the instruction
    }
        for (int j = 0; j < nops[i]; j++) {
            fprintf(outputFile, "nop\n");
        }
    }
    for(int i = 0; i < 100; i++){
        cycles += nops[i];
    }
    cycles = cycles + numInstructions + 4;
    fprintf(outputFile, "%s %d", "Total Cycles:", cycles);
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
