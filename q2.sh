#!/bin/bash

part1(){
    echo "Enter the name of file:"
    read fileName

    # display file permissions
    echo "File permissions:"
    ls -l $fileName

    # reverse the file permissions e.g rw-r--r-- to --r--r--rw
    echo "Reversed file permissions:"
    ls -l $fileName | cut -d " " -f 1 | rev
    
}


part2(){
    echo "Enter the name of file:"
    read fileName
    
    chmod 777 $fileName

    echo "Enter the string to search for:"
    read searchString

    echo "Search string:"
    grep -i -n $searchString $fileName
}

part3(){
    echo "Enter the name of file to copy from: 🤔"
    read fileName
    
    chmod 777 $fileName
    
    echo "Enter the number of even lines to copy: 🤔"
    read numLines
    
    numLines=$((numLines*2))
    
    ############################
    head -n $numLines $fileName | sed -n '0~2p' > dummy.txt

    # echo "Even lines:"
    # cat evenLines.txt

    ############################
    tail -n $numLines $fileName | sed -n '2~2p' >> dummy.txt
    
    # echo "Odd lines:"
    # cat oddLines.txt
    
    echo "Copied to dummy.txt 😎"
}

part4(){
    echo "Enter file name: 🤔"
    read fileName
    
    # modified date
    echo "Modified date: 📅"
    stat -c %y $fileName
    
    # if modified time is greater than 24 hours then change modified time to current time
    if [ $(stat -c %Y $fileName) -lt $(date -d "24 hours ago" +%s) ]
    then
        touch -d "24 hours ago" $fileName
    fi
}


exiting(){
    echo -n "Exiting the program... ☠️" 
    for i in {1..4}
    do
        echo -n "."
        sleep 1
    done
}


dateAndTime(){
    echo -n "Date: " && date +"%Y,%m,%d" >> log.txt
    echo -n "Time: " && date +%T >> log.txt
}


case $1 in
    1)
        echo "Option 1 selected at: " >> log.txt
        dateAndTime
        part1
        ;;
    2)
        echo "Option 2 selected at: " >> log.txt
        dateAndTime
        part2
        ;;
    3)
        echo "Option 3 selected at: " >> log.txt
        dateAndTime
        part3
        ;;
    4)
        echo "Option 4 selected at: " >> log.txt
        dateAndTime
        part4
        ;;
    "exit" | "quit" | "q" | "e")
        echo "Exited the script at: " >> log.txt
        dateAndTime
        exiting
        ;;
    *)
        echo "Invalid option entered at:"
        dateAndTime
        echo "Invalid option"
        ;;
esac