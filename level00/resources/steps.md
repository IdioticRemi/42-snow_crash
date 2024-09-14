Bon pour x ou y raison je vois rien d'evident dans le sujet ou dans les fichiers de level00.  
On m'a dit d'aller check la video de l'intra et effectivement il manquait un fichier...  
Il y a un fichier README dans lequel il est écrit:

`FIND this first file who can run only as flag00...`

-> On cherche donc un fichier avec pour propriétaire flag00.

`find / -user flag00 2>/dev/null`

On trouve le fichier `/usr/sbin/john` qui appartient à flag00.

`cat /usr/sbin/john` > `cdiiddwpgswtgt`

Malheureusement ce n'est pas le mdp du compte flag00.

En cherchant sur dcode comme suggerait la video de l'intra, on trouve avec la fonction de recherche de cryptage que ca peut etre par rotation/cesar.  
Le site propose de tester toutes les combinaisons de rotations possibles et propose la solution la plus logique et effectivement,  
avec un décalage de 15 on obtient:

`cdiiddwpgswtgt` -> `nottoohardhere`

je me pose pas trop de questions et je tente avec ca comme mdp pour flag00.
Bingo, c'est le bon MDP :)