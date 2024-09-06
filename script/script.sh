#!/bin/bash
# Version
version="1.0.0"

# Variables par défaut
verbose=false
quiet=false
no_interaction=false
env=false

# Vérifie si le fichier .env existe
if [ -f .env ]; then
  export $(grep -v '^#' .env | xargs)
  read -p ".env détecté, voulez-vous l'utiliser ? (y/n) " reponse
  if [ "$reponse" = "y" ]; then
      env=true
  else
      echo "Utilisation de variables par défaut"
  fi
else
  echo ".env file not found!"
  exit 1
fi

echo $BRANCH

# Fonction d'affichage d'aide
show_help() {
    echo "Usage: $0 [options] [command]"
    echo ""
    echo "Options disponibles :"
    echo "  -h, --help            Affiche les commandes et options disponibles"
    echo "  -v, --verbose         Affiche des messages de debug"
    echo "  -q, --quiet           Désactive l'affichage de tous les messages à l'exception des prompts"
    echo "  -n, --no-interaction  Désactive les prompts et résout automatiquement l'option par défaut (Yes)"
    echo "  -V, --version         Affiche la version du script (actuellement : $version)"
    echo ""
    echo "Commandes :"
    echo "  build                 Exécute le Makefile, s'il existe"
    echo "  deploy                Déploie le projet et git clone"
    echo "  rollback              Rollback vers la version précédente"
    echo "  ping                  Affiche 'pong'"
}

# Fonctions logiques pour les messages
log_message() {
    if [ "$quiet" = false ]; then
        echo "$@"
    fi
}

log_debug() {
    if [ "$verbose" = true ]; then
        echo "DEBUG: $@"
    fi
}

# Fonctions du script
build() {
    dossiers=$(ls -td project/releases/*/ | head -n 1)
    echo "$dossiers"
    last_folder=$(echo "$dossiers" | tail -n 1)
    find_make=$(find "$last_folder" -iname "Makefile")
    if [ -n "$find_make" ]; then
        echo "Makefile trouvé"
        if [ "$no_interaction" = true ]; then
            reponse="y"
        else
            read -p "Voulez-vous exécuter le Makefile ? (y/n) " reponse
        fi
        if [ "$reponse" = "y" ]; then
            makefile_dir=$(dirname "$find_make")
            make -C "$makefile_dir"
        else
            echo "Exécution du Makefile annulée"
        fi
    else
        echo "Makefile non trouvé"
    fi
}

gitVerif() {
    if git --version > /dev/null 2>&1; then
        echo "Git est installé"
        return 0
    else
        echo "Git n'est pas installé"
        if [ "$no_interaction" = true ]; then
            reponse="y"
        else
            read -p "Voulez-vous installer Git ? (y/n) " reponse
        fi
        if [ "$reponse" = "y" ]; then
            sudo apt-get install git
            echo "Installation de Git terminée"
            return 0
        else
            echo "Installation de Git annulée"
            return 1
        fi
    fi
}

gitClone() {
    if [ "$no_interaction" = true ]; then
        reponse="branche"
    else
        read -p "Cloner une branche ou un dossier ? (branche/dossier) " reponse
    fi
    if [ "$reponse" = "branche" ]; then
        gitCloneBranch
    elif [ "$reponse" = "dossier" ]; then
        gitCloneFolder
    else
        echo "Réponse invalide"
    fi
}

gitCloneBranch() {
    if [ "$no_interaction" = true ]; then
        gitBranch="main"
        git clone -b "$gitBranch" "$GIT_LINK" project/releases/"$date"
    elif [ "$env" = true ]; then
    echo "BRANCH : $BRANCH"
        git clone -b "$BRANCH" "$GIT_LINK" project/releases/"$date"
    else
        read -p "Entrez le lien du dépôt: " GIT_LINK
        read -p "Entrez le nom de la branche: " gitBranch
        git clone -b "$gitBranch" "$GIT_LINK" project/releases/"$date"
    fi
}

gitCloneFolder() {
    mkdir -p project/releases/temp
    if [ "$no_interaction" = true ] ; then
        git clone "$GIT_LINK" project/releases/temp
        link_folder=$(find project/releases/temp -type d -name "$GET_FILE")
    else
        read -p "Entrez le lien du dépôt: " git_link
        git clone "$git_link" project/releases/temp
        read -p "Entrez le nom du dossier: " gitFolder
        link_folder=$(find project/releases/temp -type d -name "$gitFolder")
    fi

    mv "$link_folder" project/releases/"$date"
    rm -rf project/releases/temp
}

deploy() {
    if gitVerif; then
        date=$(date +"%Y%m%d%H%M%S")
        mkdir -p project/releases/"$date"
        mkdir -p project/shared

        if [ -L current ]; then
            rm current
        fi
        ln -s project/releases/"$date" current

        # Limiter à 5 releases
        dossiers=$(ls -td project/releases/*/ | xargs -n 1 basename)
        count=$(echo "$dossiers" | wc -l)
        while [ $count -gt 5 ]; do
            old_folder=$(echo "$dossiers" | tail -n 1)
            echo "Suppression du dossier : $old_folder"
            rm -rf "project/releases/$old_folder"
            dossiers=$(ls -td project/releases/*/ | xargs -n 1 basename)
            count=$(echo "$dossiers" | wc -l)
        done

        gitClone

        if [ -d "project/shared" ] && [ "$(ls -A project/shared)" ]; then
            cp -r "project/shared/." project/releases/"$date"
        fi
    else
        echo "Git non disponible"
    fi
}

rollback() {
    releases=$(ls -td project/releases/*/ | xargs -n 1 basename)
    count=$(echo "$releases" | wc -l)
    if [ "$count" -lt 2 ]; then
        echo "Erreur : pas assez de releases pour un rollback."
        exit 1
    fi
    previous_release=$(echo "$releases" | head -n 2 | tail -n 1)
    if [ -L current ]; then
        rm current
    fi
    ln -s project/releases/"$previous_release" current
    echo "Rollback effectué vers la version : $previous_release"
}

# Commande principale
if [ "$1" = "deploy" ]; then
    deploy
elif [ "$1" = "rollback" ]; then
    rollback
elif [ "$1" = "build" ]; then
    build
elif [ "$1" = "ping" ]; then
    echo "pong"
elif [ "$1" = "-V" ] || [ "$1" = "--version" ]; then
    echo "Version du script : $version"
elif [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    show_help
elif [ "$1" = "-v" ] || [ "$1" = "--verbose" ]; then
    verbose=true
elif [ "$1" = "-q" ] || [ "$1" = "--quiet" ]; then
    quiet=true
elif [ "$1" = "-n" ] || [ "$1" = "--no-interaction" ]; then
    no_interaction=true
    deploy
    build
else
    echo "Commande inconnue. Utiliser -h ou --help pour afficher les commandes disponibles."
fi
