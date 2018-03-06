#!/bin/bash
rm main *.gch
g++ --std=gnu++11 main.cpp rbnode.hpp rbtree.hpp -o main
