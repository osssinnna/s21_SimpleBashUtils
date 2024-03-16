#!/bin/bash
make all

template="int"

for x in e i v c l n h s o
do
    for y in e i v c l n h s o
    do
        flag="$x$y"
        test_number=0
        echo " "
        echo "Flag -$flag:"
        for test_file in "./tests_grep/test_text_0.txt" "./tests_grep/test_text_1.txt" "./tests_grep/test_text_2.txt" "./tests_grep/test_text_3.txt" "./tests_grep/test_text_4.txt" "./tests_grep/test_text_5.txt" "./tests_grep/test_text_6.txt" "./tests_grep/test_text_7.txt" "./tests_grep/test_text_ptrn.txt"
        do
            ./s21_grep -$flag $template $test_file > 1.txt
            grep -$flag $template $test_file > 2.txt
            if ! cmp -s 1.txt 2.txt ; then
                echo "Test $test_number: Fail"
            else
                echo "Test $test_number: Success"
            fi
            rm 1.txt 2.txt
            test_number=$(( $test_number + 1 ))
        done
    done
done

for x in e i v c l n h s o
do
    for y in f
    do
        flag="$x$y"
        test_number=0
        echo " "
        echo "Flag -$flag:"
        for test_file in "./tests_grep/test_text_0.txt" "./tests_grep/test_text_1.txt" "./tests_grep/test_text_2.txt" "./tests_grep/test_text_3.txt" "./tests_grep/test_text_4.txt" "./tests_grep/test_text_5.txt" "./tests_grep/test_text_6.txt" "./tests_grep/test_text_7.txt" "./tests_grep/test_text_ptrn.txt"
        do
            ./s21_grep -$flag "tests_grep/test.txt" $test_file > 3.txt
            grep -$flag "tests_grep/test.txt" $test_file > 4.txt
            if ! cmp -s 3.txt 4.txt ; then
                echo "Test $test_number: Fail"
            else
                echo "Test $test_number: Success"
            fi
            rm 3.txt 4.txt
            test_number=$(( $test_number + 1 ))
        done
    done
done


