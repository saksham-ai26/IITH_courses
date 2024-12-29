#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int b = 0;
int j = 0;
int p = 0;   
int q = 0;   
int flag = 0;
int flag2 = 0;
char branch[10] = {0};
char branch2[10] = {0};
char jump[] = "L1";
char jump2[] = "L2";



char *hexToBin(const char *hex) {
    int len = strlen(hex);
    char *bin = (char *)malloc((4 * len + 1) * sizeof(char)); 
    if (bin == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    bin[0] = '\0'; 

    for (int i = 0; i < len; i++) {
        char hexChar = hex[i];
        char *binaryChar = NULL;

        switch (hexChar) {
            case '0':
                binaryChar = "0000";
                break;
            case '1':
                binaryChar = "0001";
                break;
            case '2':
                binaryChar = "0010";
                break;
            case '3':
                binaryChar = "0011";
                break;
            case '4':
                binaryChar = "0100";
                break;
            case '5':
                binaryChar = "0101";
                break;
            case '6':
                binaryChar = "0110";
                break;
            case '7':
                binaryChar = "0111";
                break;
            case '8':
                binaryChar = "1000";
                break;
            case '9':
                binaryChar = "1001";
                break;
            case 'A':
            case 'a':
                binaryChar = "1010";
                break;
            case 'B':
            case 'b':
                binaryChar = "1011";
                break;
            case 'C':
            case 'c':
                binaryChar = "1100";
                break;
            case 'D':
            case 'd':
                binaryChar = "1101";
                break;
            case 'E':
            case 'e':
                binaryChar = "1110";
                break;
            case 'F':
            case 'f':
                binaryChar = "1111";
                break;
            default:
                fprintf(stderr, "\nInvalid hexadecimal digit %c\n", hexChar);
                free(bin); // Free allocated memory in case of an error
                exit(1);
        }
        strcat(bin, binaryChar);
    }
    return bin;
}

int bintodec(char bin[]) {
    int len = strlen(bin);
    int dec = 0; 

        for(int i = 0; i < len; i++){
            if(bin[i] == '1'){
                dec += pow(2, len-i-1);
            }
        }
    return dec;
}

int bintodecsign(char bin[]) {
    int len = strlen(bin);
    int dec = 0;
    int sign = 0;
    if(bin[0] == '1'){
        sign = 1;
        for(int i = 0; i < len; i++){
            if(bin[i] == '1'){
                bin[i] = '0';
            }
            else{
                bin[i] = '1';
            }
        }
        for(int i = len-1; i >= 0; i--){
            if(bin[i] == '0'){
                bin[i] = '1';
                break;
            }
            else{
                bin[i] = '0';
            }
        }
        int i = len - 1, j = 0;
        while(i >= 0){
            if(bin[i] == '1'){
                dec += pow(2, j);
            }
            i--;
            j++;
        }
        return -dec;
    }

    else{
        for(int i = 0; i < len; i++){
            if(bin[i] == '1'){
                dec += pow(2, len-i-1);
            }
        }
    }
    return dec;
}

void Rinstruction(char binary[]){
    char opcode[] = "0110011";
    char op[10];
    char funct3[10];
    char funct7[10];
    char rd[10];
    char rs1[10];
    char rs2[10];
    char instruction[10];
    int a = 0;
    for (int i = 0; i < 32; i++) {

        if(i < 7){
            funct7[i] = binary[i];
        }
        if(i >= 7 && i < 12){
            a = i-7;
            rs2[a] = binary[i];
        }
        if(i >= 12 && i < 17){
            a = i-12;
            rs1[a] = binary[i];
        }
        if(i >= 17 && i < 20){
            a = i-17;
            funct3[a] = binary[i];
        }
        if(i >= 20 && i < 25){
            a = i-20;
            rd[a] = binary[i];
        }
        if(i >= 25 && i < 32){
            a = i-25;
            op[a] = binary[i];
        }
    }
    funct7[7] = '\0';
    funct3[3] = '\0';
    rs1[5] = '\0';
    rs2[5] = '\0';
    rd[5] = '\0';
    op[7] = '\0';
    instruction[0] = '\0';

    

    //add
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "000") == 0 && strcmp(funct7, "0000000") == 0){
        strcpy(instruction, "add");

    }
    //sub
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "000") == 0 && strcmp(funct7, "0100000") == 0){
        strcpy(instruction, "sub");
    }
    //sll
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "001") == 0 && strcmp(funct7, "0000000") == 0){
        strcpy(instruction, "sll");
    }
    //slt
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "010") == 0 && strcmp(funct7, "0000000") == 0){
        strcpy(instruction, "slt");
    }
    //sltu
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "011") == 0 && strcmp(funct7, "0000000") == 0){
        strcpy(instruction, "sltu");
    }
    //xor
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "100") == 0 && strcmp(funct7, "0000000") == 0){
        strcpy(instruction, "xor");
    }
    //srl
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "101") == 0 && strcmp(funct7, "0000000") == 0){
        strcpy(instruction, "srl");
    }
    //sra
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "101") == 0 && strcmp(funct7, "0100000") == 0){
        strcpy(instruction, "sra");
    }
    //or
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "110") == 0 && strcmp(funct7, "0000000") == 0){
        strcpy(instruction, "or");
    }
    //and
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "111") == 0 && strcmp(funct7, "0000000") == 0){
        strcpy(instruction, "and");
    }


    int rdint = bintodec(rd);
    int rs1int = bintodec(rs1);
    int rs2int = bintodec(rs2);

    if( flag == 1 && branch != 0){
        printf("%s: %s x%d x%d x%d\n", branch, instruction, rdint, rs1int, rs2int);
        flag = 0;
        branch[0] = '\0';
    }

    else if(flag2 == 1 && branch2 != 0){
        printf("%s: %s x%d x%d x%d\n", branch2, instruction, rdint, rs1int, rs2int);
        flag2 = 0;
        branch2[0] = '\0';
    }
    else{
        printf("%s x%d x%d x%d\n", instruction, rdint, rs1int, rs2int);
    }

}

void Iinstruction(char binary[]){
    char opcode[] = "0010011";
    char op[10];
    char funct3[10];
    char rd[10];
    char rs1[10];
    char imm[15];
    char instruction[10];
    int a = 0;
    for(int i = 0; i<32 ; i++){
        if(i < 12){
            imm[i] = binary[i];
        }
        if(i >= 12 && i < 17){
            a = i-12;
            rs1[a] = binary[i];
        }
        if(i >= 17 && i < 20){
            a = i-17;
            funct3[a] = binary[i];
        }
        if(i >= 20 && i < 25){
            a = i-20;
            rd[a] = binary[i];
        }
        if(i >= 25 && i < 32){
            a = i-25;
            op[a] = binary[i];
        }
    }
    funct3[3] = '\0';
    rs1[5] = '\0';
    rd[5] = '\0';
    op[7] = '\0';
    imm[12] = '\0';
    // instruction[0] = '\0';

    char imm611[12];
    char immn6[12];
    for(int i = 0; i<=6; i++){
        imm611[i] = imm[i];
    }
    for(int i = 6; i<=11; i++){
        immn6[i-6] = imm[i];
    }
    immn6[6] = '\0';
    imm611[6] = '\0';


    //addi
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "000") == 0){
        strcpy(instruction, "addi");
    }
    //slli
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "001") == 0 && strcmp(imm611, "000000") == 0){
        strcpy(instruction, "slli");
         int immnew = bintodecsign(immn6);
    int rdint = bintodec(rd);
    int rs1int = bintodec(rs1);

    if(flag == 1 && branch != 0){
        printf("%s: %s x%d x%d %d\n", jump, instruction, rdint, rs1int, immnew);
        flag = 0;
        branch[0] = '\0';
    }

    else if(flag2 == 1 && branch2 != 0){
        printf("%s: %s x%d x%d %d\n", jump2, instruction, rdint, rs1int, immnew);
        flag2 = 0;
        branch2[0] = '\0';
    }
    else{
    printf("%s x%d x%d %d\n", instruction, rdint, rs1int, immnew);}
    return;
    }
    //slti
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "010") == 0){
        strcpy(instruction, "slti");
    }
    //sltiu
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "011") == 0){
        strcpy(instruction, "sltiu");
    }
    //xori
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "100") == 0){
        strcpy(instruction, "xori");
    }
    //srli
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "101") == 0 &&  strcmp(imm611, "000000") == 0){
        strcpy(instruction, "srli");
         int immnew = bintodecsign(immn6);
    int rdint = bintodec(rd);
    int rs1int = bintodec(rs1);

    if(flag == 1 && branch != 0){
        printf("%s: %s x%d x%d %d\n", jump, instruction, rdint, rs1int, immnew);
        flag = 0;
        branch[0] = '\0';
    }

    else if(flag2 == 1 && branch2 != 0){
        printf("%s: %s x%d x%d %d\n", jump2, instruction, rdint, rs1int, immnew);
        flag2 = 0;
        branch2[0] = '\0';
    }
    else{
    printf("%s x%d x%d %d\n", instruction, rdint, rs1int, immnew);}
    
    return;
    }
    //srai
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "101") == 0 &&  strcmp(imm611, "010000") == 0){
        strcpy(instruction, "srai");
         int immnew = bintodecsign(immn6);
    int rdint = bintodec(rd);
    int rs1int = bintodec(rs1);

    if(flag == 1 && branch != 0){
        printf("%s: %s x%d x%d %d\n", jump, instruction, rdint, rs1int, immnew);
        flag = 0;
        branch[0] = '\0';
    }

    else if(flag2 == 1 && branch2 != 0){
        printf("%s: %s x%d x%d %d\n", jump2, instruction, rdint, rs1int, immnew);
        flag2 = 0;
        branch2[0] = '\0';
    }
    else{
    printf("%s x%d x%d %d\n", instruction, rdint, rs1int, immnew);}

    return;
    }
    //ori
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "110") == 0){
        strcpy(instruction, "ori");
    }
    //andi
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "111") == 0){
        strcpy(instruction, "andi");
    }

    int immnew = bintodecsign(imm);
    int rdint = bintodec(rd);
    int rs1int = bintodec(rs1);

    if(flag == 1 && branch != 0){
        printf("%s: %s x%d x%d %d\n", jump, instruction, rdint, rs1int, immnew);
        flag = 0;
        branch[0] = '\0';
    }

    else if(flag2 == 1 && branch2 != 0){
        printf("%s: %s x%d x%d %d\n", jump2, instruction, rdint, rs1int, immnew);
        flag2 = 0;
        branch2[0] = '\0';
    }
    else{
    printf("%s x%d x%d %d\n", instruction, rdint, rs1int, immnew);}

}

void Sintruction(char binary[]){
    char opcode[] = "0100011";
    char op[10];
    char funct3[10];
    char rs1[10];
    char rs2[10];
    char imm11_5[15];
    char imm4_0[15];
    char instruction[10];
    int a = 0;
    for(int i = 0; i<32 ; i++){
        if(i < 7){
            imm11_5[i] = binary[i];
        }
        if(i >= 7 && i < 12){
            a = i-7;
            rs2[a] = binary[i];
        }
        if(i >= 12 && i < 17){
            a = i-12;
            rs1[a] = binary[i];
        }
        if(i >= 17 && i < 20){
            a = i-17;
            funct3[a] = binary[i];
        }
        if(i >= 20 && i < 25){
            a = i-20;
            imm4_0[a] = binary[i];
        }
        if(i >= 25 && i < 32){
            a = i-25;
            op[a] = binary[i];
        }
    }
    funct3[3] = '\0';
    rs1[5] = '\0';
    rs2[5] = '\0';
    op[7] = '\0';
    imm11_5[7] = '\0';
    imm4_0[5] = '\0';
    instruction[0] = '\0';

    //sb
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "000") == 0){
        strcpy(instruction, "sb");
    }

    //sh
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "001") == 0){
        strcpy(instruction, "sh");
    }

    //sw
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "010") == 0){
        strcpy(instruction, "sw");
    }

    //sd
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "011") == 0){
        strcpy(instruction, "sd");

    }


        if(flag == 1 && branch != NULL){
            strcpy(instruction, branch);
    }

    int immnew = bintodec(imm11_5);
    int immnew2 = bintodec(imm4_0);
    int rs1int = bintodec(rs1);
    int rs2int = bintodec(rs2);
   

    if(flag == 1 && branch != 0){
        printf("%s: %s x%d x%d %d(x%d)\n", branch, instruction, rs2int, immnew+immnew2, rs1int);
        flag = 0;
        branch[0] = '\0';
    }

    else if(flag2 == 1 && branch2 != 0){
        printf("%s: %s x%d x%d %d(x%d)\n", branch2, instruction, rs2int, immnew+immnew2, rs1int);
        flag2 = 0;
        branch2[0] = '\0';
    }
    else{
    printf("%s x%d %d(x%d)\n", instruction, rs2int, immnew+immnew2, rs1int);}
}

int Binstruction(char binary[]){
    char opcode[] = "1100011";
    char op[10];
    char funct3[10];
    char rs1[10];
    char rs2[10];
    char imm10_5[15];
    char imm4_1[15];
    char imm11[15];
    char imm12[15];
    int a = 0;
    char instruction[10];

    for(int i = 0; i<32 ; i++){
        if(i < 1){
            imm12[i] = binary[i];
        }
        if(i >= 1 && i < 7){
            a = i-1;
            imm10_5[a] = binary[i];
        }
        if(i >= 7 && i < 12){
            a = i-7;
            rs2[a] = binary[i];
        }
        if(i >= 12 && i < 17){
            a = i-12;
            rs1[a] = binary[i];
        }
        if(i >= 17 && i < 20){
            a = i-17;
            funct3[a] = binary[i];
        }
        if(i >= 20 && i < 24){
            a = i-20;
            imm4_1[a] = binary[i];
        }
        if(i >= 24 && i < 25){
            a = i-24;
            imm11[a] = binary[i];
        }
        if(i >= 25 && i < 32){
            a = i-25;
            op[a] = binary[i];
        }
    }
    funct3[3] = '\0';
    rs1[5] = '\0';
    rs2[5] = '\0';
    op[7] = '\0';
    imm10_5[6] = '\0';
    imm4_1[4] = '\0';
    imm11[1] = '\0';
    imm12[1] = '\0';
    instruction[0] = '\0';

    //beq
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "000") == 0){
        strcpy(instruction, "beq");
    }

    //bne
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "001") == 0){
        strcpy(instruction, "bne");
    }

    //blt
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "100") == 0){
        strcpy(instruction, "blt");
    }

    //bge
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "101") == 0){
        strcpy(instruction, "bge");
    }

    //bltu
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "110") == 0){
        strcpy(instruction, "bltu");
    }

    //bgeu
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "111") == 0){
        strcpy(instruction, "bgeu");
    }


    strcpy(branch, jump);

    strcat(imm12, imm10_5);
    strcat(imm4_1, imm11);
    strcat(imm12, imm4_1);
    int immnew = bintodec(imm12);
    int rs1int = bintodec(rs1);
    int rs2int = bintodec(rs2);
    int jumplines = immnew/4;

    if(flag == 1 && branch != 0){
        printf("%s: %s x%d x%d %s\n", branch, instruction, rs1int, rs2int, jump);
        flag = 0;
        branch[0] = '\0';
    }

    else if(flag2 == 1 && branch2 != 0){
        printf("%s: %s x%d x%d %s\n", branch2, instruction, rs1int, rs2int, jump);
        flag2 = 0;
        branch2[0] = '\0';
    }
    else{
    printf("%s x%d x%d %s\n", instruction, rs1int, rs2int, jump);}

    return jumplines;

}

int Jinstruction(char binary[]){
    char opcode[] = "1101111";
    char op[10];
    char imm20[10];
    char imm10_1[15];
    char imm11[10];
    char imm19_12[10];
    char rd[10];

    int a = 0;
    char instruction[10];

    for(int i = 0; i<32; i++){
        if(i < 1){
            imm20[i] = binary[i];
        }
        if(i >= 1 && i < 11){
            a = i-1;
            imm10_1[a] = binary[i];
        }
        if(i >= 11 && i < 12){
            a = i-11;
            imm11[a] = binary[i];
        }
        if(i >= 12 && i < 20){
            a = i-12;
            imm19_12[a] = binary[i];
        }
        if(i >= 20 && i < 25){
            a = i-20;
            rd[a] = binary[i];
        }
        if(i >= 25 && i < 32){
            a = i-25;
            op[a] = binary[i];
        }
    }
    imm20[1] = '\0';
    imm10_1[10] = '\0';
    imm11[1] = '\0';
    imm19_12[8] = '\0';
    rd[5] = '\0';
    op[7] = '\0';
    instruction[0] = '\0';
    
    //jal
    if(strcmp(op, opcode) == 0){
        strcpy(instruction, "jal");
    }

    strcpy(branch, jump2);

    strcat(imm20, imm19_12);
    strcat(imm20, imm11);
    strcat(imm20, imm10_1);

    int immnew = bintodec(imm20);

    int rdint = bintodec(rd);

    if(flag == 1 && branch != NULL){
        printf("%s: %s x%d %s\n", branch, instruction, rdint, jump2);
        flag = 0;
        branch[0] = '\0';
    }

    else if(flag2 == 1 && branch2 != NULL){
        printf("%s: %s x%d %s\n", branch2, instruction, rdint, jump2);
        flag2 = 0;
        branch2[0] = '\0';
    }
    else{
    printf("%s x%d %s\n", instruction, rdint, jump2);}
    int jumplines = immnew/2;
    return jumplines;


}

void Uformat(char binary[]){
    char opcode[] = "0110111";
    char op[10];
    char imm[20];
    char rd[10];

    int a = 0;
    char instruction[10];

    for(int i = 0; i<32; i++){
        if(i < 20){
            imm[i] = binary[i];
        }
        if(i >= 20 && i < 25){
            a = i-20;
            rd[a] = binary[i];
        }
        if(i >= 25 && i < 32){
            a = i-25;
            op[a] = binary[i];
        }
    }
    imm[20] = '\0';
    rd[5] = '\0';
    op[7] = '\0';
    instruction[0] = '\0';

    //lui
    if(strcmp(op, opcode) == 0){
        strcpy(instruction, "lui");
    }

        if(flag == 1 && branch != NULL){
        strcpy(instruction, branch);
    }

    int immnew = bintodec(imm);
    int rdint = bintodec(rd);

    if(flag == 1 && branch != NULL){
        printf("%s: %s x%d %d\n", branch, instruction, rdint, immnew);
        flag = 0;
        branch[0] = '\0';
    }

    else if(flag2 == 1 && branch2 != NULL){
        printf("%s: %s x%d %d\n", branch2, instruction, rdint, immnew);
        flag2 = 0;
        branch2[0] = '\0';
    }
    else{
    printf("%s x%d %d\n", instruction, rdint, immnew);}
}

void Iinstruction2(char binary[]){
    char opcode[] = "0000011";
    char op[10];
    char funct3[10];
    char rd[10];
    char rs1[10];
    char imm[15];
    char instruction[10];
    int a = 0;
    for(int i = 0; i<32 ; i++){
        if(i < 12){
            imm[i] = binary[i];
        }
        if(i >= 12 && i < 17){
            a = i-12;
            rs1[a] = binary[i];
        }
        if(i >= 17 && i < 20){
            a = i-17;
            funct3[a] = binary[i];
        }
        if(i >= 20 && i < 25){
            a = i-20;
            rd[a] = binary[i];
        }
        if(i >= 25 && i < 32){
            a = i-25;
            op[a] = binary[i];
        }
    }
    funct3[3] = '\0';
    rs1[5] = '\0';
    rd[5] = '\0';
    op[7] = '\0';
    imm[12] = '\0';
    instruction[0] = '\0';

    //lb
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "000") == 0){
        strcpy(instruction, "lb");
    }

    //lh
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "001") == 0){
        strcpy(instruction, "lh");
    }

    //lw
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "010") == 0){
        strcpy(instruction, "lw");
    }

    //ld
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "011") == 0){
        strcpy(instruction, "ld");
    }

    //lbu
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "100") == 0){
        strcpy(instruction, "lbu");
    }

    //lhu
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "101") == 0){
        strcpy(instruction, "lhu");
    }

    //lwu
    if(strcmp(op, opcode) == 0 && strcmp(funct3, "110") == 0){
        strcpy(instruction, "lwu");
    }


    char opcode2[10] = "1100111";
    opcode2[7] = '\0';
    //jalr
    if(strcmp(op, opcode2) == 0 && strcmp(funct3, "000") == 0){
        strcpy(instruction, "jalr");
    }

    

    int immnew = bintodecsign(imm);
    int rdint = bintodec(rd);
    int rs1int = bintodec(rs1);
    if(flag == 1 && branch != NULL){
        printf("%s: %s x%d %d(x%d)", branch,instruction, rdint, immnew, rs1int);
        flag = 0;
        branch[0] = '\0';
    }

    else if(flag2 == 1 && branch2 != NULL){
        printf("%s: %s x%d %d(x%d)", branch2,instruction, rdint, immnew, rs1int);
        flag2 = 0;
        branch2[0] = '\0';
    }
    else{
    printf("%s x%d %d(x%d)\n", instruction, rdint, immnew, rs1int);}

}


int main() {
    char *hexinput = (char *)malloc(1000);

    char input[19][8] = {
        "00432023",
        "00032203",
        "0140006f",
        "402c5b93",
        "100004b7",
        "00c50493",
        "0053b823",
        "00e58493",
        "100004b7", 
        "007201b3",        
        "0200006f",        
        "00533623",
        "40435293",
        "00533623",
        "00d60533",
        "40bb03b3",
        "100004b7",               
        "00c50493"
        };
    input[18][8] = '\0';
    int count = 0;
    int countlines = 0;
    int count2 = 0;

    
    for(int i = 0; i < 18; i++){
        if(count != 0){
            countlines++;
        }
        if(i == j && j != 0){
            flag = 1;
        }
        if(i == q && q != 0){
            flag2 = 1;
        }
        char *bin = hexToBin(input[i]);
        char opcode[10];
        
        int k = 0;
        
           
        for (int i = 25; i < 32; i++) {
        k = i-25;
        opcode[k] = bin[i];       
        }   
        opcode[7] = '\0';
        if(strcmp(opcode, "0110011") == 0){
            Rinstruction(bin);
        }
        if(strcmp(opcode, "0010011") == 0){
            Iinstruction(bin);
    }
        if(strcmp(opcode, "0100011") == 0){
            Sintruction(bin);
        }
        if(strcmp(opcode, "1100011") == 0){
            b = Binstruction(bin);
            j = i + b;
            count++;
        }
        if(strcmp(opcode, "1101111") == 0){
            p = Jinstruction(bin);
            q = i + p;
            count2++;

        }
        if(strcmp(opcode, "0110111") == 0){
            Uformat(bin);
        }
        if(strcmp(opcode, "0000011") == 0){
            Iinstruction2(bin);  
        }
        flag = 0;
        flag2 = 0;     

    
}
// Free allocated memory
    free(hexinput);

    return 0;
}







