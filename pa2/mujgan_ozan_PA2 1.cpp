#include <iostream>
#include <string>
#include<fstream>
#include<vector>
using namespace std;
class OpenImage
{
private:
    //for read file function
    string file_name;
    int max_colour_value;//3. lines in file
    int width;
    int height;
    string format;//1. lines in file "P3"

    //for convert_grayscale function
    vector<vector<vector<int>>> gray;//3d vector to assign grayscale values
    vector<vector<vector<int>>> values;//3d vector that will hold the data in the file

public:
    void  read_file(string file)
    {
        file_name = file;
        ifstream infile(file_name);
       
        infile >> format >> width >> height >> max_colour_value;//read the first 3 lines in the file and assign the value
       
        
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

    void  convert_grayscale(float c_r, float c_g, float c_b)
    {
        gray.resize(height, vector<vector<int>>(width, vector<int>(3)));//vector resizing
        for (int x = 0; x < height; x++) {
            for (int y = 0; y < width; y++) {
                for(int z=0;z<3;z++){
                gray[x][y][z] = c_r * values[x][y][0] + c_g * values[x][y][1] + c_b * values[x][y][2];//calculating for grayscale
               //if value higher than 255 ,it will be equal to 255
                if (gray[x][y][z] > max_colour_value) {
                    gray[x][y][z] = max_colour_value;
                }
                }
            }
        }
        
    

    }
    //saving and using the data we created to grayscale in the output file
   void saved_image(string output_file){

        ofstream outfile(output_file);
        outfile<<format<<endl;//format name writing in the first line of the file
        outfile<<width<<" "<<height<<endl;
        outfile<<max_colour_value<<endl;
        for (int x = 0; x < height; x++) {
            for (int y = 0; y < width; y++) {
                for (int z = 0; z < 3; z++) {
                    outfile<<gray[x][y][z]<<" ";
                }
            }
            outfile << endl;
        }
    }
};




int main() {
    int choice;
    string fileName;
    OpenImage r;
    while (true) {
        // print main menu
        cout << "MAIN MENU"<<endl;
        cout << "0 - Exit"<<endl;
        cout << "1 - Open An Image(D)"<<endl;
        cout << "2 - Save Image Data(D)"<<endl;
        cout << "3 - Scripts(D) "<<endl;
        cin >>choice;

        if (choice == 0) {
            // exit the program
            break;
        } else if (choice == 1) {
            // open an image
            while (true) {
                cout << "OPEN AN IMAGE MENU"<<endl;
                cout << "0 - UP"<<endl;
                cout << "1 - Enter The Name Of The Image File"<<endl;
                cin >> choice;

                if (choice == 0) {
                    // go back to the main menu
                    break;
                } else if (choice == 1) {
                    // prompt for the file name
                    string file_name;
                    
                    cin >> file_name;

                    
                    r.read_file(file_name);

                } else {
                    break;
                }
            }
        }
         else if (choice == 2) {
            // save image data
            while (true) {
                cout << "SAVE IMAGE DATA MENU"<<endl;
                cout << "0 - UP"<<endl;
                cout << "1 - Enter A File Name"<<endl;
                cin >> choice;


                if (choice == 0) {
                    // go back to the main menu
                    break;
                } else if (choice == 1) {
                    // prompt for the file name
                    
                    cin >> fileName;

                    r.saved_image(fileName);


                    // save the image data to the file
                    
                } else {
                    break;
                }
            }
        } else if (choice == 3) {
            // scripts
            while (true) {
                cout << "SCRIPTS MENU"<<endl;
                cout << "0 - UP"<<endl;
                cout << "1 - Convert To Grayscale(D)"<<endl;
                cin >> choice;

                if (choice == 0) {
                    // go back to the main menu
                    break;
                } else if (choice == 1) {
                    // convert to grayscale
                    while (true) {
                        cout << "CONVERT TO GRAYSCALE MENU"<<endl;
                        cout << "0 - UP"<<endl;
                         cout<<"1 - Enter Coefficients For RED GREEN And BLUE Channels."<<endl;
                          

                        cin >> choice;

                        if (choice == 0) {
                            // go back to the scripts menu
                            break;
                        } else if (choice == 1) {
                            // prompt for the coefficients
                            
                           
                            float c_r, c_g, c_b;
                        do {
                         cout << "Enter coefficients for RED, GREEN, and BLUE channels (three floats between 0 and 1): "<<endl;
                         cin >> c_r >> c_g >> c_b;
                        } while (c_r < 0.0 || c_r >= 1.0 || c_g < 0.0 || c_g >= 1.0 || c_b < 0.0 || c_b >=1.0);
                        //if any of entered values are not in the range of[0,1),check promt again
                            
                            
                            r.convert_grayscale(c_r,c_g,c_b);


                            // perform the conversion and print the result
                        } else {
                            break;
                        }
                    }
                } else {
                    break;
                }
            }
        } else {
            break;
        }
    }

    return 0;
}
