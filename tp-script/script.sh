KEEP=5

if [ -f .env ]; then
	source .env
fi

#Valeurs par défaut
GIT_REPO=${GIT_REPO:-"https://github.com/Yo-Ikhelef/ItAK-DFS30a.git"}
GIT_BRANCH=${GIT_BRANCH:-"main"}
GIT_FOLDER=${GIT_FOLDER:-"."}
BUILD_COMMAND=${BUILD_COMMAND:-""}
ROLLBACK_COMMAND=${ROLLBACK_COMMAND:-""}

if ! command -v git &> /dev/null
then
	echo "git n'est pas installé - sortie"
	exit 1
fi

create_project_structure() {
	PROJECT_DIR="project"
	SHARED_DIR="$PROJECT_DIR/shared"
	RELEASE_DIR="$PROJECT_DIR/releases"
	LIB_DIR="$SHARED_DIR/lib"
	
	if [ ! -d "$PROJECT_DIR" ]; then
		echo "création de l'arborescence du dossier projet..."
		mkdir -p "$LIB_DIR"
		mkdir -p "$RELEASE_DIR"
		echo "arborescence du dossier project créé avec succes"
	else
		echo "Dossier project existant, skipping initialisation"
	fi
}


#Fonction pour supprimer les anciennes releases 

cleanup_releases() {
	RELEASE_DIR="project/releases"
	
	RELEASES=($(ls -t $RELEASE_DIR))
	
	if [ ${#RELEASES[@]} -gt $KEEP ]; then
		for i in $(seq $KEEP $((${#RELEASES[@]} -1))); do
			rm -rf "$RELEASE_DIR/${RELEASES[$i]}"
		done
	fi
}


create_symlinks() {
	SHARED_DIR="project/shared"
	RELEASE_PATH=$1
	
	for file in $(find $SHARED_DIR -type f); do
		target="$RELEASE_PATH/$(basename $file)"
		ln -s "$file" "$target"
	done
	
	echo "Liens symboliques créés dans $RELEASE_PATH"
}

build_application(){
	if [ -n "$BUILD_COMMAND" ]; then
		echo "Lancement du build avec: $BUILD_COMMAND"
		$BUILD_COMMAND
		if [ $? -ne 0 ]; then 
			echo "Le build a échoué"
			exit 1
		fi
		
	else
		MAKEFILE_PATH=$(find "$RELEASE_PATH" -name "Makefile" -type f)

		if [ -n "$MAKEFILE_PATH" ]; then
			read -p "Un Makefile est disponible, souhaitez vous l'executer? (y/n)" yn
			case $yn in
				[Yy]* )
					make -C "$(dirname "$MAKEFILE_PATH")" build
                    if [ $? -ne 0 ]; then
                        echo "Le build a échoué."
                        exit 1
                    fi
					;;
				[Nn]* ) echo "Build non executé";;
				* ) echo "Répondez avec Y ou N"
			esac
		else
			echo "Aucune commande de build ou makefile détecté, resuming operation.."
		fi
	fi
}


deploy() {

create_project_structure

CURRENT_DATE=$(date +"%Y%m%d%H%M%S")

RELEASE_PATH="project/releases/$CURRENT_DATE"

mkdir -p "$RELEASE_PATH"

#sequence de clonage
echo "Clonage du dépot $GIT_REPO (branche: $GIT_BRANCH) dans le dossier $GIT_FOLDER"
git clone --branch "$GIT_BRANCH" --single-branch "$GIT_REPO" "$RELEASE_PATH"

if [ "$GIT_FOLDER" != "." ]; then
	if [ -d "$RELEASE_PATH/$GIT_FOLDER" ]; then
		mkdir -p "$RELEASE_PATH/temp"
		mv "$RELEASE_PATH/$GIT_FOLDER" "$RELEASE_PATH/temp/"
		
		find "$RELEASE_PATH" -mindepth 1 -maxdepth 1 ! -name "temp" -exec rm -rf {} +
		
		LAST_DIR=$(basename "$GIT_FOLDER")
		
		mv "$RELEASE_PATH/temp/$LAST_DIR" "$RELEASE_PATH"
				
		rm -rf "$RELEASE_PATH/temp"
	else
		echo "Le dossier $GIT_FOLDER n'existe pas dans le dépot"
		exit 1
	fi
fi

create_symlinks "$RELEASE_PATH"

build_application

ln -sfn "$RELEASE_PATH" project/current

cleanup_releases

echo "La nouvelle release a été déployé: "$RELEASE_PATH""
echo "nombre de releases a conserver: $KEEP"
}

rollback() {
	RELEASE_DIR="project/releases"
	
	RELEASES=($(ls -t $RELEASE_DIR))
	
	if [ ${#RELEASES[@]} -lt 2 ]; then 
		echo "rollback impossible, il y a moins de 2 releases"
		exit 1
	fi
	
	PREVIOUS_RELEASE="$RELEASE_DIR/${RELEASES[1]}"
	ln -sfn "$PREVIOUS_RELEASE" project/current
	
	echo "Rollback effectué, release active : "$PREVIOUS_RELEASE""
}

command=$1
shift

while getopts ":k:r:b:d:" opt; do
	case ${opt} in
		k )
			KEEP=$OPTARG
			;;
		r )
			GIT_REPO=$OPTARG
			;;
		b ) 
			GIT_BRANCH=$OPTARG
			;;
		d )
			GIT_FOLDER=$OPTARG
			;;
		\? )
			echo "option invalide : $OPTARG" 1>&2
			exit 1
			;;
	esac
done





case $command in
	deploy)
		deploy
		;;
	rollback)
		rollback
		;;
	create)
		create_project_structure
		;;
	*)
		echo "Usage: $0 {deploy|rollback|create} [-k nombre_de_release_à_conserver] [-r repo] [-b branch] [-d dossier]"
		exit 1
		;;
esac