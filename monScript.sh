PROJECT_DIR="project"
RELEASES_DIR="$PROJECT_DIR/releases"
SHARED_DIR="$PROJECT_DIR/shared"
DATE=$(date +"%Y%m%d%H%M%S")
NEW_RELEASE_DIR="$RELEASES_DIR/$DATE"
CURRENT_LINK="$PROJECT_DIR/current"
KEEP_RELEASES=5

while getopts "k:" option; do
  case "${option}" in
    k)
      KEEP_RELEASES=${OPTARG}
      ;;
    *)
      echo "Merci d'utilisé cette syntaxe: $0 [-k number_of_releases_to_keep]"
      exit 1
      ;;
  esac
done

shift $((OPTIND - 1))

deploy() {
    echo "Date: $DATE"

    echo "Création de la structure de dossiers"
    mkdir -p "$SHARED_DIR/lib"
    mkdir -p "$RELEASES_DIR"

    if [ ! -f "$SHARED_DIR/mysupersecretproductionconfigfile.yaml" ]; then
    touch "$SHARED_DIR/mysupersecretproductionconfigfile.yaml"
    echo "Fichier mysupersecretproductionconfigfile.yaml créé dans shared."
    fi

    if [ ! -d "$SHARED_DIR/lib/thecompanylegacynotversionnedlibrary" ]; then
    mkdir "$SHARED_DIR/lib/thecompanylegacynotversionnedlibrary"
    echo "Répertoire thecompanylegacynotversionnedlibrary créé dans shared/lib."
    fi

    mkdir "$NEW_RELEASE_DIR"
    echo "Nouveau dossier de release créé : $NEW_RELEASE_DIR"

    echo "Création des liens symboliques vers les fichiers dans shared"

    find "$SHARED_DIR" -type f | while read -r file; do
    relative_path="${file#$SHARED_DIR/}"

    mkdir -p "$NEW_RELEASE_DIR/$(dirname "$relative_path")"
    
    ln -s "$file" "$NEW_RELEASE_DIR/$relative_path"
    done

    mkdir -p "$NEW_RELEASE_DIR/lib"
    echo "Création du lien symbolique pour le dossier thecompanylegacynotversionnedlibrary"
    ln -s "$SHARED_DIR/lib/thecompanylegacynotversionnedlibrary" "$NEW_RELEASE_DIR/lib/thecompanylegacynotversionnedlibrary"

    echo "Mise à jour du lien symbolique 'current'"
    ln -sfn "$NEW_RELEASE_DIR" "$CURRENT_LINK"

    echo "Conservation des $KEEP_RELEASES dernières releases"
    RELEASES=$(ls -1t "$RELEASES_DIR")
    OLD_RELEASES=$(echo "$RELEASES" | tail -n +$(($KEEP_RELEASES + 1)))

    for RELEASE in $OLD_RELEASES; do
    rm -rf "$RELEASES_DIR/$RELEASE"
    echo "Release supprimée : $RELEASES_DIR/$RELEASE"
    done

    echo "Structure finale du projet :"
    ls -R "$PROJECT_DIR"
}

rollback() {
  echo "Rollback à la version précédente"

  # Récupérer la liste des releases triées par ordre décroissant (la première est la plus récente)
  RELEASES=$(ls -1t "$RELEASES_DIR")

  # Récupérer la deuxième release (la première étant celle actuellement utilisée)
  PREVIOUS_RELEASE=$(echo "$RELEASES" | sed -n '2p')

  if [ -z "$PREVIOUS_RELEASE" ]; then
    echo "Aucune version précédente disponible pour le rollback."
    exit 1
  fi

  # Afficher la version vers laquelle on effectue le rollback
  ln -sfn "$RELEASES_DIR/$PREVIOUS_RELEASE" "$CURRENT_LINK"
  echo "Rollback effectué. Vous utilisez maintenant la release : $PREVIOUS_RELEASE"
}

# Vérifier la commande (deploy ou rollback)
if [ "$1" == "deploy" ]; then
  deploy
elif [ "$1" == "rollback" ]; then
  rollback
else
  echo "Usage : $0 [-k number_of_releases_to_keep] deploy|rollback"
  exit 1
fi


