set -e

if [ -f .env ]; then
  source .env
fi

PROJECT_DIR="project"
RELEASES_DIR="$PROJECT_DIR/releases"
SHARED_DIR="$PROJECT_DIR/shared"
DATE=$(date +"%Y%m%d%H%M%S")
NEW_RELEASE_DIR="$RELEASES_DIR/$DATE"
CURRENT_LINK="$PROJECT_DIR/current"
KEEP_RELEASES=5

if ! command -v git &> /dev/null; then
  echo "Erreur : Git n'est pas installé ou non disponible dans le PATH."
  exit 1
fi

GIT_REPO=${GIT_REPO:-""}
GIT_BRANCH=${GIT_BRANCH:-""}
GIT_SUBDIR=${GIT_SUBDIR:-""}
BUILD_COMMAND=${BUILD_COMMAND:-""}

while getopts "k:r:b:s:" option; do
  case "${option}" in
    k)
      KEEP_RELEASES=${OPTARG}
      ;;
    r)
      GIT_REPO=${OPTARG}
      ;;
    b)
      GIT_BRANCH=${OPTARG}
      ;;
    s)
      GIT_SUBDIR=${OPTARG}
      ;;
    c)
      BUILD_COMMAND=${OPTARG}
      ;;
    *)
      echo "Merci d'utilisé cette syntaxe: $0 [-k number_of_releases_to_keep] [-r git_repo] [-b git_branch] [-s git_subdir] deploy|rollback"
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

    TEMP_DIR="$PROJECT_DIR/tmp"
    mkdir -p "$TEMP_DIR"
    
    git clone --branch "$GIT_BRANCH" --depth 1 "$GIT_REPO" "$TEMP_DIR"

    if [ $? -ne 0 ]; then
      echo "Erreur lors du clonage du dépôt Git."
      rm -rf "$TEMP_DIR"
      exit 1
    fi

    if [ -d "$TEMP_DIR/$GIT_SUBDIR" ]; then
      cp -r "$TEMP_DIR/$GIT_SUBDIR" "$NEW_RELEASE_DIR/"
      echo "Le sous-dossier $GIT_SUBDIR a été copié dans $NEW_RELEASE_DIR."
    else
      echo "Erreur : Le sous-dossier $GIT_SUBDIR n'existe pas dans le dépôt."
      rm -rf "$TEMP_DIR"
      exit 1
    fi

    if [ -n "$BUILD_COMMAND" ]; then
      echo "Exécution de la commande de build : $BUILD_COMMAND"
      ($BUILD_COMMAND)
    elif [ -f "$NEW_RELEASE_DIR/clone_me/Makefile" ]; then
      echo "Exécution du Makefile trouvé."
      (cd "$NEW_RELEASE_DIR/clone_me" && make)
    fi

    rm -rf "$TEMP_DIR"

    echo "Structure finale du projet :"
    ls -R "$PROJECT_DIR"
}

rollback() {
  echo "Rollback à la version précédente"

  RELEASES=$(ls -1t "$RELEASES_DIR")

  PREVIOUS_RELEASE=$(echo "$RELEASES" | sed -n '2p')

  if [ -z "$PREVIOUS_RELEASE" ]; then
    echo "Aucune version précédente disponible pour le rollback."
    exit 1
  fi

  ln -sfn "$RELEASES_DIR/$PREVIOUS_RELEASE" "$CURRENT_LINK"
  echo "Rollback effectué. Vous utilisez maintenant la release : $PREVIOUS_RELEASE"
}

if [ "$1" == "deploy" ]; then
  deploy
elif [ "$1" == "rollback" ]; then
  rollback
else
  echo "Usage : $0 [-k number_of_releases_to_keep] [-r git_repo] [-b git_branch] [-s git_subdir] deploy|rollback"
  exit 1
fi


