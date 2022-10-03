#!/bin/bash
tests_dir="./tests/"

# tests
echo "It works""
echo oi
echo -n
echo -n oi
echo -n -n -n
echo $PATH
expr $? + $?
expr 2 + 2
cd ..
cd -
cd ..
cd -
cd ..
cd -
cd ..
cd -
echo $?

foo
/bin/ls
/bin/ls -laF
/bin/ls -l -a -F
/bin/ls
echo $?
/bin/ls
echo $?
/bin/ls
echo $?
/bin/ls
echo $?
/bin/ls
ls

bk="$PATH"
unset PATH
ls
cat Makefile
PATH="$bk"
ls
cat Makefile

ls > cat.txt
cat cat.txt
ls >> cat.txt
cat cat.txt
cat.txt < tr a b
rm cat.txt
echo "teste" | << FIM | tr a b
echo "teste" | << FIM | tr a b > teste
cat teste
rm teste
ls && ls
ls asdf || ls
cd ..
cd -
(cd ..)
ls *
ls a*
ls *a
ls a*a
ls a*g*l
ls *a*
ls *************
ls * * * * * * *
echo "'oi'"
echo '"oi"'
echo '"$PWD"'
echo "'$PWD'"
echo -n-n-n---n-n-n

