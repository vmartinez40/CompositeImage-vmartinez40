/* Victor Martinez's Composite Image

Steps to complete program
1)Ask user for image name, until they input 'DONE' or reached a max of 10 images
2)Check if filename exists or if it has the same width and height as the first image
3)Check if user provided at least two images of the same hieght and width
4)Print error and explanations for errors in 2/3
5)Combine image and get the average RGB of each Pixel
6)Display progress report of how many images have loaded
7) Save file as 'composite-vmartinez40.bmp'

*/

#include "bitmap.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

//Prototypes

//Asks for a filename until user inputs DONE or reaches a max of 10 images and returns what images are used into a matrix
vector<string> askFileName();


//Recieves the vector, then checks if at least two images provied have the same dimensions, and returns an error message
int errorAtLeast ( vector <string> & files);

//Recieves a 3d vector of images and its pixels, averages the rgb of all the images, returns a 2d vector of all of the images put together
vector < vector<Pixel> > combineImage (vector <string> & files);

//Recieves the combined image, then saves it as combined image
void saveToUsername(vector <vector <Pixel> > finalImage);

int main() 
{
  /*
  vector <vector<Pixel> > bmp;
  vector< vector <vector<Pixel> > >vector_of_bmps;
  vector_of_bmps.push_back(bmp);
  bmp = combineImage(vector_of_bmps);*/

  vector < string > files = askFileName();
  errorAtLeast(files);
  vector <vector <Pixel> > finalImage = combineImage(files);
  //saveToUsername(finalImage);
}

vector<string> askFileName()
{
    string filename;
    vector <string> files;
    int validNum = 0;
    while(validNum < 10)
    {
        cout<<"Enter filename"<<endl;
        cin>>filename;
        if(filename == "DONE")
        {
            break;
        }
        Bitmap image;
        image.open(filename);
        bool validBmp = image.isImage();
        if(validBmp == true && validNum > 0)
        {
            Bitmap image;
            Bitmap cimage;
            bool errorDimensions = true;
            image.open(files[0]);
            vector <vector <Pixel> > firstImage;
            firstImage = image.toPixelMatrix();
            cimage.open(filename);
            vector <vector <Pixel> > currentImage;
            currentImage = cimage.toPixelMatrix();
            if( firstImage.size() == currentImage.size() && firstImage[0].size() == currentImage[0].size() )
            {
                files.push_back(filename);
                validNum++;
            }
            else
            {
                cout<<filename<<" does not have the same dimensions as the first image"<<endl;
            }
        }
        if(validBmp == true && validNum == 0)
        {
            files.push_back(filename);
            validNum++;
        }
        if(validBmp == false)
        {
            cout<<filename<<" is not a valid Image"<<endl;
        }
    }
    cout<<files.size()<<endl;
    return files;
}

int errorAtLeast (vector <string> & files)
{
    int validFiles = files.size();
    if(validFiles < 1)
    {
        cout<<"A composite image can not be created"<<endl;
        return 0;
    }
} 

vector<vector<Pixel> > combineImage (vector <string> & files)
{
    Bitmap image;
    Pixel rgb;
    image.open(files[0]);
    vector <vector <Pixel> > finalImage;
    finalImage = image.toPixelMatrix();
   
    for(int r = 0;r<finalImage.size();r++)
    {
        for(int c = 0;c < finalImage[0].size();c++)
        {
                finalImage[r][c].red = 0;
                finalImage[r][c].green = 0;
                finalImage[r][c].blue = 0;
        }
    }
    for(int f = 0; f<files.size();f++)
    {
        Bitmap cimage;
        cimage.open(files[f]);
        vector <vector <Pixel> > tempImage;
        tempImage = cimage.toPixelMatrix();
        cout<<files.size()<<endl;
        cout<<tempImage.size()<<endl;
        cout<<tempImage[0].size()<<endl;
        for(int row = 0;row<tempImage.size();row++)
        {
            for(int col = 0;col<tempImage[0].size();col++)
            {
                finalImage[row][col].red += tempImage[row][col].red;
                finalImage[row][col].green += tempImage[row][col].green;
                finalImage[row][col].blue += tempImage[row][col].blue;
            }
        }
        cout<<"The "<<f+1<<"st image has been loaded"<<endl;
    }
    for(int i = 0;i<finalImage.size();i++)
    {
        for(int j = 0;j<finalImage[0].size();j++)
        {
            finalImage[i][j].red /= files.size();
            finalImage[i][j].blue /= files.size();
            finalImage[i][j].green /= files.size();
        }
    }
    image.fromPixelMatrix(finalImage);
    image.save("composite-vmartinez40.bmp");
    cout<<"Your composite image was saved!"<<endl;
       
    return finalImage;
}

void saveToUsername (vector <vector <Pixel> > finalImage)
{
}
