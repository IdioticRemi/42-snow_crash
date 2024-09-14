```bash
$ ls -l
total 8
-rwsr-sr-x 1 flag13 level13 7303 Aug 30  2015 level13
```

Once again, un executable avec le sbit activé.

```bash
$ ./level13
UID 2013 started us but we we expect 4242
```

Bon a priori on doit etre l'utilisateur 4242 pour avoir le flag.  
Neanmoins j'aime bien demanteler les binaires pour comprendre ce qu'ils font.  
Apres ouverture du programme dans Ghidra, je vois que le programme compare l'uid avec 4242, et si c'est le cas,  
il execute une fonction de decryptage sur une string ecrite en dur. Pas tres malin...
Grace a Ghidra, j'ai pu recuperer un equivalent en code C de la fonction de decryptage.

```c++
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
```

Apres compilation et execution du programme, on obtient le flag.

```bash
$ gcc level13.c
$ ./a.out 
your token is 2A31L79asukciNyi8uppkEuSx
```

Et voila, pas besoin d'aller bidouiller pour bypass la verification d'uid.
Une autre idee serait de lancer le programme avec gdb et de modifier l'uid en cours d'execution, mais j'ai prefere la solution via ghidra :)

```bash
$ gdb -q ./level13
Reading symbols from /home/user/level13/level13...(no debugging symbols found)...done.
(gdb) b main
Breakpoint 1 at 0x804858f
(gdb) run
Starting program: /home/user/level13/level13

Breakpoint 1, 0x0804858f in main ()
(gdb) disassemble
Dump of assembler code for function main:
   0x0804858c <+0>:     push   %ebp
   0x0804858d <+1>:     mov    %esp,%ebp
=> 0x0804858f <+3>:     and    $0xfffffff0,%esp
   0x08048592 <+6>:     sub    $0x10,%esp
   0x08048595 <+9>:     call   0x8048380 <getuid@plt>
   0x0804859a <+14>:    cmp    $0x1092,%eax
   0x0804859f <+19>:    je     0x80485cb <main+63>
   0x080485a1 <+21>:    call   0x8048380 <getuid@plt>
   0x080485a6 <+26>:    mov    $0x80486c8,%edx
   0x080485ab <+31>:    movl   $0x1092,0x8(%esp)
   0x080485b3 <+39>:    mov    %eax,0x4(%esp)
   0x080485b7 <+43>:    mov    %edx,(%esp)
   0x080485ba <+46>:    call   0x8048360 <printf@plt>
   0x080485bf <+51>:    movl   $0x1,(%esp)
   0x080485c6 <+58>:    call   0x80483a0 <exit@plt>
   0x080485cb <+63>:    movl   $0x80486ef,(%esp)
   0x080485d2 <+70>:    call   0x8048474 <ft_des>
   0x080485d7 <+75>:    mov    $0x8048709,%edx
   0x080485dc <+80>:    mov    %eax,0x4(%esp)
   0x080485e0 <+84>:    mov    %edx,(%esp)
   0x080485e3 <+87>:    call   0x8048360 <printf@plt>
   0x080485e8 <+92>:    leave
   0x080485e9 <+93>:    ret
End of assembler dump.
(gdb) jump *0x080485cb
Continuing at 0x80485cb.
your token is 2A31L79asukciNyi8uppkEuSx

Program received signal SIGSEGV, Segmentation fault.
0x0804b008 in ?? ()
```

Pour recapituler avec gdb:
- On place un breakpoint sur la fonction main
- On regarde le code assembleur de la fonction main
- `[main+19]` on voit que le programme jump a l'addresse `0x80485cb` si la comparaison precedente est bonne
- On saute la verification d'uid en y allant directement
- On obtient le flag