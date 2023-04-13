#!/bin/sh
g++ higher_twist.cpp -Wall "$@" $(root-config --cflags --libs) -o higher_twist
