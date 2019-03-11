/*--------------------------------------------------------------
//Name:         Jose Munoz
//NetID:        jam151830@utdallas.edu
//Course:       CS4348.001
//Project:      Project 3
//Due:          12/01/2018
//File:         Block.h
//Notes:
--------------------------------------------------------------*/
#ifndef BLOCK_H
#define BLOCK_H
#include <iostream>
#include <stdlib.h>
#include <string>
#include "main.h"
using namespace std;

class Block{
 //Attributes
 private:
  int block_size;
 protected:
  char *data; 

 public:
  //Default Constructor
  Block(){
    block_size = 512;
    //block = array of 512 chars 
    data = new char[512];
    //initialize array to all 0 chars
    for(int i = 0; i < block_size; i++){
      data[i] = '0';
    }
  }
  
  //Methods
  Block* readBlock()
  {
    Block* temp = new Block(); 
    for(int j = 0; j < block_size; j++){   
        temp->data[j] = this->data[j];
     }
    return temp; 
  }

  void writeBlock(Block* newBlock)
  {
     for(int j = 0; j < 512; j++){   
        data[j] =  newBlock->data[j];
     }
  }
  //Given a number, it displays the corresponding block 
  void displayBitmap(){
     for(int j = 0; j < 256; j++){    
	  if(j%32 == 0 && j != 0)
	  	cout << endl;
       	  cout << data[j];	
	}
	cout << endl;
  }
  void displayFileAllocTable(){
     cout << "FileName\tStartBlock\tLength" << endl;
     for(int j = 0; j < 256; j++){      
     	for(int i = 0; i < 8; i++, j++)
       	  cout << data[j];
	cout << "\t" << data[j+1] << "\t\t" << data[j+2] << endl; 
	j+=2;
     }
     cout << endl;
  }
     
  void updateBitmap(int n, char c){
     if(n > 256 || n < 0)
        return;
     data[n] = c; 
  }
  void display(){
     for(int j = 0; j < block_size; j++){    
        if(j%32 == 0 && j != 0)
	  cout << endl;
       	cout << data[j];	
     }
     cout << endl;
  }
  char getcAt(int n){
    if( n > block_size || n < 0)
       return '0';
    return data[n];  
  }
  void putcAt(int n, char c){
    if( n > block_size || n < 0)
       return;
    data[n] = c;  
  }
}; 
#endif
