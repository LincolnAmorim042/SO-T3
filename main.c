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
                
                return;
            }
            else if(strcmp(str, "andi") == 0) {
                
                return;
            }
            else if(strcmp(str, "or") == 0) {
                            
                return;
            }
            else if(strcmp(str, "xor") == 0) {
                
                return;
            }
            else if(strcmp(str, "ori") == 0) {
                
                return;
            }
            else if(strcmp(str, "slt") == 0) {
                
                return;
            }
            else if(strcmp(str, "slti") == 0) {
                
                return;
            }
            else if(strcmp(str, "sll") == 0) {
                
                return;
            }
            else if(strcmp(str, "srl") == 0) {
                
                return;
            }
            else if (strcmp(str, "add") == 0) {
                
                return;
            }
            else if (strcmp(str, "addi") == 0) {
                
                return;
            }
            else if (strcmp(str, "sub") == 0) {
                
                return;
            }
            else if (strcmp(str, "mult") == 0) {
                
                return;
            }
            else if(strcmp(str, "div") == 0) {
                
                return;
            }
            
            else if(strcmp(str, "j") == 0) {
                
                return;
            }
            else if(strcmp(str, "beq") == 0) {
                
                return;
            }
            else if(strcmp(str, "bne") == 0) {
                
                return;
            }
            else if(strcmp(str, "bgez") == 0) {
                
                return;
            }
            else if(strcmp(str, "bgtz") == 0) {
                
                return;
            }
            else if(strcmp(str, "lb") == 0) {
                
                return;
            }
            else if(strcmp(str, "sb") == 0) {
                
                return;
            }
            else if(strcmp(str, "lw") == 0) {
                
                return;
            }
            else if(strcmp(str, "sw") == 0) {
                
                return;
            }
            else if(strcmp(str, "lui") == 0) {
                
                return;
            }
            else if(strcmp(str, "readb") == 0) {
                
                return;
            }
            else if(strcmp(str, "writeb") == 0) {
                
            }
        }
    } else {
        
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
