### Filtrer et compter des lignes

Commande : ls | grep "log" | wc -l

![Exercie-1](images/ex1.png)

### Rechercher un motif

Commande : grep -H "500" *.txt > output.log

![Exercie-2-1](images/ex2_1.png)
![Exercie-2-2](images/ex2_2.png)

### Déplacer des fichiers

Commande : find -type f -name "*.png" ! -path "./images/*" -exec mv {} images/ \

![Exercie-3](images/ex3.png)
