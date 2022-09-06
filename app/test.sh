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


(ls)
(cd ..)
(ls) | tr a b
(ls) | tr a b && ls
(ls | tr a b) && (cat Makefile | grep a)
(ls | tr a b) && (cat Makefile | grep a | ls asdf) || (ls)