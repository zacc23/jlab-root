#!/bin/sh
\time -v -- g++ leading_twist.cpp $(root-config --cflags --libs) -o leading_twist
