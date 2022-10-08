#!/bin/bash

echo -e "\nPattern Option Entered: $1"
echo -e "Number Entered: $2"

pattern=$1
option=$2


leftPattern ()
{
    echo -e "\nLeft Pattern\n"
    # option number of rows
    for (( i=1; i<=$option; i++ ))
    do
        # print star the number of times = current rows done
        for (( j=1; j<=$i; j++ ))
        do
            echo -n "*"
        done
        echo
    done
    
    for (( i=$option-1; i>=1; i-- ))
    do
        for (( j=1; j<=$i; j++ ))
        do
            echo -n "*"
        done
        echo
    done
}

rightPattern(){
    echo -e "\nRight Pattern\n"
    for (( i=1; i<=$option; i++ ))
    do
        for (( j=1; j<=$option; j++ ))
        do
            if [ $j -le $(( $option - $i )) ]
            then
                echo -n " "
            else
                echo -n "*"
            fi
        done
        echo
    done
    
    for (( i=$option-1; i>=1; i-- ))
    do
        for (( j=1; j<=$option; j++ ))
        do
            if [ $j -le $(( $option - $i )) ]
            then
                echo -n " "
            else
                echo -n "*"
            fi
        done
        echo
    done
}

fullPattern(){
    echo -e "\nFull Pattern\n"
    for (( i=1; i<=$option; i++ ))
    do
        for (( j=1; j<=$option; j++ ))
        do
            if [ $j -le $(( $option - $i )) ]
            then
                echo -n " "
            else
                echo -n "*"
            fi
        done
        
        for (( j=1; j<=$i; j++ ))
        do
            echo -n "*"
        done
        echo
    done
    
    for (( i=$option-1; i>=1; i-- ))
    do
        for (( j=1; j<=$option; j++ ))
        do
            if [ $j -le $(( $option - $i )) ]
            then
                echo -n " "
            else
                echo -n "*"
            fi
        done
        
        for (( j=1; j<=$i; j++ ))
        do
            echo -n "*"
        done
        echo
    done
}


case "$1" in
    "full")
        fullPattern
    ;;
    "left") 
        leftPattern
    ;;
    "right") 
        rightPattern
    ;;
    *) 
        echo -e "\nWrong Option For Pattern\n"
esac