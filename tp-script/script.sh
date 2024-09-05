KEEP=5


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
		echo "dossier project existe déja"
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


deploy() {

create_project_structure

CURRENT_DATE=$(date +"%Y%m%d%H%M%S")

RELEASE_PATH="project/releases/$CURRENT_DATE"

mkdir -p "$RELEASE_PATH"

create_symlinks "$RELEASE_PATH"

ln -sfn "$RELEASE_PATH" project/current

cleanup_releases

echo "La nouvelle release a été déployé: "$RELEASE_PATH""
echo $KEEP


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

while getopts ":k:" opt; do
	case ${opt} in
		k )
			KEEP=$OPTARG
			;;
		\? )
			echo "option invalide : $OPTARG" 1>$2
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
		echo "Usage: $0 {deploy|rollback|create} [-k nombre_de_release_à_conserver]"
		exit 1
		;;
esac