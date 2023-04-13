#!/bin/sh
g++ leading_twist.cpp -Wall "$@" $(root-config --cflags --libs) -o leading_twist
