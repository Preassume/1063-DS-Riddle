/**
* @ProgramName: Program-1
* @Author: Austin Riddle
* @Description: 
*     This program reads in images stored as rgb values in a space delimited file format.
* 	The program can flip an image horizontally or vertically, and it can convert a color
* 	image into grayscale.
* @Course: 1063 Data Structures
* @Semester: Spring 2017
* @Date: 09/02/2016
*/

#include<iostream>
#include<fstream>
#include<math.h>
using namespace std;

/**
Structure to hold an rgb value
*/
struct rgb{
    int r;
    int g;
    int b;
	rgb(){
		r = 0;
		g = 0;
		b = 0;
	}
};

/**
* @FunctionName: flipVert
* @Description: 
*     Loops through a 2D array and writes its contents to the output file
* 	  with the rows in reverse order
* @Params:
*    rgb** imgArray - 2D array holding rgb values
*    int width - width of image
*    int height - height of image
*    ofstream ofile - output file of new image
* @Returns:
*    void
*/
void flipVert(rgb** imgArray,int width,int height, ofstream &ofile){
    //Write out the data to a new file in a different order
    ofile<<width<<" "<<height<<'\n';
    for(int i = (height - 1); i >= 0; i--){
        for(int j = 0; j < width; j++){
            ofile<<imgArray[i][j].r<<" "<<imgArray[i][j].g<<" "<<imgArray[i][j].b<<" ";
        }
        ofile<<'\n';
    }
}

/**
* @FunctionName: flipHorz
* @Description: 
*     Loops through a 2D array and writes its contents to the output file
* 	  with the columns in reverse order
* @Params:
*    rgb** imgArray - 2D array holding rgb values
*    int width - width of image
*    int height - height of image
*    ofstream ofile - output file of new image
* @Returns:
*    void
*/
void flipHorz(rgb** imgArray,int width,int height, ofstream &ofile){
    //Write out the data to a new file in a different order
    ofile<<width<<" "<<height<<'\n';
    for(int i = 0; i < height; i++){
        for(int j = (width - 1); j >= 0; j--){
            ofile<<imgArray[i][j].r<<" "<<imgArray[i][j].g<<" "<<imgArray[i][j].b<<" ";
        }
        ofile<<'\n';
    }
}

/**
* @FunctionName: grayScale
* @Description: 
*    Loops through a 2D array and turns every RGB value into its grayscale equivalent,
*    then it writes the new grayscale image to the output file.
* @Params:
*    rgb** imgArray - 2D array holding rgb values
*    int width - width of image
*    int height - height of image
*    int gray - integer used to store grayscale value
*    ofstream ofile - output file of new image
* @Returns:
*    void
*/
void grayScale(rgb** imgArray,int width,int height, ofstream &ofile){
    int gray;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            gray = (imgArray[i][j].r + imgArray[i][j].g + imgArray[i][j].b) / 3;
			imgArray[i][j].r = gray;
			imgArray[i][j].g = gray;
			imgArray[i][j].b = gray;
        }
    }
    //Write out our grayscale data to a new file
    ofile<<width<<" "<<height<<'\n';
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            ofile<<imgArray[i][j].r<<" "<<imgArray[i][j].g<<" "<<imgArray[i][j].b<<" ";
        }
        ofile<<'\n';
    }
}

/**
* @FunctionName: main
* @Description: 
* 	  Creates a 2D array called imgArray.  Then, it loads the image file
*     (in text form) to imgArray.  It will then display the selection menu,
*     and get the user's selection input.  The user's input is used to call
*     the other functions.
* @Params:
*    rgb** imgArray - 2D array holding rgb values
*    int width - width of image
*    int height - height of image
* 	 int selection - user input for menu
* 	 ifstream ifile - input file of original image
*    ofstream ofile - output file of new image
* @Returns:
*    int
*/
int main(){
    ifstream ifile;          //Input / output files
    ofstream ofile;
    ifile.open("smile.txt");
    ofile.open("smile2.txt");   
    
    int width;               //width of image
    int height;              //height of image
    
    rgb **imgArray;         //Pointer var for our 2D array because we         
                            //don't know how big the image will be!

    ifile>>width>>height;   //Read in width and height from top of input file
                            //We need this so we can make the array the right 
                            //size. After we get these two values, we can
                            //now allocate memory for our 2D array.

    imgArray = new rgb*[height];    //This array points to every row

    for(int i=0;i<height;i++){
        imgArray[i] = new rgb[width]; //Now allocate each row of rgb's
    }
    
    //Read the color data in from our txt file
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            ifile>>imgArray[i][j].r>>imgArray[i][j].g>>imgArray[i][j].b;            
        }
    }
	
	cout << "Austin Riddle\nSimple image manipulation software for CMPS 1063\n\n"
		<< "Please select one of the following:\n\n"\
		<< "1.) Vertically flip image\n"
		<< "2.) Horizontally flip image\n"
		<< "3.) Convert image into grayscale\n"
		<< "4.) Exit\n";
		int input = 0;
		cin >> input;
		switch (input)
		{
			case 1:
				flipVert(imgArray, width, height, ofile);
				cout << "Done. The image has now been flipped vertically.\n";
				break;
			case 2:
				flipHorz(imgArray, width, height, ofile);
				cout << "Done. The image has now been flipped horizontally.\n";
				break;
			case 3:
				grayScale(imgArray, width, height, ofile);
				cout << "Done. The image is now grayscale.\n";
				break;
			default:
				cout << "Exiting...\n";
				break;
		}
  return 0;
}
