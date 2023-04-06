#!/bin/bash

echo '2.1 Create tempFiles'
mkdir -p tempFiles

echo '2.2 Creating detailed(with dimension) content list'
ls -Rhl

echo '2.3 Move .c .sh files to tempFiles folder'
mv *.c *.sh tempFiles
ls -Rhl

echo '2.4 All files (except folder content) in the work path are deleted.'
rm -rf *.*
ls -Rhl

echo '2.5 All content in the tempFiles folder is copied to the work path.'
cp -a tempFiles/* .
ls -Rhl

echo '2.6 Delete tempFiles'
rm -rf tempFiles
ls -Rhl

echo '2.7 Compile source code'
gcc -o main 152120191064_uyg1A.c

echo '2.8 Output is directed to file (152120191064_uyg1A_output.txt)'

for i in {1..3}; do
  echo 'Enter a number:'
    read num
    output=$(./main $num)
    echo $output
    echo "$output" >> 152120191064_uyg1A_output.txt
    echo 'Character count:'
    wc -c < 152120191064_uyg1A_output.txt | cut -d' ' -f1
    echo '---------------------------'
done

echo '2.9 All the contents of the output file are printed to the screen'
cat 152120191064_uyg1A_output.txt