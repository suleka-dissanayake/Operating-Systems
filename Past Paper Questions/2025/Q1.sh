#!/bin/bash

count=0

for file in *.jpg *.png
do
    if [ -f "$file" ]
    then
        echo $file

        folder=$(echo $file | cut -c1-7)

        mkdir -p $folder

        sum=$(md5sum $file | cut -d " " -f1)

        duplicate=0

        for f in $folder/*
        do
            if [ -f "$f" ]
            then
                s=$(md5sum $f | cut -d " " -f1)

                if [ "$sum" = "$s" ]
                then
                    duplicate=1
                    rm $file
                    break
                fi
            fi
        done

        if [ $duplicate -eq 0 ]
        then
            mv $file $folder/
            count=$((count+1))
        fi
    fi
done

for d in */
do
    c=$(ls $d | wc -l)
    echo "$d : $c files"
done

echo "Total files organized = $count"