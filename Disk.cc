/*--------------------------------------------------------------
//Name:         Jose Munoz
//NetID:        jam151830@utdallas.edu
//Course:       CS4348.001
//Project:      Project 3
//Due:          12/01/2018
//File:         Disk.cc
//Notes:
--------------------------------------------------------------*/
#ifndef DISK_CC
#define DISK_CC
#include <iostream>
#include <stdlib.h>
#include <string>
#include "main.h"
using namespace std;

class Disk{
 //Attributes
 private:
  int  length;
  int *blocks; 

 public:
  //Default Constructor
  Disk(){
    length = 256;
    //Disk storage = array of 256 blocks of size 512 bytes
    blocks = new int[length];
  }
  //Overloaded Constructors
  
  //Methods
  int read(int block)
  {
    if(block < 0 || block > 256)
       return  -1;
    else 
      return blocks[block];
  }

  void write(int index, int block)
  {
    blocks[index] = block;
  }

};
#endif 
