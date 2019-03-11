/*--------------------------------------------------------------
//Name:         Jose Munoz
//NetID:        jam151830@utdallas.edu
//Course:       CS4348.001
//Project:      Project 3
//Due:          12/01/2018
//File:         Disk.h
//Notes:
--------------------------------------------------------------*/
#ifndef DISK_H
#define DISK_H
#include <iostream>
#include <stdlib.h>
#include <string>
#include "main.h"
#include "Block.h"
using namespace std;

class Disk{
 //Attributes
 private:
  int  size;
  Block* blocks;

 public:
  //Default Constructor
  Disk(){
    size = 256;
    //Disk storage = array of 256 block of size 512 bytes
    //initialize the data array 
    //update bitmap to default values
    blocks = new Block[size];
    updateBitmap(0, '1');//file alloc table
    updateBitmap(1, '1');//bitmap 
  }
  //Overloaded Constructors
  //Methods
  void displayDisk(){
    for(int i = 0; i < size; i++){
	cout << i << endl;
       	blocks[i].display();
	cout << endl;
    }

  } 
  //returns the contents of the given block number
  Block* read(int n)
  {
    if(n < 0 || n > size)
       return  NULL;
    return blocks[n].readBlock(); 
  }

  void write(int n, Block* newBlock)
  {
    if(n < 0 || n > size)
        return;
     blocks[n].writeBlock(newBlock);
     updateBitmap(n, '1');//mark this block as full
  }
  //Given a number, it displays the corresponding block 
  void displayBitmap(){
     for(int j = 0; j < size; j++){    
	  if(j%32 == 0 && j != 0)
	  	cout << endl;
       	  cout << blocks[1].getcAt(j);	
	}
	cout << endl;
  }
  void displayFileAllocTable(){
     char c1, c2;
     cout << "FileName\t\tStartBlock\tLength" << endl;
     for(int j = 0; j < 512; j++){      
     	for(int i = 0; i < 18; i++ ){
       	   cout << blocks[0].getcAt(j);
	   j++;
	}
	c1 = blocks[0].getcAt(j);
	c2 = blocks[0].getcAt(j+1);
	if( c2 == '0')
	   c1 = c2 = 0;
	printf( "\t%d\t\t%d\n", c1 , c2 ); 
	j++;
     }
     cout << endl;
  }
  void displayBlock(int n ){
     if(n > size || n < 0)
        return;
     blocks[n].display();
 
  }
  void updateBitmap(int n, char c){
     if(n > size || n < 0)
        return;
     blocks[1].putcAt(n, c);
  }

  Block* getBlock(int n){
     if(n > size || n < 0)
        return NULL;
     return &blocks[n];
  }
};
#endif 
