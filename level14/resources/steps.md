```bash
$ ls -l
total 0

$ find / -user flag14 2>/dev/null

$ find / -user level14 2>/dev/null
...rien qui semble utile
```

Bon, rien du tout, je me dis donc que je vais 
devoir trouver un moyen de bypass getflag pour faire comme si j'etais flag14 (uid=3014).  

Je le recupere sur ma machine via scp et je le decompile dans ghidra.
J'y vois deja des sortes de verifications de bypass mais c'est sans interet ici.
Je continue ma lecture et je vois une serie de 'if' qui verifient chacun un uid 
different pour ensuite decoder un token comme j'avais pu voir dans l'exo precedent.  
La comparaison des uid se fait en hexadecimal, je vais donc devoir convertir 3014 en hexa, soit 0xBC6.  
Je lance une petite recherche dans ghidra et je vois que le dernier des 'if' est celui qui m'interesse.

```c++
if (_Var6 != 0xbc6) goto LAB_08048e06;
pcVar4 = (char *)ft_des("g <t61:|4_|!@IF.-62FH&G~DCK/Ekrvvdwz?v|");
fputs(pcVar4,__stream);
```

Bon, comme pour l'exo precedent, je compile un programme qui va me permettre de decoder
le token en utilisant la version decompilee de 'ft_des' que j'ai trouvee dans ghidra.

```c++
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char * ft_des(char *param_1)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  char *pcVar4;
  byte bVar5;
  uint local_20;
  int local_1c;
  int local_18;
  int local_14;
  
  bVar5 = 0;
  pcVar2 = strdup(param_1);
  local_1c = 0;
  local_20 = 0;
  do {
    uVar3 = 0xffffffff;
    pcVar4 = pcVar2;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + (uint)bVar5 * -2 + 1;
    } while (cVar1 != '\0');
    if (~uVar3 - 1 <= local_20) {
      return pcVar2;
    }
    if (local_1c == 6) {
      local_1c = 0;
    }
    if ((local_20 & 1) == 0) {
      if ((local_20 & 1) == 0) {
        for (local_14 = 0; local_14 < "0123456"[local_1c]; local_14 = local_14 + 1) {
          pcVar2[local_20] = pcVar2[local_20] + -1;
          if (pcVar2[local_20] == '\x1f') {
            pcVar2[local_20] = '~';
          }
        }
      }
    }
    else {
      for (local_18 = 0; local_18 < "0123456"[local_1c]; local_18 = local_18 + 1) {
        pcVar2[local_20] = pcVar2[local_20] + '\x01';
        if (pcVar2[local_20] == '\x7f') {
          pcVar2[local_20] = ' ';
        }
      }
    }
    local_20 = local_20 + 1;
    local_1c = local_1c + 1;
  } while( true );
}

int main () {
    printf("%s", ft_des("g <t61:|4_|!@IF.-62FH&G~DCK/Ekrvvdwz?v|"));
    
    return 0;
}
```

Je compile et je lance le programme.

```bash
$ gcc main.c
$ ./a.out 
7QiHafiNa3HVozsaXkawuYrTstxbpABHD8CPnH
```

Et voila le travail :)

Encore une fois, la meme chose est faisable dans gdb avec un jump a l'adresse de la fonction 'ft_des'

```bash
(gdb) b main
Breakpoint 1 at 0x804894a
(gdb) run
Starting program: /bin/getflag

Breakpoint 1, 0x0804894a in main ()
(gdb) disassemble
Dump of assembler code for function main:
   0x08048946 <+0>:     push   %ebp
   0x08048947 <+1>:     mov    %esp,%ebp
   0x08048949 <+3>:     push   %ebx
=> 0x0804894a <+4>:     and    $0xfffffff0,%esp
   0x0804894d <+7>:     sub    $0x120,%esp
(...)
   0x08048af8 <+434>:   call   0x80484c0 <fwrite@plt>
   0x08048afd <+439>:   call   0x80484b0 <getuid@plt>    # recup de l'uid
   0x08048b02 <+444>:   mov    %eax,0x18(%esp)           # stockage de l'uid
   0x08048b06 <+448>:   mov    0x18(%esp),%eax
# a partir d'ici on a une serie de 'if' qui verifient l'uid, je cherche donc celui qui compare a 0xbc6
   0x08048b0a <+452>:   cmp    $0xbbe,%eax
   0x08048b0f <+457>:   je     0x8048ccb <main+901>
   0x08048b15 <+463>:   cmp    $0xbbe,%eax
   0x08048b1a <+468>:   ja     0x8048b68 <main+546>
(...)
# je le trouve enfin ici et je vois que le programme jump a l'addresse 0x8048de5 si l'uid est bon
   0x08048bb6 <+624>:   cmp    $0xbc6,%eax
   0x08048bbb <+629>:   je     0x8048de5 <main+1183>
   0x08048bc1 <+635>:   jmp    0x8048e06 <main+1216>
   0x08048bc6 <+640>:   mov    0x804b060,%eax
(...)
# on peut donc jump ici pour decoder le token puisqu'il est print juste apres avoir ete decode, c'est pas grave si le programme plante
   0x08048de5 <+1183>:  mov    0x804b060,%eax
   0x08048dea <+1188>:  mov    %eax,%ebx
   0x08048dec <+1190>:  movl   $0x8049220,(%esp)
   0x08048df3 <+1197>:  call   0x8048604 <ft_des>
   0x08048df8 <+1202>:  mov    %ebx,0x4(%esp)
   0x08048dfc <+1206>:  mov    %eax,(%esp)
   0x08048dff <+1209>:  call   0x8048530 <fputs@plt>
(...)
   0x08048eca <+1412>:  leave
   0x08048ecb <+1413>:  ret
End of assembler dump.
# du coup un petit jump et ca ne loupe pas :)
(gdb) jump *0x8048de5
Continuing at 0x8048de5.
7QiHafiNa3HVozsaXkawuYrTstxbpABHD8CPnHJ
*** stack smashing detected ***: /bin/getflag terminated
(...)
```