/*--------------------------------------------------------------
//Name:         Jose Munoz
//NetID:        jam151830@utdallas.edu
//Course:       CS4348.001
//Project:      Project 3
//Due:          12/01/2018
//File:         Disk.h
//Notes:
--------------------------------------------------------------*/
#ifndef DISK_HH
#define DISK_HH
#include <iostream>
#include <stdlib.h>
#include <string>
#include "main.h"
using namespace std;

class Disk{
 //Attributes
 private:
  int  block;
  int  block_size;
  char data[256][512]; 

 public:
  //Default Constructor
  Disk(){
    block = 256;
    block_size = 512;
    //Disk storage = array of 256 block of size 512 bytes
    //data = new char[block][block_size];
    //initialize the data array 
    for(int i = 0; i < block; i++){
    	for(int j = 0; j < block_size; j++){
      	  data[i][j] = '0';
      }
    }
    //update bitmap to default values
    updateBitmap(0, '1');//file alloc table
    updateBitmap(1, '1');//bitmap 
  }
  //Overloaded Constructors
  //Methods
  void printData(){
    for(int i = 0; i < block; i++){
	cout << i << endl;
	for(int j = 0; j < block_size; j++){    
	  if(j%32 == 0 && j != 0)
	  	cout << endl;
       	  cout << data[i][j];	
	}
	cout << endl;
    }

  } 
  //returns the contents of the given block number
  char* read(int n)
  {
    if(n < 0 || n > block)
       return  NULL;
    char* temp = new char[block_size];
    for(int j = 0; j < block_size; j++){   
        temp[j] = data[n][j];
     }
    return temp; 
  }

  void write(int n, char newBlock[])
  {
     if(n > 256 || n < 0)
        return;
     for(int j = 0; j < block_size; j++){   
        data[n][j] =  newBlock[j];
     }
     updateBitmap(n, '1');//mark this block as full
  }
  //Given a number, it displays the corresponding block 
  void printBitmap(){
     for(int j = 0; j < block; j++){    
	  if(j%32 == 0 && j != 0)
	  	cout << endl;
       	  cout << data[1][j];	
	}
	cout << endl;
  }
  void printFileAllocTable(){
     cout << "FileName\tStartBlock\tLength" << endl;
     for(int j = 0; j < block; j++){      
     	for(int i = 0; i < 8; i++, j++)
       	  cout << data[0][j];
	cout << "\t" << data[0][j+1] << "\t\t" << data[0][j+2] << endl; 
	j+=2;
     }
     cout << endl;
  }
  void displayFile(){
     
  }
  void updateBitmap(int n, char c){
     if(n > 256 || n < 0)
        return;
     data[1][n] = c; 
  }
  void displayBlock(int n){
     cout <<"Block: " <<  n << endl;
     for(int j = 0; j < block_size; j++){    
        if(j%32 == 0 && j != 0)
	  cout << endl;
       	cout << data[n][j];	
     }
     cout << endl;
  }
};
#endif 
