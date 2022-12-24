#!/bin/bash

GREEN='\e[32m'
NC='\e[0m'
RED='\e[31m'

DIFF_RES=""
failed=0
testNum=1
TEST=""
echo "" > log.txt

CURRENTFILES="test1.txt test2.txt test3.txt test4.txt test5.txt"
EXE=./cat
rm log.txt


printf "${GREEN}////////////RUNNING TESTS!/////////////  ${NC}\n"


for FLAG in -b -e -s -t -n -v
do
    TEST="$FLAG $CURRENTFILES"
    cat $TEST > cat_temp_file
    ./cat $TEST > s21_cat_temp_file
    DIFF_RES="$(diff  s21_cat_temp_file cat_temp_file)"
    if [ $? -eq 0 ]; then
        printf "TEST #$testNum($TEST):${GREEN}PASSED${NC}\n"
    else
        printf "TEST #$testNum($TEST):${RED}FAILED${NC}\n"
    echo $TEST $(diff s21_cat_test_temp_file cat_test_temp_file) > log.txt
    ailed=$((failed+1))
    fi
    rm s21_cat_temp_file cat_temp_file
    testNum=$((testNum+1))
done

for FLAG1 in -b -e -s -t -n -v
do
    for FLAG2 in -b -e -s -t -n -v
    do
    if [ $FLAG1 != $FLAG2 ]; then
        TEST="$FLAG1 $FLAG2 $CURRENTFILES"
        cat $TEST > cat_temp_file
        ./cat $TEST > s21_cat_temp_file
        DIFF_RES="$(diff -s s21_cat_temp_file cat_temp_file)"
        if [ $? -eq 0 ]; then
            printf "TEST #$testNum($TEST):${GREEN}PASSED${NC}\n"
        else
            printf "TEST #$testNum($TEST):${RED}FAILED${NC}\n"
            echo $DIFF_RES >> tests_log.txt
            failed=$((failed+1))
        fi
    rm -rf s21_cat_temp_file cat_temp_file
    testNum=$((testNum+1))
    fi
    done
done

for FLAG1 in -b -e -s -t -n -v
do
    for FLAG2 in -b -e -s -t -n -v
    do
        for FLAG3 in -b -e -s -t -n -v
        do
        if [ $FLAG1 != $FLAG2 ] && [ $FLAG1 != $FLAG3 ] && [ $FLAG2 != $FLAG3 ]; then
            TEST="$FLAG1 $FLAG2 $CURRENTFILES"
            cat $TEST > cat_temp_file
            ./cat $TEST > s21_cat_temp_file
            DIFF_RES="$(diff -s s21_cat_temp_file cat_temp_file)"
            if [ $? -eq 0 ]; then
                printf "TEST #$testNum($TEST):${GREEN}PASSED${NC}\n"
            else
                printf "TEST #$testNum($TEST):${RED}FAILED${NC}\n"
                echo $DIFF_RES >> tests_log.txt
                failed=$((failed+1))
            fi
            rm -rf s21_cat_temp_file cat_temp_file
            testNum=$((testNum+1))
        fi
        done
    done
done

for FLAG1 in -b -e -s -t -n -v # -E -T  --number --squeeze-blank --number-nonblank
    do
        for FLAG2 in -b -e -s -t -n -v # -E -T --number --squeeze-blank --number-nonblank
        do
            for FLAG3 in -b -e -s -t -n -v # -E -T --number --squeeze-blank --number-nonblank
            do
                for FLAG4 in -b -e -s -t -n -v # -E -T --number --squeeze-blank --number-nonblank
                do
                if [ $FLAG1 != $FLAG2 ] && [ $FLAG2 != $FLAG3 ] && [ $FLAG1 != $FLAG3 ] && [ $FLAG4 != $FLAG2 ] && [ $FLAG4 != $FLAG3 ] && [ $FLAG4 != $FLAG1 ]; then   
                    TEST="$FLAG1 $FLAG2 $FLAG3 $FLAG4 $CURRENTFILES"
                    cat $TEST > cat_temp_file
                    ./cat $TEST > s21_cat_temp_file
                    DIFF_RES="$(diff -s s21_cat_temp_file cat_temp_file)"
                    if [ $? -eq 0 ]; then
                    printf "TEST #$testNum($TEST):${GREEN}PASSED${NC}\n"
                    else
                    printf "TEST #$testNum($TEST):${RED}FAILED${NC}\n"
                    echo $DIFF_RES >> log.txt
                    failed=$((failed+1))
                    fi
                rm -rf s21_cat_test_temp_file cat_test_temp_file
                testNum=$((testNum+1))
                fi
            done
        done
    done
done

rm -rf s21_cat_test s21_cat_temp_file cat_temp_file

printf " ${GREEN}/////////////DONE[$((testNum - failed - 1))/$((testNum-1))]//////////////${NC}\n"
