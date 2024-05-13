# Idée

Créer une protection moi même pour ne pas pouvoir smasher le saved eip :
- Utilisation de nanomites : le processus fils est celui sur lequel tout se passe (les syscalls read et write essentiellement) et le père est le checker.
- Côté père : sur le call de notre fonction fille, on récupère le saved eip au début du call, et on vérifie avant de revenir que c'est bien celui qu'on avait récupéré au début.
- Côté fils : on a un buffer overflow mais le smashed eip est remplacé dans tous les cas par le non smashed à la fin de la routine donc à quoi bon.

# Mise en place des nanomites (Côté reverse)

Voir le code pour le fils mais en gros on calle des instructions en plus dans les routines pour faire nos vérifications et modifier ce qui potentiellement aurait pu être rewrite.
Côté père, le code est générique pareil, on récupère des signaux du son et sur ces signaux on prend des mesures précises.
Le fils est packé pour plus de fun hihihaha.

# Idées pour le pwn 

L'idée c'est de trouver un moyen de bypass les protections et de smash le saved rip en contournant la protection.
Pour ça, on a à notre disposition :
    1. Une routine qui va permettre un read une input user.
    2. Une possibilité de relecture du message envoyé : affichage de l'input user pour permettre des potentiels leaks.
    3. Pour s'arrêter.

Le binaire est full protection pour le summum du fun.