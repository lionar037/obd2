#!/bin/bash


g++ -o elm327_bluetooth main.cc -lbluetooth

g++ -o app main.cpp -lbluetooth
