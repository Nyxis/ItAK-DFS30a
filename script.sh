
dir_proj="project"
dir_rel="release"
dir_sha="shared"
date_folder=$(date +"%Y-%m-%d-%T")
dir_lib="lib"
dir_company="thecompanylegacynotversionnedlibrary"

create_project(){
  mkdir "$dir_proj"
  cd "$dir_proj"
  mkdir "$dir_rel"
  mkdir -p "$dir_sha/$dir_lib"
  mkdir -p "$dir_sha/$dir_lib/$dir_company"
}

create_date_dir(){
  cd "$dir_proj/$dir_rel"
  mkdir "$date_folder"
}

deletus(){
  rm -r `ls -t | tail -n +6`
}

OPTSTRING=":abc"

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
    ?)
      echo "Invalid option: -${OPTARG}."
      exit 1
      ;;
  esac
done




