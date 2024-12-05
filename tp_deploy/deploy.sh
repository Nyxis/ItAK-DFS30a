#!/bin/bash

source .env

deploy () {
    printf -v date '%(%Y%m%d%H%M%S)T' -1
    echo "create project/release/$date"

    mkdir project/release/$date

    clone_project

    # copy_shared_to_release

    delete_releases
}

copy_shared_to_release () {
    shared_file=($(cd ./project/shared/ && ls -pa | grep -v / ))

    for i in "${shared_file[@]}"
        do
            echo ln -s ./project/shared/$i ./project/release/$date/$i 
            ln -s ./project/shared/$i ./project/release/$date/$i
    done
}

delete_releases () {
    releases=($(ls -t  ./project/release/ ))
    nb_releases=${#releases[@]}
    nb_to_delete=10

    if [ "$nb_releases" -gt "$nb_to_delete" ] 
    then
        releases_to_delete=("${releases[@]:nb_to_delete}")
        for i in "${releases_to_delete[@]}"
        do
            rm -rf ./project/release/"$i"
        done
    fi
}

clone_project () {
#   rm ./project/current

  cd ./../AD9_Linux_web/
  git clone -b main $REMOTE clone_me 
  cd ../tp_deploy/
  echo $(pwd)
  cp -r ./../AD9_Linux_web/clone_me/* ./project/release/$date/

    FILE=$(pwd)/project/release/$date/AD9_Linux_web/clone_me/

    if [ -f $FILE/Makefile ]; then
        cd $FILE
        make build
    fi

    cd ../../../../../
    ln -s $(pwd)/project/release/$date $(pwd)/project/current
}


rollback () {
    last_two_release=($(ls project/release/ -t | head -2 ))
    last_two_release2=("${last_two_release[@]:b}")
    previous_release=${last_two_release2[1]}
    project_files=($(ls -f project/ ))

    for i in "${project_files[@]}"
        do
            if [ "$i" = "current" ]; then
                rm -rf ./project/"$i"
            fi
    done

    echo "update current release link"
    ln -s ./project/release/$previous_release ./project/current
}


clean () {
    rm -rf ../AD9_Linux_web/clone_me
}

if [ "$1" = "deploy" ]; then
    echo "deploy mode"
    deploy
elif [ "$1" = "rollback" ]; then
    echo "rollback mode"
    rollback

elif [ "$1" = "clean" ]; then
    clean
fi




    




# # create release folder

# # delete old release function
# delete_releases () {
#     releases=($(ls -t  ./project/release/ ))
#     nb_releases=${#releases[@]}
#     b=$nb_to_delete

#     # if nb releases > 5
#     if [ "$nb_releases" -gt "$b" ] 
#     then
#         releases_to_delete=("${releases[@]:b}")
#         for i in "${releases_to_delete[@]}"
#         do
#             rm -rf ./project/release/"$i"
#         done
#     fi
# }

# # get arg releases nb to delete
# OPTSTRING=":x:"

# nb_to_delete=5
# while getopts ${OPTSTRING} opt; do
# case ${opt} in
#     x)
#     nb_to_delete=${OPTARG}
#     echo "Option -x was triggered, Argument: ${OPTARG}"
#     ;;
#     :)
#     echo "Option -${OPTARG} requires an argument."
#     exit 1
#     ;;
#     ?)
#     echo "Invalid option: -${OPTARG}."
#     exit 1
#     ;;
# esac
# done

# delete_releases "$nb_to_delete"

