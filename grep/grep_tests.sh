#!/bin/bash

GREEN='\e[32m'
RED='\e[31m'
NC='\e[0m'
testNum=0;
failed=0
DIFF_RES=""
TEST_FILES="test1 test2 test3"
VALGRIND="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind.txt"

printf "${GREEN}///////////RUNNING TESTS!/////////////${NC}\n"

for var in -i -v -c -l -n -h -s -o
do
  for FILE1 in "test1" "test2" "test3"
  do
    for FILE2 in "test1" "test2" "test3"
    do
      for FILE3 in "test1" "test2" "test3"
      do
        if [ $FILE1 != $FILE2 ] && [ $FILE1 != $FILE3 ] && [ $FILE2 != $FILE3 ]; then
          (( testNum++ ))
          TEST="$var $FILE1 $FILE2 $FILE3"
          ./grep $TEST > mygrep_temp_file
          grep $TEST > grep_temp_file
          DIFF_RES="$(diff -s mygrep_temp_file grep_temp_file)"
          if [ $? -eq 0 ]; then
            printf "TEST #$testNum ($TEST):${GREEN}PASSED${NC}\n"
          else
            printf "TEST #$testNum ($TEST):${RED}FAILED${NC}\n"
            echo "$TEST" >> log.txt
            (( failed++ ))
          fi
          rm mygrep_temp_file grep_temp_file
        fi
      done
    done
  done
done

for var in -i -v -c -l -n -h -s -o
do
  for var2 in -i -v -c -l -n -h -s -o
  do
        if [ $var != $var2 ]; then
          (( testNum++ ))
          TEST="$var $var2 $TEST_FILES"
          ./grep $TEST > mygrep_temp_file
          grep $TEST > grep_temp_file
          DIFF_RES="$(diff -s mygrep_temp_file grep_temp_file)"
          if [ $? -eq 0 ]; then
            printf "TEST #$testNum ($TEST):${GREEN}PASSED${NC}\n"
          else
            echo "$TEST1" >> log.txt
            (( failed++ ))
            printf "TEST #$testNum ($TEST):${RED}FAILED${NC}\n"
          fi
          rm mygrep_temp_file grep_temp_file
        fi
  done
done

for var in -i -v -c -l -n -h -s -o
do
  for var2 in -i -v -c -l -n -h -s -o
  do
      for var3 in -i -v -c -l -n -h -s -o
      do
        if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]; then
          (( testNum++ ))
          TEST="$var $var2 $var3 $TEST_FILES"
          ./grep $TEST > mygrep_temp_file
          grep $TEST > grep_temp_file
          DIFF_RES="$(diff -s mygrep_temp_file grep_temp_file)"
          if [ $? -eq 0 ]; then
            printf "TEST #$testNum ($TEST):${GREEN}PASSED${NC}\n"
          else
            printf "TEST #$testNum ($TEST):${RED}FAILED${NC}\n"
            echo "$TEST" >> log.txt
            (( failed++ ))
          fi
          rm mygrep_temp_file grep_temp_file

        fi
      done
  done
done

for var in -i -v -c -l -n -h -s -o
do
  for var2 in -i -v -c -l -n -h -s -o
  do
      for var3 in -i -v -c -l -n -h -s -o
      do
          for var4 in -i -v -c -l -n -h -s -o
          do
            if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ] && [ $var != $var4 ] && [ $var2 != $var4 ] && [ $var3 != $var4 ]
            then
              (( testNum++ ))
              TEST="$var $var2 $var3 $var4  $TEST_FILES"
              ./grep $TEST > mygrep_temp_file
              grep $TEST > grep_temp_file
              DIFF_RES="$(diff -s mygrep_temp_file grep_temp_file)"
              if [ $? -eq 0 ]; then
                printf "TEST #$testNum ($TEST):${GREEN}PASSED${NC}\n"
              else
                printf "TEST #$testNum ($TEST):${RED}FAILED${NC}\n"
                echo "$TEST" >> log.txt
                (( failed++ ))
              fi
              rm mygrep_temp_file grep_temp_file

            fi
          done
      done
  done
done
printf " ${GREEN}/////////////DONE[$((testNum - failed - 1))/$((testNum-1))]//////////////${NC}\n"
