/*---------------------------------------------------------------------------------------
Student:    Jose Munoz
NetID:      jam151830
Course:     CS4348.001
Due:	    12/1/2018
Project:    Project 3 - Disk Allocation Methods
File:       main.cc
Notes:
---------------------------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include "main.h"
#include "Disk.h"
#include "Block.h"
using namespace std;

void printFile(fstream &);
Block* fileFromSystemToDisk(FILE* , int*, int );
void storeFileInDisk(Block*, char ,  string , Disk &, int );
int findNextFreeBlock(Disk &, int& , char );
char getRandomFreeBlock(Disk &); 

int main(int argc, char *argv[])
{
    //Check if user input a file name
    if( argc < 2){
        cout << "Error - Please Enter An Allocatin Mode. " << endl;
        exit(0);
    }
    int mode = -1;
    mode = strcmp(argv[1], "contiguous") == 0? 1: mode;
    mode = strcmp(argv[1], "chained"   ) == 0? 2: mode;
    mode = strcmp(argv[1], "indexed"   ) == 0? 3: mode;
    if(mode == -1){
       cout << "Make sure spelling is corret - contiguous, chained or indexed."; 
       return 0;
    }
    //variables
    //fstream dataFile; //to read from the file
    //ofstream outPutFile; //to write into a file
    string modes[] = {"contiguous", "chained", "indexed"}; 
    //string fName(argv[1]);
    //FILE *dataFile;
    //dataFile = fopen(argv[1], "r");
    //Open the files
    //dataFile.open(argv[1]);
    //outPutFile.open("answers.txt");
    Disk disk;
    int fileSize = 10;
    Block *inputFileData; 
    //new variables
    int opt = 0; //store the user's choice of the main menu
    string option = "";//store the user's choice of the main menu in a string in order to validate it
    //    char result;//store the of weather the input is a valid Roman/Arabic numeral or none
    int numb = 0;
    //temporarily file variables
    FILE *inputFile;
    string fileName = ""; 
   //test
    Block b;
    for(int i = 0; i < 256; i++){
    b.putcAt(i, 'X');

}
    disk.write(5, &b);   
    
    //display mode
    cout << "Mode: " << modes[mode-1] << endl;
//--USER Menu--------------------------------------------------------------------------------------------------
    do
    {
        displayMenu(); //display user interface
        cin >>opt; //get input from user
        cin.ignore(10, '\n');
        //number from user = case
	cout << "Choice: " << opt << endl;
        switch(opt)
        {
        case 1: //Option 1) Display a file
	  //check wether file alllocation table is empty

	  //if empty, display a file given by the user
	  //ask for file name
	  cout << "Enter File Name: "<< endl; 
	  getline(cin, fileName, '\n'); 
	  //get file name 
	  cout << "file Name: " << fileName << endl;
	  //pass in file name and open file 
    	  inputFile = fopen(fileName.c_str(), "r");
	  //check if file opened correctly
	  if(!inputFile){
		cout << "Error - File did not open correctly" << endl;
		break;
	  }
	  //read file and store it in an array
          inputFileData = fileFromSystemToDisk(inputFile, &fileSize, mode);
	  //display file
          cout << "-------------------------Start of File-------------------------"<<endl;
          for(int i = 0; i <fileSize; i++){
             for(int j = 0; j < 512; j++){
	        if( (int)inputFileData[i].getcAt(j) == -1)//if this is the end of file character, stop 
	           break;
                cout <<  inputFileData[i].getcAt(j);
             }
          }
          cout << "---------------------------End of File-------------------------"<<endl;
          fclose(inputFile);
          break;
        case 2: //Option 2) Display a file table
	  disk.displayFileAllocTable();
	  break;
        case 3: //Option 3) Display the free space bitmap
	  disk.displayBitmap();
          break;
        case 4: //Option 4) Display a disk block
	  cout << "Enter Block Number: " << endl;
	  cin >> numb;
	  disk.displayBlock(numb);
	  break;
        case 5: //Option 5) Copy a file from the simulation to a file on the real system
          break;
	case 6: //Option 6) Copy a file from the real system to a file in the simulation
          //ask for file name
	  cout << "Enter File Name: "<< endl; 
	  getline(cin, fileName, '\n'); 
	  //open the file  
    	  inputFile = fopen(fileName.c_str(), "r");
	  //check if file opened correctly
          if(!inputFile){
	     cout << "Error - File did not open correctly" << endl;
	     break;
	  }
	  //read file and store it in temp block an array
          inputFileData = fileFromSystemToDisk(inputFile, &fileSize, mode);

	  cout << "File Name: " << fileName << endl;
	  //store the array of blocks on the disk 
          storeFileInDisk( inputFileData, (char)fileSize,  fileName, disk, mode );
	  cout << "File Sucessfully Copied" << endl;
          fclose(inputFile);
	  break;
	case 7: //Option 7) Delete a file
	  break;
        case 8: //Opiton 8) Exit
	  break;
        default: //Invalid option
	  cout << "\n*Invalid Option*\n";
	  opt = 8;
	  break;
        }//end of switch
    }while(opt !=8);//if user inputs 8, break loop
    //close the all files 
    //dataFile.close();
    //outPutFile.close();
    //fclose(dataFile);

    return 0;
}


/*Function Definitions*/

//displays the menu options when called - no parameters, does not return anything
void displayMenu()
{
        cout << "\n";
        cout << "1) Display a file\n";
        cout << "2) Display the file table\n";
        cout << "3) Display the free space bitmap\n";
        cout << "4) Display a disk block\n";
        cout << "5) Copy a file from the simulation to a file on the real system\n";
        cout << "6) Copy a file from the real system to a file in the simulation\n";
	cout << "7) Delete a file\n";
	cout << "8) Exit\n";
}

//chain allocation - limit it to 10 blocks, max number of chars for file name = 8
//

//validates the user's input for the menu options - takes in a string and checks to see if is a 1,2 or 3
bool validOption(string input)
{
    int size = input.length();
    bool valid = false;
    char chr;
    if (size > 1){//if the string is not a single character, the its not a valid option 
        valid = false;
        return valid;
    }
    else{
        chr = input.at(0);//store the character
    }
    if(!isdigit(chr)){//if its not a digit, then invalid
        valid = false;
        return valid;
    }
    else{
        valid = true;
    }
    if(valid){//if is a digit
        int i = atoi(input.c_str());//convert it to an int
        if ( i > 0 && i<8){//check to see if  within range
            valid = true;//if it is, the it's valid
            return valid;
        }
        else{ //otherwise invalid
            valid = false;
            return valid;
        }
    }
    return valid;
}

void printFile(fstream &dataFile)
{
string line = "";//temporarily stores a numeral
int numb = 0;//temporarily stores a numeral
 
if(dataFile)
    {
        while(!dataFile.eof()) //stop when the pointer reads the end of file bit
        {
            //read the current line and store it
            getline(dataFile, line, '\n'); //store the first line of the file in a string
            if(!line.empty())//if the string "is not empty"
            {
		    cout << line << "\n";                    
		    numb++;
            }//end if
        }//end while loop
    }
    else //file did not open properly
    {
        cout << "Error - The file did not open\n"; //prints error message
	exit(0);
    }
    dataFile.clear(); //clear the EOF bit
}

//given a file pointer and an integer, it copies the contents of the file upto 10 blocks
// and assigns the number of blocks to the integer given. 
Block* fileFromSystemToDisk(FILE* file, int *size, int mode){
    //initialize the array with spaces
    Block* blocks = new Block[10];
    rewind(file); //reset file pointer
    //copy file contents to the array
    int s = 0;
    bool exit = false;
    for( ; s < 10; s++){
       for(int j = 0; j < 512; j++){
         //if this is a in chained mode, skip the last byte
    	 if(feof(file)){ //while not end of file, store the current char
	    s++;
	    exit = true;
	    break;
	 }
         if(mode != 2 && j != 510)
            blocks[s].putcAt(j , getc(file));
       }
       if(exit)
          break;
    }
    cout << "method s = " << s << endl;
    if( s != 10)//if the file did not fill all 10 blocks
    {
    	//create a new shorter array and return it 
	Block* temp = new Block[s+1];
	for(int i = 0; i <= s; i++){
           temp[i].writeBlock(&blocks[i]);
          }
          *size = s;//update the number of blocks, by default is 10
          return temp; //return the shorter block array
    } 
    rewind(file); //rewind the file pointer
    return blocks;//return the array with 10 blocks
}

   //Given a file, split the file and store in the disk in a contigious mode
void storeFileInDisk(Block *fileBlocks, char fileSize,  string fileName, Disk  &disk, int mode){
     //insert file name into the fileallocation table
     char lengthIndex= 19; //the file length char is located at the 10th place of the disk allocation table
     do{
        if( disk.getBlock(0)->getcAt( (int)lengthIndex ) == '0')
	   break; 
	lengthIndex+= 20;//move down a row to check next file length	 
     }while(lengthIndex < 500);
     if( lengthIndex > 500){
     	cout << "Error - File Allocation Table is Full. " << endl;
	return;
     }
     //find the first free block
     
     int totalFreeBlocks = 0;
     unsigned char nearestFreeBlock = 0;
     //if mode == continious
     if(mode == 1)
     {
	//find a continious set of free blocks 
        nearestFreeBlock = findNextFreeBlock( disk, totalFreeBlocks,  fileSize);
	cout << "total free blocks - outside: " << totalFreeBlocks << endl;
        if( totalFreeBlocks < (int)fileSize){
           cout << "Error - Not Enough Free Space in the Disk." << endl;
	   return;
        } 
        //Store the starting block of the file. 
        disk.getBlock(0)->putcAt( (int) lengthIndex -1, (char)  nearestFreeBlock);  
        //store each block continiously
        for(int i = 0; i < (int) fileSize; i++){
	   //write block to disk
     	   disk.write(nearestFreeBlock, &fileBlocks[i]);
           //update bitmap
	   disk.updateBitmap(nearestFreeBlock, '1');
           //increase the nearestfreeblock counter to store the file contigiously
	   nearestFreeBlock++;
        } 
     }else{//the mode is either chained or indexed
        //get a random starting block
        nearestFreeBlock = getRandomFreeBlock(disk); 
        if(mode == 2) //mode is chained 
        { 
           //store the starting block of the file
           disk.getBlock(0)->putcAt( (int) lengthIndex -1, (unsigned char) nearestFreeBlock);
	   unsigned char nextBlockAddress; 
           //loop to store all the blocks 
	   for( int i = 0; i < (int) fileSize; i++){
              //update the bitmap
              disk.updateBitmap(nearestFreeBlock, '1');
              //get the address of the next block
              nextBlockAddress =(char) getRandomFreeBlock(disk);// get the new address
              //store the address of the next block in the current block
              fileBlocks[i].putcAt(510, nextBlockAddress);
	      //store the block in the disk
	      disk.write(nearestFreeBlock, &fileBlocks[i]);
              //update the current address with the next address
              nearestFreeBlock = nextBlockAddress;
           }

        }
        else{ //mode is indexed
        //pick a random starting block to store the addresses of all the blocks
        nearestFreeBlock = getRandomFreeBlock(disk); 
	unsigned char nextBlockAddress; 
        //save the address of the directory block
        int addressBlock = nearestFreeBlock; 
        //get a new address for the first block of the file
        nearestFreeBlock = getRandomFreeBlock(disk); 
        //create a new block for the index table is the size of the file is less than 9 blocks
        Block* directoryBlock = new Block();
        //add it to the file allocation table, along with its size
        if((int) fileSize < 10 && (int) fileSize > 0)
           (int) fileSize++;
        for( int i =  0; i < (int) fileSize; i++){
           //update bitmap
           disk.updateBitmap(nearestFreeBlock, '1');
           //get the address for the next block
           nextBlockAddress =(char) getRandomFreeBlock(disk);// get the new address
           //put the address of the current block on the directoryBlock
           directoryBlock->putcAt(i, nearestFreeBlock);
           //store the block in the disk  
	   disk.write(nearestFreeBlock, &fileBlocks[i]);
           //update the current address with the new address
           nearestFreeBlock = nextBlockAddress;
        }	
        //all the adresses have been store in the directory block, now store the directory block
        disk.write(addressBlock, directoryBlock);
        //store the starting block in the allocation table
        disk.getBlock(0)->putcAt( (int) lengthIndex -1, (unsigned char) addressBlock);

       } 

     }
     //store the file length at the allocation table 
     disk.getBlock(0)->putcAt( (int) lengthIndex, fileSize);
     lengthIndex -= 19;//reset the index to the beginig of the row to store the file name
     int s = fileName.length();//get the number of chars in the string    
     char c;
     for(int i = 0; i < 18; i++){ //18 iterations = max number of chars per file name
        c = s > i?(fileName.at(i)):' '; //if the string is less than 18, store spaces until end of loop
        disk.getBlock(0)->putcAt( (int)lengthIndex + i, c);//store the current char
     }
     return; 
} 

void fileFromDiskToSystem(Block *fileBlocks, char fileSize,  string fileName, Disk  &disk){
}


int findNextFreeBlock(Disk &disk, int &totalFreeBlocks, char fileSize){
   //look at the bitmap block 
   char c; 
   bool flag = true;
   //used to return 1.- the closest free block set that matches the given size, 2.- the beggining of the largest set of free blocks, 3.- its size
   int closest = 0;
   totalFreeBlocks = 0;
   for(int i =0; i< 256; i++){
      c = disk.getBlock(1)->getcAt(i);
      if(c =='0') totalFreeBlocks++;
   }
   //traverse top-down the bitmap to find the nearest free block 
   for(int i = 0; i < 256; i++){
      c = disk.getBlock(1)->getcAt(i);
      if( c == '0')
      {
	closest = i; //starting point
	 for(int j = i + 1; j < (fileSize + i); j++)
         { 
            c = disk.getBlock(1)->getcAt(j);
            flag = (c == '1')?false:flag;  
         }
     	 if(flag)
	   return closest;
      }
      flag = true;
   }
   return -1; //if main loop ends, then there is not a continious set large enough in the disk
}


void storeFileContigious(Disk &disk, Block* fileBlocks, char fileSize){
}

void storeFileChained(Disk &disk, Block* fileBlocks, char fileSize){
} 

void storeFileIndexed(Disk &disk, Block* fileBlocks, char fileSize){
}
//generates a random number b/w 2 and 256, the checks the bitmap to see if that block is empty
char getRandomFreeBlock(Disk &disk ){
   int numb = 2;
   int min = 2;
   int maximum = 256;
   for( int i = 0; i < 10; i++){
     numb = (rand() % (maximum + 1 - min)) + min;
     if(disk.getBlock(1)->getcAt(numb) == '0' && i == 4){
        cout << "numb: " << numb << " i= " << i << endl;
	break;
      }
   }
   return numb;	
}


//disk has two methods, diks can only read an entire block or write an entire block, is an unintelliget device
//minimal design - 3 objects
//UI
//takes input and talks to diks
//Disk
//
