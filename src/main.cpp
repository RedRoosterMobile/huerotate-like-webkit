#define PI 3.141592653589793

#include <iostream>
#include <FreeImage.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using std::cout;
using std::endl;
using std::string;
using std::atoi;

// bit depth of image
#define BPP 24

double clamp(double num) {
    if (num < 0.0) {
        return 0.0;
    } else if (num > 255.0){
        return 255.0;
    } else {
        return num;
    }
}
//========================================================================
int main(int argc, char* argv[]){
    
    // cout <<  "argc " << argc << endl;

    if (argc < 4) {
        cout << "usage: " << argv[0] << " [angle_deg] [in_image] [out_image]" << endl;
        exit(1);
    }
    // cout <<  "command: " << argv[0] << " " << argv[1] << " " << argv[2] << " " << argv[3] << endl;

    string in_image_s(argv[2]);
    string out_image_s(argv[3]);
    int angle = atoi(argv[1]);
    
    // causes a segfault 11 .. sometimes
    //cout << "FreeImage version: " << FreeImage_GetVersion() << endl;
    
    const char* in_image = in_image_s.c_str();
    cout << "loading: " << in_image << endl;

    // has to be at the beginning
    FreeImage_Initialise();

    RGBQUAD color;
    
    FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType(in_image), in_image, 0);
    
    unsigned int w = FreeImage_GetWidth(image);
    unsigned int h = FreeImage_GetHeight(image);
    
    printf("Width: %u Height: %u\n", w, h);
    
    // iternate pixels
    FIBITMAP* bitmap = FreeImage_Allocate(w, h, BPP);
    for ( int i =0; i<w; i++) {
        for ( int j =0; j<h; j++) {
            
            FreeImage_GetPixelColor(image, i, j, &color);
            
            // START CALCULATE HUE

            double cosv,sinv;
            cosv = cos(angle * PI / 180);
            sinv = sin(angle * PI / 180);
            double matrix [9] = {
                1, 0, 0,   // Reds
                0, 1, 0,   // Greens
                0, 0, 1    // Blues
            };
            
            matrix[0] = 0.213 + cosv * 0.787 - sinv * 0.213;
            matrix[1] = 0.715 - cosv * 0.715 - sinv * 0.715;
            matrix[2] = 0.072 - cosv * 0.072 + sinv * 0.928;
            
            matrix[3] = 0.213 - cosv * 0.213 + sinv * 0.143;
            matrix[4] = 0.715 + cosv * 0.285 + sinv * 0.140;
            matrix[5] = 0.072 - cosv * 0.072 - sinv * 0.283;
            
            matrix[6] = 0.213 - cosv * 0.213 - sinv * 0.787;
            matrix[7] = 0.715 - cosv * 0.715 + sinv * 0.715;
            matrix[8] = 0.072 + cosv * 0.928 + sinv * 0.072;
            
            // todo: this should be unneccessary
            double r,g,b;
            r = (double)color.rgbRed;
            g = (double)color.rgbGreen;
            b = (double)color.rgbBlue;
            
            color.rgbRed = clamp(matrix[0] * r + matrix[1] * g + matrix[2] * b);
            color.rgbGreen = clamp(matrix[3] * r + matrix[4] * g + matrix[5] * b);
            color.rgbBlue = clamp(matrix[6] * r + matrix[7] * g + matrix[8] * b);
            
            // END CALCULATE HUE
            
            FreeImage_SetPixelColor ( bitmap , i , j ,&color );
        }
    }
    // save new image
    if ( FreeImage_Save (FIF_PNG, bitmap , out_image_s.c_str() , 0 )) {
        cout << "Image successfully saved to " << out_image_s << endl;
    } else {
        cout << "ERROR converting image" << endl;
        exit(1);
    }

    // has to be at the end
    FreeImage_DeInitialise();

    return 0;
}
