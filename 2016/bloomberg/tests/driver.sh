cd `dirname $0`
rm -f tmp*.txt
cat input001.txt | ../a.out > tmp001.txt
diff -y tmp001.txt output001.txt
cat input002.txt | ../a.out > tmp002.txt
diff -y tmp002.txt output002.txt
cat input003.txt | ../a.out > tmp003.txt
diff -y tmp003.txt output003.txt
cat input004.txt | ../a.out > tmp004.txt
diff -y tmp004.txt output004.txt
cat input005.txt | ../a.out > tmp005.txt
diff -y tmp005.txt output005.txt
