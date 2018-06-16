#!/bin/bash
IFS=$'\n'
if [ ! -d "lab1" ] 
then
  mkdir lab1
fi 
cd lab1
if [ ! -d "11510225" ]
then
  mkdir 11510225
fi 
cd 11510225
if [ -f "file.info" ]
then
  rm -f file.info
fi 
touch file.info

folder="/home/lifesaver"
fil=0
dir=0
unlist=0
enlist=0

function readfile ()
{
  echo "[ ${1##*/} ]" >> file.info
  for file in `ls $1`
  do
    if [ -d $1"/"$file ]
    then
      dir=$((dir+1))
      echo ${1:5}"/"$file >> file.info
      #readfile $1"/"$file
      unread[$unlist]="$1"/"$file"
      unlist=$((unlist+1))
    else
      fil=$((fil+1))
      echo ${1:5}"/"$file >> file.info
   fi
  done
  echo >> file.info
}

readfile $folder

while [ $unlist -ne $enlist ]
 do
 readfile ${unread[$enlist]}
 enlist=$((enlist+1))
 done

echo "[ Directories Count ] : $dir" >> file.info
echo >> file.info
echo "[ Files Count ] : $fil" >> file.info    
