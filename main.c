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
    

    fclose(fw);
    fclose(fr);
    return 0;
}