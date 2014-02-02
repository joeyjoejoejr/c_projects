#!/bin/bash

set -e
rm db.dat
make ex17plusplus
./ex17plusplus db.dat c 100 512
./ex17plusplus db.dat s 1 joe joe@jackson.com
./ex17plusplus db.dat s 2 jack jack@jackson.com
./ex17plusplus db.dat g 1
./ex17plusplus db.dat g 2
./ex17plusplus db.dat d 2
./ex17plusplus db.dat s 2 jack jack@jackson.com
./ex17plusplus db.dat l
./ex17plusplus db.dat f joe
./ex17plusplus db.dat f jack
