#!/bin/bash
echo "hello, i'm hello.sh"
int=1
while(( $int<=5 ))
do
    echo $int
    let "int++"
    sleep 1
done

