/*--------------------------------------------------------------
//Name:         Jose Munoz
//NetID:        jam151830@utdallas.edu
//Course:       CS4348.001
//Project:      Project 3
//Due:          12/01/2018
//File:         Block.cc
//Notes:
--------------------------------------------------------------*/
#ifndef BLOCK_CC
#define BLOCK_CC
#include <iostream>
#include <stdlib.h>
#include <string>
#include "main.h"
#endif
using namespace std;

class Block{
 //Attributes
 private:
  int size;
  char *block; 

 public:
  //Default Constructor
  Block(){
    size = 512;
    //block = array of 512 chars 
    block = new char[size];
    //initialize array to all 0 chars
    for(int i = 0; i < 512; i++){
      block[i] = '0';
    }
  }
  //Overloaded Constructor
  Block(char *data, int s){
    size = 512;
    block = new char[size];
    if (s == 512){
      for(int i = 0; i < 512; i++){
	block[i] = data[i];
      }
    }  
  }
  //Methods
  void print(){
    for(int i = 0; i < 512; i++){
      cout << endl;
      cout << endl;
    }
  }

}; 
