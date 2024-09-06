printf -v date '%(%Y%m%d%H%M%S)T' -1

if [ "$1" = "deploy" ]; then 

  # create release folder
  mkdir project/release/$date


  # delete old release function
  delete_releases () {
      releases=($(ls -t  ./project/release/ ))
      nb_releases=${#releases[@]}
      b=$nb_to_delete

      # if nb releases > 5
      if [ "$nb_releases" -gt "$b" ] 
      then
          releases_to_delete=("${releases[@]:b}")
          for i in "${releases_to_delete[@]}"
          do
              rm -rf ./project/release/"$i"
          done
      fi
  }

  # get arg releases nb to delete
  OPTSTRING=":x:"

  nb_to_delete=5
  while getopts ${OPTSTRING} opt; do
    case ${opt} in
      x)
        nb_to_delete=${OPTARG}
        echo "Option -x was triggered, Argument: ${OPTARG}"
        ;;
      y)
        echo "Option -y was triggered, Argument: ${OPTARG}"
        ;;
      :)
        echo "Option -${OPTARG} requires an argument."
        exit 1
        ;;
      ?)
        echo "Invalid option: -${OPTARG}."
        exit 1
        ;;
    esac
  done



  # link shared/files to release
  shared_file=($(cd ./project/shared/ && ls -pa | grep -v / ))

  for i in "${shared_file[@]}"

    do
      echo $i
      echo ./project/shared/$i
      echo ./project/release/$date/$i
        ln -s ./project/shared/$i ./project/release/$date/$i
  done

  # create current link from current release
  rm ./project/current
  ln -s ./project/release/$date ./project/current


  delete_releases "$nb_to_delete"

# update current link with the previous release
elif [ "$1" = "rollback" ]; then

    last_two_release=($(ls project/release/ -t | head -2 ))
    last_two_release2=("${last_two_release[@]:b}")
    previous_release=${last_two_release2[1]}

    rm ./project/current
    ln -s ./project/release/$previous_release ./project/current
fi