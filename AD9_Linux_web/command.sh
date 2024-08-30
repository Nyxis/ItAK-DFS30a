
# lister tous les fichier
ls

# lister tous les fichiers avec "logs" dans le nom
ls | grep log

# compter tous les fichiers avec "logs" dans le nom
ls | grep log | wc -l


# Affichez chaque ligne dans tous les fichiers .txt d'un répertoire qui contient les code "500"
grep -r "500" *

# écrit ces lignes dans le fichier all_five_hundred.log
grep -r "500" * > all_five_hundred.log

# déplace tous les fichiers jpeg du dossier courant dans le dossier images du dossier courant
mv ./*.jpeg images/