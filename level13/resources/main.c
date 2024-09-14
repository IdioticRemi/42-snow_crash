#include <string.h>
#include <stdio.h>

typedef unsigned int uint;
typedef unsigned char byte;

extern char *strdup(const char *);
extern int printf(const char *, ...);

char * ft_des(char *param_1)
{
    char cVar1;
    char *serKey;
    uint uVar2;
    char *pcVar3;
    byte bVar4;
    uint local_20;
    int local_1c;
    int local_18;
    int local_14;

    bVar4 = 0;
    serKey = strdup(param_1);
    local_1c = 0;
    local_20 = 0;
    do {
        uVar2 = 0xffffffff;
        pcVar3 = serKey;
        do {
            if (uVar2 == 0) break;
            uVar2 = uVar2 - 1;
            cVar1 = *pcVar3;
            pcVar3 = pcVar3 + (uint)bVar4 * -2 + 1;
        } while (cVar1 != '\0');
        if (~uVar2 - 1 <= local_20) {
            return serKey;
        }
        if (local_1c == 6) {
            local_1c = 0;
        }
        if ((local_20 & 1) == 0) {
            if ((local_20 & 1) == 0) {
                for (local_14 = 0; local_14 < "0123456"[local_1c]; local_14 = local_14 + 1) {
                    serKey[local_20] = serKey[local_20] + -1;
                    if (serKey[local_20] == '\x1f') {
                        serKey[local_20] = '~';
                    }
                }
            }
        }
        else {
            for (local_18 = 0; local_18 < "0123456"[local_1c]; local_18 = local_18 + 1) {
                serKey[local_20] = serKey[local_20] + '\x01';
                if (serKey[local_20] == '\x7f') {
                    serKey[local_20] = ' ';
                }
            }
        }
        local_20 = local_20 + 1;
        local_1c = local_1c + 1;
    } while( 1 );
}

int main(void)
{
    char *uVar1;

    uVar1 = ft_des("boe]!ai0FB@.:|L6l@A?>qJ}I");
    printf("your token is %s\n",uVar1);
    return 0;
}