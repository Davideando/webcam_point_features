
//OpenCV 
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"

//std
#include <iostream>
#include <cstdlib>
#include <vector>

//consts
const unsigned int MIN_NUM_FEATURES = 300; //minimum number of point fetaures
const unsigned int SAMPLE_PARTS = 4; // Numero de partes en la que dividirá la imagen en X y en Y

int main(int argc, char *argv[]) 
{
    cv::VideoCapture camera; //OpenCV video capture object
    cv::Mat image; //OpenCV image object
	int cam_id; //camera id . Associated to device number in /dev/videoX
    cv::Ptr<cv::ORB> orb_detector = cv::ORB::create(); //ORB point feature detector
    orb_detector->setMaxFeatures(MIN_NUM_FEATURES);
    std::vector<cv::KeyPoint> point_set; //set of point features
    cv::Mat descriptor_set; //set of descriptors, for each feature there is an associated descriptor 
	
	//check user args
	switch(argc)
	{
		case 1: //no argument provided, so try /dev/video0
			cam_id = 0;  
			break; 
		case 2: //an argument is provided. Get it and set cam_id
			cam_id = atoi(argv[1]);
			break; 
		default: 
			std::cout << "Invalid number of arguments. Call program as: webcam_capture [video_device_id]. " << std::endl; 
			std::cout << "EXIT program." << std::endl; 
			break; 
	}
	
	//advertising to the user 
	std::cout << "Opening video device " << cam_id << std::endl;

    //open the video stream and make sure it's opened
    if( !camera.open(cam_id) ) 
	{
        std::cout << "Error opening the camera. May be invalid device id. EXIT program." << std::endl;
        return -1;
    }

    // Se adquiere el tamaño de las imagenes que provienen de la cámara
    int camera_width = camera.get(CV_CAP_PROP_FRAME_WIDTH);
    int camera_height = camera.get(CV_CAP_PROP_FRAME_HEIGHT);

    //Process loop. Capture and point feature extraction. User can quit pressing a key
    while(1)
	{
		//Read image and check it. Blocking call up to a new image arrives from camera.
        if(!camera.read(image)) 
		{
            std::cout << "No image" << std::endl;
            cv::waitKey();
        }

        // Se crea un bucle para recorrer todos los rincones de la imagen
        // en este caso se dividirá la imagen por los trozos que indique la constante 
        // SAMPLE_PARTS.
        for(int i = 0; i < SAMPLE_PARTS; i++)
        {
        	for(int j = 0; j < SAMPLE_PARTS; j++)
        	{
		    //******************** Se define la máscara****************//

		        // Se define una mascará de un canal de datos de 8 bits
		        cv::Mat mascara = cv::Mat::zeros(image.size(), CV_8UC1);

		        // Se define un area de interes, que será la mascara
		        cv::Mat roi(mascara, cv::Rect(0+i*camera_width/SAMPLE_PARTS,0+j*camera_height/SAMPLE_PARTS,camera_width/SAMPLE_PARTS,camera_height/SAMPLE_PARTS));
		        // Se colocan los bytes de la zona donde se quiere aplicar la máscara
		        // a 1, y se deja el resto a 0.
		        roi = cv::Scalar(255,255,255);
		        // Como la máscara y el area de interes (roi) están enlazados, todos los cambios que se realizen en 1, se realizarán 
		        // en el otro.

		        		
		    //**************** Find ORB point fetaures and descriptors ****************************
		        
		        //clear previous points
		        point_set.clear(); 
		        
		        //detect and compute(extract) features
		        orb_detector->detectAndCompute(image, mascara, point_set, descriptor_set);
		        
		        //draw points on the image
		        cv::drawKeypoints( image, point_set, image, 255, cv::DrawMatchesFlags::DEFAULT );     
		    }
        } 
                
    //********************************************************************
		
        //show image
        cv::imshow("Output Window", image);

		//Waits 1 millisecond to check if a key has been pressed. If so, breaks the loop. Otherwise continues.
        if(cv::waitKey(1) >= 0) break;
    }   
}