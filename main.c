#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define max (1<<20)

struct s_regs{
    int32_t r[16];
    uint32_t ir;
    uint32_t pc;
    uint32_t base;
    uint32_t limit;
    uint8_t mode;
};

struct s_regs regs;
int bbench = 0;
void traduz( uint8_t *mem) {
    u_int16_t op = regs.ir >> 26;
    u_int8_t rs,rt;
    rs = (regs.ir<<6)>>27;
    rt = (regs.ir<<11)>>27;

    if(op!=0){
        int16_t imed;
        u_int32_t endereco;
        imed= regs.ir % (1 << 16);
        endereco= regs.ir % (1 << 26);
        switch (op) {
            case 8://addi
                regs.r[rt] = regs.r[rs] + imed;
                break;
            case 12://andi
                regs.r[rt] = (regs.r[rs]) & (imed);
                break;
            case 4://beq
                if(regs.r[rs] == regs.r[rt]) {
                    regs.pc += imed << 2;
                    bbench = 1;
                }
                break;
            case 1://bgez
                if(regs.r[rs] >= 0) {
                    regs.pc += imed << 2;
                    bbench = 1;
                }
                break;
            case 7://bgtz
                if(regs.r[rs] > 0) {
                    regs.pc += imed << 2;
                    bbench = 1;
                }
                break;
            case 5://bne
                if(regs.r[rs] != regs.r[rt]) {
                    regs.pc += imed << 2;
                    bbench = 1;
                }
                break;
            case 2://jump
                regs.pc= (regs.pc & 0xf0000000) | (endereco << 2);
                bbench = 1;
                break;
            case 32://lb
                regs.r[rt] = mem[regs.r[rs] + imed];
                break;
            case 15://lui
                regs.r[rt] = imed << 16;
                break;
            case 35://lw
                regs.r[rt] = mem[regs.r[rs] + imed];
                break;
            case 13://ori
                regs.r[rt] = regs.r[rs] | ((int32_t)imed);
                break;
            case 40://sb
                mem[regs.r[rs] + imed] = (0xff & regs.r[rt]);
                break;
            case 10://slti
                if(regs.r[rs] < imed)regs.r[rt] = 1;
                else regs.r[rt] = 0;
                break;
            case 43://sw
                *((uint32_t*) (mem + regs.r[rs] + imed))=regs.r[rt];
                break;
        }
    }else{
        u_int16_t func = regs.ir % (1 << 6);
        u_int8_t rd;
        rd = (regs.ir<<16)>>27;
        switch (func) {
            case 32://add
                regs.r[rd] = regs.r[rs] + regs.r[rt];
                break;
            case 36://and
                regs.r[rd] = (regs.r[rs]) & (regs.r[rt]);
                break;
            case 26://div
                regs.r[10] = regs.r[rs] / regs.r[rt];
                regs.r[11] = regs.r[rs] % regs.r[rt];
                break;
            case 24://mull
                regs.r[10] = regs.r[rs] * regs.r[rt];
                break;
            case 37://or
                regs.r[rd] = regs.r[rs] | regs.r[rt];
                break;
            case 0://sll
                regs.r[rd] = regs.r[rt] << ((regs.ir >> 6) % 32);
                break;
            case 42://slt
                if(regs.r[rs] < regs.r[rt])regs.r[rd]=1;
                else regs.r[rd] = 0;
                break;
            case 2://srl
                regs.r[rd] = regs.r[rt] >> ((regs.ir >> 6) % 32);
                break;
            case 34://sub
                regs.r[rd] = regs.r[rs] - regs.r[rt];
                break;
            case 38://xor
                regs.r[rd] = regs.r[rs] ^ regs.r[rt];
                break;
        }
    }
}

int main(int argc, char** argv) {
    uint8_t mem[max];
    FILE *fw, *fr;

    if(argc==2){
        if((fr=fopen(argv[1],"r"))==NULL){
            perror("erro ao abrir arquivo\n");
            return 1;
        }
    }else{
        perror("uso: arquivo.bin\n");
        return 1;
    }
    struct stat data;

    memset(mem, 0, sizeof(uint8_t)*max);
    memset(&regs, 0, sizeof (struct s_regs));
    regs.limit = (max) - 1;

    fstat(fileno(fr), &data);
    off_t size = data.st_size;
    fread(mem,size,1,fr);

    fclose(fr);

    regs.ir = *((uint32_t*) (mem + regs.pc));

    while(regs.ir != 0){
        traduz(mem);
        if(bbench == 0)regs.pc+=4;
        else bbench = 0;
        regs.ir = *((uint32_t*) (mem + regs.pc));
    }
    fw=fopen("sim.out","w");

    fwrite(&regs, sizeof(struct s_regs), 1, fw);
    uint32_t soma = 0;

    for(int i =0;i<max/4;i+=4){
        soma += *((uint32_t *)(mem+i));
    }
    fwrite(&soma,sizeof (int),1,fw);
    
    fclose(fw);
    return 0;
}