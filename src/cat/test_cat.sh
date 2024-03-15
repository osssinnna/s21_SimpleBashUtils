#!/bin/bash
make all

echo " "
echo "Response to wrong flag:"
./s21_cat -q $test_file
echo " "
echo "Response to wrong file:"
./s21_cat -$flag nofile.txt

for flag in "-b" "-e" "-n" "-s" "-t" 
do
    test_number=1
    echo " "
    echo "Flags: $flag:"
    for test_file in  "tests_grep/test_text_0.txt" "tests_grep/test_text_1.txt" "./tests_grep/test_text_2.txt" "./tests_grep/test_text_3.txt" "./tests_grep/test_text_4.txt" "./tests_grep/test_text_5.txt" "./tests_grep/test_text_6.txt" "./tests_grep/test_text_7.txt" "./tests_grep/test_text_ptrn.txt" "./tests_grep/test_text_6.txt ./tests_grep/test_text_6.txt"
    do
        ./s21_cat $flag $test_file > 1.txt
        cat $flag $test_file > 2.txt
        if ! cmp -s 1.txt 2.txt ; then
            echo "Test $test_number: Fail"
        else
            echo "Test $test_number: Success"
        fi
        rm 1.txt 2.txt
        test_number=$(( $test_number + 1 ))
    done
done
echo " "
echo " "
