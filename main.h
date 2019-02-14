/*---------------------------------------------------------------------------------------
Student:    Jose Munoz
NetID:      jam151830
Course:     CS4348.001
Due:	    12/1/2018
Project:    Project 3 - Disk Allocation Methods
File:       main.h
Notes:
---------------------------------------------------------------------------------------*/
#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip>
#include <cstdlib>
#endif
using namespace std;

/*Function Prototypes*/
void displayMenu(); //displays user options
bool validOption(string );//validates the user's input for the menu options - takes in a string and checks to see if is a 1,2 or 3


//disk has two methods, diks can only read an entire block or write an entire block, is an unintelliget device
//minimal design - 3 objects
//UI
//takes input and talks to diks
//Disk
//19641 - scantron
