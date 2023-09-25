#include "ppm_utils.h"
/*************************
*Ethan Coffey
*CPSC 2310-002, Sp23
*ejcoffe@g.clemson.edu
*************************/

   //Function that will open the array of files passed in
   void openInputFiles(char* argv, FILE* inPut[]){
	if(strcmp(argv, "average") == 0){

		for(int i = 1; i < 11; i++){
		 char fileName[25];

		 //Reads the ppm file names
		 sprintf(fileName,"%s_%03d.ppm",argv,i);

		 //Save open ppm images
		 inPut[i-1] = fopen(fileName,"r");		

		 //Assures ppm file is opened correctly
		 assert(inPut[i-1]); 

	     }

	 } 
	 
         //Used For Meadien 
	 else{
		for(int i = 1; i < TEN; i++){
		 char fileName[25];
		
		 //Reads the ppm file names
		 sprintf(fileName,"%s_%03d.ppm",argv,i);
		 
		 //Save open ppm images
		 inPut[i-1] = fopen(fileName,"r");
		
		 //Assures ppm file is opened correctly
		 assert(inPut[i-1]);

	     }
	 }	
		
}

  //Remove excess pixels or "noise" from image
   image_t* removeNoiseAverage(image_t* img[]){
     
	//Temporarily saves the pixel values Red, Blue and Green from all image files 
	int rTotal = 0;
	int bTotal = 0;
	int gTotal = 0;
	
        //Allocate Memory for the finale output.ppm image	
	image_t* temp = allocateMemory(&img[0]->header);

	  for(int j = 0; j < img[0]->header.HEIGHT; ++j){
			
	       for(int b = 0; b < img[0]->header.WIDTH; ++b){
			
			for(int i = 0; i < TEN; i++){
			  rTotal += img[i]->pixels[j][b].R;
			  gTotal += img[i]->pixels[j][b].G;
			  bTotal += img[i]->pixels[j][b].B;
			}

		  //Statments below is setting the Red,Green and Blue Value of a single pixel (after averaging all img. file pixels) 
		    temp->pixels[j][b].R = rTotal/TEN;		
		    temp->pixels[j][b].G = gTotal/TEN;		
		    temp->pixels[j][b].B = bTotal/TEN;
				
		    rTotal = 0;
		    gTotal = 0;
		    bTotal = 0;		
		  }
	}

	
	
    return temp;

   }

   //remove the noise be taking the meadian of R, G, and B pixels of all images.
   image_t* removeNoiseMedian(image_t* image[]){
	
    image_t* temp = allocateMemory(&image[0]->header);
	
	unsigned int rValues[NINE];
	unsigned int bValues[NINE];
	unsigned int gValues[NINE];

	  for(int j = 0; j < image[0]->header.HEIGHT; ++j){
			
	       for(int b = 0; b < image[0]->header.WIDTH; ++b){
			
			//Saves each RGB pixel value from every image that was passed in
			for(int i = 0; i < 9; i++){
			   rValues[i] = image[i]->pixels[j][b].R;
			   gValues[i] = image[i]->pixels[j][b].G;
			   bValues[i] = image[i]->pixels[j][b].B;
			}
			
		sort(rValues, NINE);
		sort(gValues, NINE);
		sort(bValues, NINE);

		//Sets the meadian of the pixels that was sorted
		temp->pixels[j][b].R = rValues[4];
		temp->pixels[j][b].G = gValues[4];
		temp->pixels[j][b].B = bValues[4];			
		
		}

	}
	
     return temp;

   }
    //Reads all the pixels from the image passed in
    pixel_t readPixels(FILE* in, image_t* img){
	unsigned char r;
	unsigned char b;
	unsigned char g;

	//printf(" %d \n",img->header.HEIGHT);
	for(int i = 0; i < img->header.HEIGHT;i++){
		
		for(int j = 0; j < img->header.WIDTH; j++){
			fscanf(in, "%c%c%c" , &r,&g,&b);
			
			img->pixels[i][j].R = r;
			img->pixels[i][j].G = g;
			img->pixels[i][j].B = b;

		}
		
	}

	return **img->pixels;

    }

   //Reads the header file of image_file.
   header_t read_header(FILE* image_file){
	
     header_t temp;

	fscanf(image_file,"%2s\n",temp.MAGIC_NUMBER);
	//printf(" %s ", temp.MAGIC_NUMBER);

	fscanf(image_file,"%d\n",&temp.WIDTH);
	//printf(" %d ", temp.WIDTH);

	fscanf(image_file,"%d\n",&temp.HEIGHT);
	//printf(" %d ", temp.HEIGHT);
	
	fscanf(image_file,"%d\n",&temp.MAX_VAL);
	//printf(" %d ", temp.MAX_VAL);
	
        return temp;

   }

    // Calls the reading functions.
   image_t* read_ppm(FILE* image_file){
	
	header_t mem = read_header(image_file);

	image_t* reading = allocateMemory(&mem);
	
	readPixels(image_file,reading);
	

     return reading;

   }
  //Writes Header to the output file.
   void write_header(FILE* out_file, header_t header){
     
        fprintf(out_file,"%s\n%d\n%d\n%d\n",header.MAGIC_NUMBER,header.WIDTH,header.HEIGHT,header.MAX_VAL);	

   }

   //Writes Outfile
   void write_p6(FILE* out_file, image_t* image){

     write_header(out_file,image->header);

	 
	for(int i = 0; i < image->header.HEIGHT; i++){
		
		for(int j = 0; j < image->header.WIDTH; ++j){
		
                  fprintf(out_file,"%c%c%c",image->pixels[i][j].R,image->pixels[i][j].G,image->pixels[i][j].B);
		
		}
	}

   }

   //Sorts the pixel into an ordered array using bubble sort
   void sort(unsigned int* arr, int n){

     int i,j;
 
    for(i = 0; i < n-1; i++){
	for(j = 0; j < n-i-1; j++){
	   if(arr[j] > arr[j+1]){
		swap(&arr[j], &arr[j+1]);
	   }
	}

     }
	
   }
   
   //Swap pixel position with one another.
   void swap(unsigned int* a,unsigned int* b){
	
    unsigned int temp = *a;

    *a = *b;

    *b = temp;     

   }

   //Allocates memory to pixel_t to supply to the image
   image_t* allocateMemory(header_t* pics){

     image_t* temp = (image_t*)malloc(sizeof(image_t));
     temp->pixels = (pixel_t**)malloc(sizeof(pixel_t*)*pics->HEIGHT);

	temp->header = *pics;

        for(int i = 0; i < (pics->HEIGHT); i++){
		temp->pixels[i] =(pixel_t*)malloc(sizeof(pixel_t)*pics->WIDTH);
	}
	
     return temp;

   }

