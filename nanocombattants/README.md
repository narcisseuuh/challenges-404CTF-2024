# Idée

nanomites à 2 enfants :
- un premier fils qui selon le signal va xorer différemment le code de l'autre enfant (différentes suites de clés).
- un second qui fils qui lui va exécuter toute la partie intéressante : fait en plusieurs rounds faits à la main et on passe d'un round à l'autre par xoring sur le **même code** càd qu'on unpack sur un code qui est déjà bon pour passer à un autre code déjà bon.
- le père supervise tout ça et décide quelle partie xorer puis jump dessus, exécute et prend une décision selon le flag changé par cmp (selon si la comparaison passe ou pas).

# Clés d'implémentation

Idéalement l'objectif c'est 3 rounds, et surtout des rounds qui évitent les vilains petits canards qui vont vouloir m'exécuter symboliquement.... On veut un challenge pour les vaillants nanocombattants ici!
Des trucs dont il fallait se méfier : 
- les droits sur les mmap (car le second fils peut pas xorer si le code de l'autre est en mmap_private)...
- avoir les bons offsets : pour ça on scripte au maximum ce qu'on peut, j'ai généré les snippets 1 à 1 à la main parce que c'était fun mais après j'ai géré les offsets et la prise d'information dans les headers avec un script python pour que tout soit aligné et que l'idée du xorage par blocs ne devienne pas chaotique!
