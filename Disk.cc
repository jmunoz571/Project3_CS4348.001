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
  int  blocks;
  int  block_size;
  char *data; 

 public:
  //Default Constructor
  Disk(){
    blocks = 256;
    block_size = 512;
    //Disk storage = array of 256 blocks of size 512 bytes
    data = new char[blocks * block_size];
    //initialize the data array 
    for(int i = 0; i < blocks * block_size; i++){
      block[i] = '0';
    }
  }
  //Overloaded Constructors
  void printData(){
    for(int i = 0; i < blocks; i++){
	cout << i << endl;
	for(int j = 0; j < block_size; j++){    
       	cout << data[i][j];	
	}
    }

  } 
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
