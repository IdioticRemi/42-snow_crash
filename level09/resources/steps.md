```bash
$ ls -l
total 12
-rwsr-sr-x 1 flag09 level09 7640 Mar  5  2016 level09
----r--r-- 1 flag09 level09   26 Mar  5  2016 token
```

Encore un s-bit :)

```bash
$ ./level09
You need to provied only one arg.
$ ./level09 a
a
$ ./level09 aa
ab
$ ./level09 aaa
abc
$ ./level09 abc
ace
```

Bon, a priori level09 prend un arg et le transforme en decalant
les lettres par rapport a leur index

0030 -> 0153
0031 -> 0154
0831 -> 0954

ainsi il faudrait faire l'inverse pour obtenir le token,
on peut le faire en python:

```python
# coding=utf-8
# ^ Python est debile :)

# Récupérer le token en bytes ascii
def get_token():
    with open('token', 'r') as f:
        return f.read().strip()

# Décalage inverse en prenant en compte les charactere non alphabétique
def decode(token):
    return ''.join([chr(ord(c) - i) for i, c in enumerate(token)])

# Appel
print(decode(get_token()))
```

```bash
$ python3 /tmp/decode.py
f3iji1ju5yuevaus41q1afiuq
```