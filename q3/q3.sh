#!/bin/bash

# array of directory names
declare -a dirNames=("java" "txt" "cpp" "cc" "others")

init(){
    # make $1 number of directories such as "dir1", "dir2", "dir3" etc
    cd mainDir
    for (( i=1; i<=$1; i++ ))
    do
        mkdir "dir_$i"
    done
}

forward(){
    # move to directory of extension name and file name is of format "dirname_fileName"
    cd mainDir
    for i in "${dirNames[@]}"
    do
        mkdir $i
        echo "Created $i directory"
    done
    
    for i in *
    do
        if [[ -d $i ]] # if it is a directory
        then
            
            # skip new heirarchy directories
            if [[ " ${dirNames[@]} " =~ " $i " ]] # if exists in dirNames array
            then
                continue
            fi
            
            # go inside the old heirarchy directory
            cd $i
            
            # loop over all files in the directory and move them in the extension specific folders present one step behind
            for j in *
            do
                echo -e "\033[0;31mDir name: $i \033[0m"
                # if it is a file
                if [ -f $j ]
                then
                    # extract extension name
                    ext=${j##*.}
                    if [ $ext == "java" ]
                    then
                        echo "Moving $j to java directory"
                        mv $j ../java/"$i"-"$j"
                    elif [ $ext == "txt" ]
                    then
                        echo "Moving $j to txt directory"
                        mv $j ../txt/"$i"-"$j"
                    elif [ $ext == "cpp" ]
                    then
                        echo "Moving $j to cpp directory"
                        mv $j ../cpp/"$i"-"$j"
                    elif [ $ext == "cc" ]
                    then
                        echo "Moving $j to cc directory"
                        mv $j ../cc/"$i"-"$j"
                    else
                        echo "Moving $j to others directory"
                        mv $j ../others/"$i"-"$j"
                    fi
                fi
            done
            cd ..
        fi
    done
    
    # delete directories starting with "dir_"
    for i in *
    do
        if [[ $i == dir_* ]]
        then
            rm -r $i
        fi
    done
}

backward(){
    cd mainDir
    # extract directory name from file name such as "dir1_file1" and move it to "dir1" directory
    for i in *
    do
        if [[ -d $i ]]
        then
            cd $i
            for j in *
            do
                echo $j
                # extract directory name from file name such as "dir_1-file.cc"
                dirName=${j%%-*}
                # make directory one step back with the name extracted from file name
                mkdir -p ../$dirName
                echo "Moving $j to $dirName directory"
                # remove "dir_1" from directory name and getting original file name
                fileName=${j#*-}
                # move file to original directory
                mv $j ../$dirName/$fileName
            done
            cd ..
        fi
    done
    
    # delete extension specific directories
    for i in *
    do
        if [[ " ${dirNames[@]} " =~ " $i " ]]
        then
            rm -r $i
        fi
    done
}





case $1 in
    init)
        init $2
        ;;
    forward)
        forward
        ;;
    backward)
        backward
        ;;
    *)
        echo "Invalid command"
        ;;
esac