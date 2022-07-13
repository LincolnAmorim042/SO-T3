#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


struct s_regs{
int32_t r[16];
uint32_t ir;
uint32_t pc;
uint32_t base;
uint32_t limit;
uint8_t mode;
};

void getop(char* str,FILE *f){
    char* pt;
    char tx2[50];
    memset(tx2,0,50);
    if (strcmp(str,"syscall")!=0){
        if (fscanf(f, "%s", tx2) != EOF) {
            pt=strtok(tx2, ",");
            if(strcmp(str, "and") == 0) {
                oprt.tipo = r;
                oprt.op = 0;
                oprt.func = 0x24;
                oprt.shamp = 0;
                instR3(pt);
                return;
            }
            else if(strcmp(str, "andi") == 0) {
                oprt.tipo = i;
                oprt.op = 12;
                instI3ts(pt);
                return;
            }
            else if(strcmp(str, "or") == 0) {
                oprt.tipo = r;
                oprt.op = 0;
                oprt.func = 0x25;
                oprt.shamp = 0;
                instR3(pt);
                return;
            }
            else if(strcmp(str, "xor") == 0) {
                oprt.tipo = r;
                oprt.op = 0;
                oprt.func = 0x26;
                oprt.shamp = 0;
                instR3(pt);
                return;
            }
            else if(strcmp(str, "ori") == 0) {
                oprt.tipo = i;
                oprt.op = 13;
                instI3ts(pt);
                return;
            }
            else if(strcmp(str, "slt") == 0) {
                oprt.tipo = r;
                oprt.op = 0;
                oprt.func = 0x2a;
                oprt.shamp = 0;
                instR3(pt);
                return;
            }
            else if(strcmp(str, "slti") == 0) {
                oprt.tipo = i;
                oprt.op = 10;
                instI3ts(pt);
                return;
            }
            else if(strcmp(str, "sll") == 0) {
                oprt.tipo = r;
                oprt.op = 0;
                oprt.func = 0x00;
                oprt.s = 0;
                int i;
                if((i=pulaIni(pt))>=0)pt=pt+i;
                oprt.d = (u_int8_t) atoi(pt);

                pt = strtok(NULL,",");
                if((i=pulaIni(pt))>=0)pt=pt+i;
                oprt.t = (u_int8_t) atoi(pt);

                pt= strtok(NULL,",");
                if((i=pulaIni(pt))>=0)pt=pt+i;
                oprt.shamp = (u_int8_t) atoi(pt);
                return;
            }
            else if(strcmp(str, "srl") == 0) {
                oprt.tipo = r;
                oprt.op = 0;
                oprt.func = 0x02;
                oprt.s = 0;
                int i;
                if((i=pulaIni(pt))>=0)pt=pt+i;
                oprt.d = (u_int8_t) atoi(pt);

                pt = strtok(NULL,",");
                if((i=pulaIni(pt))>=0)pt=pt+i;
                oprt.t = (u_int8_t) atoi(pt);

                pt = strtok(NULL,",");
                if((i=pulaIni(pt))>=0)pt=pt+i;
                oprt.shamp = (u_int8_t) atoi(pt);
                return;
            }
            else if (strcmp(str, "add") == 0) {
                oprt.tipo = r;
                oprt.op = 0;
                oprt.func = 0x20;
                oprt.shamp = 0;
                instR3(pt);
                return;
            }
            else if (strcmp(str, "addi") == 0) {
                oprt.tipo = i;
                oprt.op = 8;
                instI3ts(pt);
                return;
            }
            else if (strcmp(str, "sub") == 0) {
                oprt.tipo = r;
                oprt.op = 0;
                oprt.func = 0x22;
                oprt.shamp = 0;
                instR3(pt);
                return;
            }
            else if (strcmp(str, "mult") == 0) {
                oprt.tipo = r;
                oprt.op = 0;
                oprt.func = 0x18;
                oprt.shamp = 0;
                instR2(pt);
                return;
            }
            else if(strcmp(str, "div") == 0) {
                oprt.tipo = r;
                oprt.op = 0;
                oprt.func = 0x1a;
                oprt.shamp = 0;
                instR2(pt);
                return;
            }
            
            else if(strcmp(str, "j") == 0) {
                oprt.tipo = j;
                oprt.op = 2;
                oprt.end = atoi(pt);
                return;
            }
            else if(strcmp(str, "beq") == 0) {
                oprt.tipo = i;
                oprt.op = 4;
                instI3st(pt);
                return;
            }
            else if(strcmp(str, "bne") == 0) {
                oprt.tipo = i;
                oprt.op = 5;
                instI3st(pt);
                return;
            }
            else if(strcmp(str, "bgez") == 0) {
                oprt.tipo = i;
                oprt.op = 1;
                oprt.t = 1;
                int i;
                if((i=pulaIni(pt))>=0)pt=pt+i;
                oprt.s = (u_int8_t) atoi(pt);

                pt = strtok(NULL,",");
                oprt.imed = (u_int8_t) atoi(pt);
                return;
            }
            else if(strcmp(str, "bgtz") == 0) {
                oprt.tipo = i;
                oprt.op = 7;
                oprt.t = 0;
                int i;
                if((i=pulaIni(pt))>=0)pt=pt+i;
                oprt.s = (u_int8_t) atoi(pt);

                pt = strtok(NULL,",");
                oprt.imed = (u_int8_t) atoi(pt);
                return;
            }
            else if(strcmp(str, "lb") == 0) {
                oprt.tipo = i;
                oprt.op = 32;
                int i;
                if((i=pulaIni(pt))>=0)pt=pt+i;
                oprt.t = (u_int8_t) atoi(pt);
                pt = strtok(NULL,",");
                pt = strtok(pt,"(");
                oprt.imed = atoi(pt);
                pt = strtok(NULL,"(");
                limpaString(&pt);
                pt = pt+pulaIni(pt);
                oprt.s = atoi(pt);
                return;
            }
            else if(strcmp(str, "sb") == 0) {
                oprt.tipo = i;
                oprt.op = 40;
                int i;
                if((i=pulaIni(pt))>=0)pt=pt+i;
                oprt.t = (u_int8_t) atoi(pt);
                pt = strtok(NULL,",");
                pt = strtok(pt,"(");
                oprt.imed = atoi(pt);
                pt = strtok(NULL,"(");
                limpaString(&pt);
                pt = pt+pulaIni(pt);
                oprt.s = atoi(pt);
                return;
            }
            else if(strcmp(str, "lw") == 0) {
                oprt.tipo = i;
                oprt.op = 35;
                int i;
                if((i=pulaIni(pt))>=0)pt=pt+i;
                oprt.t = (u_int8_t) atoi(pt);
                pt = strtok(NULL,",");
                pt = strtok(pt,"(");
                oprt.imed = atoi(pt);
                pt = strtok(NULL,"(");
                limpaString(&pt);
                pt = pt+pulaIni(pt);
                oprt.s = atoi(pt);
                return;
            }
            else if(strcmp(str, "sw") == 0) {
                oprt.tipo = i;
                oprt.op = 43;
                int i;
                if((i=pulaIni(pt))>=0)pt=pt+i;
                oprt.t = (u_int8_t) atoi(pt);
                pt = strtok(NULL,",");
                pt = strtok(pt,"(");
                oprt.imed=atoi(pt);
                pt = strtok(NULL,"(");
                limpaString(&pt);
                pt = pt+pulaIni(pt);
                oprt.s = atoi(pt);
                return;
            }
            else if(strcmp(str, "lui") == 0) {
                oprt.tipo = i;
                oprt.op = 15;
                int i;
                if((i=pulaIni(pt))>=0)pt=pt+i;
                oprt.t =(u_int8_t) atoi(pt);
                pt= strtok(NULL,",");
                oprt.imed = atoi(pt);
                oprt.s = 0;
                return;
            }
            else if(strcmp(str, "readb") == 0) {
                oprt.tipo = j;
                oprt.op = 60;
                oprt.end = 0;
                return;
            }
            else if(strcmp(str, "writeb") == 0) {
                oprt.tipo = j;
                oprt.op = 61;
                oprt.end = 0;
            }
        }
    } else {
        oprt.op = 0;
        oprt.end = 12;
        oprt.tipo = j;
    }
}

int main(int argv, char **argc) {
    int32_t inst;
    FILE *fr, *fw;

    if(argv != 2){
        perror("uso: nomearquivo.bin\n");
        return 1;
    }
    fr = fopen(argc[1], "r");
    if (fr == NULL) {
        perror("Arquivo nao encontrado\n");
        return 1;
    }
    fw = fopen("sim.out","w");
    
    while (fscanf(fr, "%s", txt) != EOF) {
        getop(txt, fr);
    }
    fclose(fw);
    fclose(fr);
    return 0;
}
