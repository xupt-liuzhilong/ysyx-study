#!/bin/sh

set -e

echo "TEST 1: movement"

output=$(printf "n\ne\nw\ns\n" | ./ex19)

echo "$output" | grep -q "The throne room"
echo "$output" | grep -q "Kitchen"
echo "$output" | grep -q "The great Hall"

echo "PASS"

echo "TEST 2: list exits"

output=$(printf "l\nn\nl\n" | ./ex19)

echo "$output" | grep -q "NORTH"
echo "$output" | grep -q "SOUTH"
echo "$output" | grep -q "EAST"
echo "$output" | grep -q "WEST"

echo "PASS"

echo "TEST 3: attack"

output=$(printf "n\nw\na\n" | ./ex19)

echo "$output" | grep -q "The arena"
echo "$output" | grep -q "You attack The evil minotaur"

echo "PASS"

echo "TEST 4: invalid input"

output=$(printf "x\n" | ./ex19)

echo "$output" | grep -q "What?:"

echo "PASS"

echo "TEST 5: extra room and monster"

output=$(printf "n\ne\nn\na\n" | ./ex19)

echo "$output" | grep -q "The dark cellar"
echo "$output" | grep -q "You attack The cave troll"

echo "PASS"

echo "All testes passed."
