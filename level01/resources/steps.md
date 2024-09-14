Pas de fichier ou autre dans le home, mais en regardant `/bin/passwd` par curiosite je vois que `flag01` differe des autres:

```
...
flag00:x:3000:3000::/home/flag/flag00:/bin/bash
flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash -- ICI
flag02:x:3002:3002::/home/flag/flag02:/bin/bash
flag03:x:3003:3003::/home/flag/flag03:/bin/bash
flag04:x:3004:3004::/home/flag/flag04:/bin/bash
flag05:x:3005:3005::/home/flag/flag05:/bin/bash
flag06:x:3006:3006::/home/flag/flag06:/bin/bash
flag07:x:3007:3007::/home/flag/flag07:/bin/bash
flag08:x:3008:3008::/home/flag/flag08:/bin/bash
flag09:x:3009:3009::/home/flag/flag09:/bin/bash
flag10:x:3010:3010::/home/flag/flag10:/bin/bash
flag11:x:3011:3011::/home/flag/flag11:/bin/bash
flag12:x:3012:3012::/home/flag/flag12:/bin/bash
flag13:x:3013:3013::/home/flag/flag13:/bin/bash
flag14:x:3014:3014::/home/flag/flag14:/bin/bash
```

La video de presentation du projet sur l'intra nous a parle d'un outil, 'john' qui est aussi mysterieusement le nom du fichier de l'exo precedent...

On peut donc essayer de le lancer pour voir ce qu'il fait (le contenu de test.txt est juste `42hDRfypTqqnw`)

```bash
$ john test.txt
Loaded 1 password hash (descrypt, traditional crypt(3) [DES 128/128 SSE2-16])
Will run 16 OpenMP threads
Press 'q' or Ctrl-C to abort, almost any other key for status
abcdefg          (?)
1g 0:00:00:00 100% 2/3 25.00g/s 1638Kp/s 1638Kc/s 1638KC/s 123456..Dneirfts
Use the "--show" option to display all of the cracked passwords reliably
Session completed
```

On teste donc `abcdefg` comme mot de passe pour flag01

Ca fonctionne!