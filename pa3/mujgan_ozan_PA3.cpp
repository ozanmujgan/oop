#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

class ppmImage
{
private:
    
    string file_name;
    int maxVal;//3. lines in file
    int width;
    int height;
    string format;//1. lines in file "P3"
     
     vector<vector<vector<int>>> values;
   

public:
	ppmImage() : width(0), height(0)  {}   //default constructor
    /*A constructor which creates an object according to the given dimensions. The image data should be
allocated an initialized in a way to represent a blank (white) image.*/
     ppmImage(int h,int w,string f,int max){
        format=f;
        maxVal=max;
        height=h;
        width=w;
        
        values.resize(height, vector<vector<int>>(width, vector<int>(3)));
        for (int x = 0; x < height; ++x)
        {
            for (int y = 0; y< width; ++y)
            {
                for (int z = 0; z < 3; ++z)
                {
                    values[x][y][z]=255;
                }
            }
        }
    }
    /*A constructor which takes a ppm file name as argument and creates object form file.*/

	ppmImage(const string& file){
        file_name=file;
        ifstream infile(file_name);
        if (!(infile.is_open()))
        {
            
            return;
        }
           file_name = file;
           infile >> format >> width >> height >> maxVal;//read the first 3 lines in the file and assign the value
       
        
            values.resize(height, vector<vector<int>>(width, vector<int>(3)));//vector resizing

            int value;
            for (int x = 0; x < height; x++){
                for (int y = 0; y < width; y++){
                    for (int z = 0; z < 3; z++) {
                    infile >> value; // read a values from file
                    values[x][y][z] = value; // assign values from file to 3d vector
                    }
                }
            }

	       infile.close(); // File is closed
    } 



    void  read_file(string file)
    {
        file_name = file;
        ifstream infile(file_name);
       
        infile >> format >> width >> height >> maxVal;//read the first 3 lines in the file and assign the value
       
        
        values.resize(height, vector<vector<int>>(width, vector<int>(3)));//vector resizing
        int value;
        for (int x = 0; x < height; x++) {
            for (int y = 0; y < width; y++) {
                for (int z = 0; z < 3; z++) {
                    infile >> value; // read a values from file
                    values[x][y][z] = value; // assign values from file to 3d vector
                }
            }
        }
       
        infile.close(); // File is closed
    }

    
   

    ppmImage operator+(const ppmImage& other) const{
        //contol the objects of dimensions whether if or not equals to other object dimensions
        if (width != other.width || height != other.height) {
        exit(0);
        }
        //Constructor usage for assigning the width, height, maximum color value and format name of the new object 
        ppmImage temp(height,width,format,maxVal);
         temp.values.resize(height, vector<vector<int>>(width, vector<int>(3)));//resizing vectors
        for (int x = 0; x < height; x++) {
                for (int y = 0; y < width; y++) {
                    for (int z = 0; z < 3; z++) {
                   
                    temp.values[x][y][z]=values[x][y][z]+other.values[x][y][z]; //add the datas of objects
                    if (temp.values[x][y][z]>255)
                    {
                        temp.values[x][y][z]=255;//if the addition is higher than 255 ,the result is 255
                    }
                    }
                }
            }
            return temp;

    }
    ppmImage operator-(const ppmImage& other) const{
        //contol the objects of dimensions whether if or not equals to other object dimensions
        if (width != other.width || height != other.height) {
        exit(0);
        }
        //Constructor usage for assigning the width, height, maximum color value and format name of the new object 
        ppmImage temp(height,width,format,maxVal);
        temp.values.resize(height, vector<vector<int>>(width, vector<int>(3)));//resizing vectors
        for (int x = 0; x < height; x++) {
                for (int y = 0; y < width; y++) {
                    for (int z = 0; z < 3; z++) {
                   
                    temp.values[x][y][z]=values[x][y][z]-other.values[x][y][z]; //substruction operations
                    if (temp.values[x][y][z]<0)//if the result of the subtraction is negative, the result is 0 control
                    {
                        temp.values[x][y][z]=0;
                    }
                    }
                }
            }
            return temp;
    }
    void saved_image(string output_file){

        ofstream outfile(output_file);
        outfile<<format<<endl;//format name writing in the first line of the file
        outfile<<width<<" "<<height<<endl;
        outfile<<maxVal<<endl;
        for (int x = 0; x < height; x++) {
            for (int y = 0; y < width; y++) {
                for (int z = 0; z < 3; z++) {
                    outfile<<values[x][y][z]<<" ";
                }
            }
            outfile << endl;
            }
        
    }

    int& operator()(int h, int w, int color)//funtion call operator
    {
    return values[h][w][color];
    }

    int operator()(int row, int column,int color_choice) const{
        return values[row][column][color_choice];
    }



//The purpose of this overloaded operator function is to define how a ppmImage object should be displayed when it is output to an ostream object, such as cout.

    friend ostream& operator<<(ostream& os, const ppmImage& img);

    void setFormat(string f) {
    format = f;
    }
    /*Accessor and mutator functions for private member data*/

    void setWidth(int w) { width = w; }
    void setHeight(int h) { height = h; }
    void setMaxValue(int m) { maxVal = m; }

    string getFileName() const{return file_name; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getMaxValue() const { return maxVal; }
    string getFormat() const{return format; }
    vector<vector<vector<int>>> getValues() const { return values; }
    
};
/*operator <<: Prints image details and image data to stdout. This is similar to saving the image to a file.
Allows cascading.*/
ostream& operator<<(ostream& os, const ppmImage& img) {
    os << "File name: " << img.getFileName() << endl;
    os << "Format: " << img.getFormat() << endl;
    os << "Width: " << img.getWidth() << endl;
    os << "Height: " << img.getHeight() << endl;
    os << "Maximum value: " << img.getMaxValue() << endl;
    os << "Image data:" << endl;

    
    for (int i = 0; i < img.getHeight(); i++) {
        for (int j = 0; j < img.getWidth(); j++) {
            for (int k = 0; k < 3; k++) {
                os << img.values[i][j][k] << " ";
            }
            os << " ";
        }
        os << endl;
    }

    return os;

}

    int read_ppm(const string source_ppm_file_name, ppmImage& destination_object);
    int write_ppm(const string destination_ppm_file_name, const ppmImage& source_object);
    int test_addition(const string filename_image1, const string filename_image2, const string filename_image3);
    int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3);
    int test_print(const string filename_image1);
    int swap_channels(ppmImage& image_object_to_be_modified, int swap_choice);
    ppmImage single_color(const ppmImage& source, int color_choice);


int main(int argc, char *argv[])
{
     
    string ppm_file_name1, ppm_file_name2, ppm_file_name3;
    /*check for number of command line arguments
    the first argument is going to be choice number
    the second argument is going to be a ppm_file_name1
    the third argument is going to be ppm_file_name2 (this is optional)
    the third argument is going to be ppm_file_name3*/
    ppm_file_name1 = argv[2];
    ppm_file_name2 = argv[3];
    ppm_file_name3 = argv[4];
   
    //read a data from file using constructor
    ppmImage f1(ppm_file_name1);
    ppmImage f2(ppm_file_name2);
   

    ppmImage destination_object;
    ppmImage newobj;
    //I used atoi function since the first command line argument is number
    int num=atoi(argv[1]);
   // test_print(ppm_file_name1);

    // if choice number is 1
    // check the existence of the optional arguments. If they are not given, exit
     if (num==1) {
        test_addition(ppm_file_name1, ppm_file_name2, ppm_file_name3);
    }




    // if choice number is 2
    // check the existence of the optional arguments. If they are not given, exit

     else if (num==2) {
        test_subtraction(ppm_file_name1, ppm_file_name2, ppm_file_name3);
    }
    




    // if choice number is 3
    //read ppm_file_name1 using function read_ppm
    //swap red and blue channels
    //write the updated data to a file named "ppm_file_name2". use write_ppm function.

     else if (num==3) {
        read_ppm(ppm_file_name1, destination_object);
        swap_channels(destination_object, 2);
        write_ppm(ppm_file_name2, destination_object);
    }




    // if choice number is 4
    //read ppm_file_name1 using function read_ppm
    //swap green and blue channels. use swap_channels function
    //write the updated data to a file named "ppm_file_name2". use write_ppm function.

    else if (num==4) {
        read_ppm(ppm_file_name1, destination_object);
        swap_channels(destination_object, 3);
        write_ppm(ppm_file_name2, destination_object);
    }






    // if choice number is 5
    // read ppm_file_name1 using function read_ppm
    // create a new object which only contains red channel data of the file read. use single_color function
    // write the data of the new object to a file named "ppm_file_name2". use write_ppm function.


    else if (num==5) {
        ppmImage newobj;
        read_ppm(ppm_file_name1, destination_object);
        newobj=single_color( destination_object, 1);
        write_ppm(ppm_file_name2, newobj);
    }





    // if choice number is 6
    // read ppm_file_name1 using function read_ppm
    // create a new object which only contains green channel data of the file read. use single_color function
    // write the data of the new object to a file named "ppm_file_name2". use write_ppm function
   else if (num==6) {
      ppmImage newobj;
        read_ppm(ppm_file_name1, destination_object);
        newobj=single_color(destination_object, 2);
        write_ppm(ppm_file_name2, newobj);
    }




    // if choice number is 7
    // read ppm_file_name1 using function read_ppm
    // create a new object which only contains blue channel data of the file read. use single_color function
    // write the data of the new object to a file named "ppm_file_name2". use write_ppm function.
   else if (num==7) {
      ppmImage newobj;
        read_ppm(ppm_file_name1, destination_object);
        newobj= single_color(destination_object, 3);
        write_ppm(ppm_file_name2, newobj);
    }



    else{
        return 0;
    }



    return 0;
}


int test_addition(const string filename_image1, const string filename_image2, const string filename_image3){
    /*read  datas  of filename_image1 and filename_image2  from file using constructor*/
    ppmImage image1(filename_image1);
    ppmImage image2(filename_image2);
    // reads images from filename_image1 and filename_image2. Adds them and saves the resulting image to filename_image3
    ppmImage image3 =image2+image1;
    //write datas of filename_image3 in file using saved_image function; 
    image3.saved_image(filename_image3);
    return 1;
}



int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3){
/*read  datas  of filename_image1 and filename_image2  from file using constructor*/
    ppmImage image1(filename_image1);
    ppmImage image2(filename_image2);
    // reads images from filename_image1 and filename_image2. Subtracts filename_image2 from filename_image1 saves the resulting image to filename_image3
    ppmImage image3=image2-image1;
    image3.saved_image(filename_image3);
     return 1;
}



int read_ppm(const string source_ppm_file_name, ppmImage& destination_object){
        destination_object.read_file(source_ppm_file_name);

        return 1;
}




int swap_channels(ppmImage& image_object_to_be_modified, int swap_choice){
     if (swap_choice < 1 || swap_choice > 3) {
        return 0;  // Everything is normal, but no swaps needed
    }
    //if swap_choice is 1: swaps red and green
    if (swap_choice==1)
        {
              for (int x = 0; x < image_object_to_be_modified.getHeight(); x++) {
                for (int y = 0; y < image_object_to_be_modified.getWidth(); y++) {
                    int temp=image_object_to_be_modified(x,y,0);
                    image_object_to_be_modified(x,y,0)=image_object_to_be_modified(x,y,1);
                    image_object_to_be_modified(x,y,1)=temp;
                }
            }
        }
        //if swap_choice is 2: swaps red and blue
        else if (swap_choice==2)
        {
             for (int x = 0; x < image_object_to_be_modified.getHeight(); x++) {
                for (int y = 0; y < image_object_to_be_modified.getWidth(); y++) {
                    int temp=image_object_to_be_modified(x,y,0);
                    image_object_to_be_modified(x,y,0)=image_object_to_be_modified(x,y,2);
                    image_object_to_be_modified(x,y,2)=temp;
                }
            }
        }
       // if swap_choice is 3: swaps green and blue

        else{
             for (int x = 0; x < image_object_to_be_modified.getHeight(); x++) {
                for (int y = 0; y < image_object_to_be_modified.getWidth(); y++) {
                    int temp=image_object_to_be_modified(x,y,1);
                    image_object_to_be_modified(x,y,1)=image_object_to_be_modified(x,y,2);
                    image_object_to_be_modified(x,y,2)=temp;
                }
            }
        }


        return 1;
}



  int write_ppm(const string destination_ppm_file_name, const ppmImage& source_object){ 

    ofstream outfile(destination_ppm_file_name);
        outfile<<source_object.getFormat()<<endl;//format name writing in the first line of the file
        outfile<<source_object.getWidth()<<" "<<source_object.getHeight()<<endl;//write width and height values in file using accessor functions
        outfile<<source_object.getMaxValue()<<endl;//write a max color value in file 
        for (int x = 0; x < source_object.getHeight(); x++) {
            for (int y = 0; y < source_object.getWidth(); y++) {
                for (int z = 0; z < 3; z++) {
                    outfile<<source_object.getValues()[x][y][z]<<" ";//write a values of source_object in file
                }
            }
            outfile << endl;
        }
    return 1;

}





ppmImage single_color(const ppmImage& source, int color_choice) {
    //Constructor usage for assigning the width, height, maximum color value and format name of the new object created in the source object
   ppmImage result(source.getHeight(),source.getWidth(),source.getFormat(),source.getMaxValue());
   

    for (int i = 0; i < source.getHeight(); i++) {
        for (int j = 0; j < source.getWidth(); j++) {
            for (int k = 0; k < 3; k++) {
                if (k == color_choice - 1) {
                    result(i, j, k) = source(i, j, k);//if (color_choice -1) equals to k ,assigns to result object from source object
                } else {
                    result(i, j, k) = 0;//if (color_choice -1) is not equals to k, assigns to 0 the other pixel values
                }
            }
        }
    }

    return result;
}


