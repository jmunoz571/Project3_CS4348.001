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
#include <cstdlib>
#include "main.h"
using namespace std;

int main(int argc, char *argv[])
{
    //Check if user input a file name
    if( argc < 2){
        cout << "Error - Please Enter A File Name. " << endl;
        exit(0);
    }
    //variables
    fstream dataFile; //to read from the file
    //ofstream outPutFile; //to write into a file
    string line = ""; //used to temporarily store a string
    string numeral = "";//temporarily stores a numeral
    int numb = 0;//temporarily stores a numeral
    //char chr;
	//convert c string to string
    //string fName(argv[1]);

    //Open the files
    dataFile.open(argv[1]);
    //outPutFile.open("answers.txt");

    //check to see if file opened correctly
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


//--USER Menu--------------------------------------------------------------------------------------------------

    //new variables
    int opt = 0; //store the user's choice of the main menu
    string option = "";//store the user's choice of the main menu in a string in order to validate it
    //    char result;//store the of weather the input is a valid Roman/Arabic numeral or none
    do
    {
        displayMenu(); //display user interface
        cin >>opt; //get input from user
        cin.ignore(10, '\n');
        //number from user = case
        switch(opt)
        {
        case 1: //Option 1) Display a file
          break;
        case 2: //Option 2) Display a file table
          break;
        case 3: //Option 3) Display the free space bitmap
          break;
        case 4: //Option 4) Display a disk block
          break;
        case 5: //Option 5) Copy a file from the simulation to a file on the real system
          break;
	case 6: //Option 6) Copy a file from the real system to a file in the simulation
	  break;
	case 7: //Option 7) Delete a file
	  break;
        case 8: //Opiton 8) Exit
	  break;
        default: //Invalid option
	  cout << "\n*Invalid Option*\n";
	  break;
        }//end of switch
    }while(opt !=8);//if user inputs 8, break loop

    //close the all files
    dataFile.close();
    //outPutFile.close();
    char c;
    cout << "Enter Char: \n";
    cin >> c;
    printf("Your Char is: %d - %c \n",c, c);
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



//disk has two methods, diks can only read an entire block or write an entire block, is an unintelliget device
//minimal design - 3 objects
//UI
//takes input and talks to diks
//Disk
//19641 - scantron
