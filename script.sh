
dir_proj="project"
dir_rel="release"
dir_sha="shared"
date_folder=$(date +"%Y-%m-%d-%T")
dir_lib="lib"
dir_company="thecompanylegacynotversionnedlibrary"


create_project(){
  mkdir -p "$dir_proj/$dir_rel"
  mkdir -p "$dir_proj/$dir_sha/$dir_lib/$dir_company"
  touch "$dir_proj/$dir_sha/mysupersecretproductionconfigfile.yaml"
  echo "Project directories created."
}

create_date_dir(){
 new_release_dir="$dir_proj/$dir_rel/$date_folder"
  mkdir -p "$new_release_dir"
  echo "New release directory created: $new_release_dir"
}

deletus(){
   cd "$dir_proj/$dir_rel"
   rm -r $(ls -t | tail -n +6)
   echo "Keeping only the last 5."
}

symbolic_link(){
 latest_dir=$(ls -1dt "$dir_proj/$dir_rel"/*/ | head -n 1)
#make a symbolic link of the shared folder into the latest release folder
  ln -sf "$(realpath "$dir_proj/$dir_sha")" "$latest_dir/$dir_sha"
#updates the symbolic link for the latest folder
  ln -sfn "$latest_dir" "$dir_proj/current"
  echo "Symbolic links updated: $latest_dir"
}


deploy(){
   latest_dir="$dir_proj/$dir_rel/$date_folder"

   mkdir -p "$latest_dir"
   symbolic_link

   echo "Deployed: $latest_dir"
   #maybe call the delete function to not finish with a lot of folders
}


rollback() {
  releases=$(ls -1dt "$dir_proj/$dir_rel"/*/)

  release_count=$(echo "$releases" | wc -l)

  if [ "$release_count" -lt 2 ]; then
    echo "Error: Not enough releases to roll back. At least two releases are required."
    return 1
  fi

  previous_release=$(echo "$releases" | head -n 2 | tail -n 1)

  ln -sfn "$previous_release" "$dir_proj/current"

  echo "Rolled back to: $previous_release"
}





OPTSTRING=":abcdef"

while getopts ${OPTSTRING} opt; do
  case ${opt} in
    a)
       echo "Directories deleted"
       deletus
      ;;
    b)
      echo "Option create project was selected"
      create_project
      ;;
    c)
      echo "Create date directory"
      create_date_dir
      ;;
    d)
      echo "Symbolic link created"
      symbolic_link
      ;;
    ?)
      echo "Invalid option: -${OPTARG}."
      exit 1
      ;;
  esac
done

  # Command-line options

    if [ "$1" == "deploy" ]; then
      deploy
    elif [ "$1" == "rollback" ]; then
      rollback
    else
      echo "Usage: $0 {deploy|rollback}"
      exit 1
    fi


