```bash
$ ll
total 24
dr-x------ 1 level02 level02  120 Mar  5  2016 ./
d--x--x--x 1 root    users    340 Aug 30  2015 ../
-r-x------ 1 level02 level02  220 Apr  3  2012 .bash_logout*
-r-x------ 1 level02 level02 3518 Aug 30  2015 .bashrc*
----r--r-- 1 flag02  level02 8302 Aug 30  2015 level02.pcap
-r-x------ 1 level02 level02  675 Apr  3  2012 .profile*
```

Je recup le fichier pcap via la commande `scp` (execute depuis wsl2, la vm etant sur windows, le host est farfelu)

```bash
$ scp -P 4242 "level02@$(hostname).local:/home/user/level02/level02.pcap" .
```

Je l'ouvre avec une commande trouvee sur stackoverflow en toute impunite

```bash
$ tcpick -C -yP -r level02.pcap
Starting tcpick 0.2.1 at 2024-09-13 16:04 CEST
Timeout for connections is 600
tcpick: reading from level02.pcap
1      SYN-SENT       59.233.235.218:39247 > 59.233.235.223:12121
1      SYN-RECEIVED   59.233.235.218:39247 > 59.233.235.223:12121
1      ESTABLISHED    59.233.235.218:39247 > 59.233.235.223:12121
..%
..%
..&..... ..#..'..$
..&..... ..#..'..$
.. .....#.....'.........
.. .38400,38400....#.SodaCan:0....'..DISPLAY.SodaCan:0......xterm..
........"........!
........"..".....b........b.... B.
..............................1.......!
.."....
.."....
..!..........."
........"
..".............        ..
.....................

Linux 2.6.38-8-generic-pae (::ffff:10.1.1.2) (pts/10)

..wwwbugs login:
l
.l
e
.e
v
.v
e
.e
l
.l
X
.X

.
.
Password:
f
t
_
w
a
n
d
r
.
.
.
N
D
R
e
l
.
L
0
L

.
.
.
Login incorrect
wwwbugs login:
1      FIN-WAIT-1     59.233.235.218:39247 > 59.233.235.223:12121
1      TIME-WAIT      59.233.235.218:39247 > 59.233.235.223:12121
1      CLOSED         59.233.235.218:39247 > 59.233.235.223:12121
tcpick: done reading from level02.pcap

95 packets captured
1 tcp sessions detected
```

On voit donc dans ce pcap que le mdp serait `ft_wandr...NDRel.L0L`

En essayant on se rend compte que le mdp n'est pas correct

Or possiblement le mdp est `ft_wandr...NDRel.L0L` mais avec des caracteres non printables

En regardant via wireshark, on retrouve ce texte mais on voit que les points dans le mdp sont en fait le charactere `7f` (backspace)

Ainsi le mdp final serait `ft_waNDReL0L`

J'essaie et bingo, ca marche