#include"ppm_utils.h"
/*************************
*Ethan Coffey
*CPSC 2310-002, Sp23
*ejcoffe@g.clemson.edu
*************************/

int main(int argc, char *argv[]){

   FILE* inputMed[NINE];
   FILE* inputAvr[TEN];

   image_t* imgAverage[TEN];
   image_t* imgMedian[NINE];


 if(strcmp(argv[1], "average") == 0){

	//Opens all Input files to read
        openInputFiles(argv[1],inputAvr);

	//Makes all files that were open to images
	for(int i = 0; i < TEN; i++){
	 imgAverage[i] = read_ppm(inputAvr[i]);
	
	}

   	FILE* out = NULL;
   	out = fopen(argv[2],"w");

	//Removes noise from all images to create the finale ultimate image
	image_t* temp = removeNoiseAverage(imgAverage);
			
	//Outputs image
	write_p6(out,temp);			
	

   fclose(out);
 } 
 
 //Used For Meadien 
 else{
	
	//Opens all input files for Meadien
       openInputFiles(argv[1],inputMed);

	//Converts all the opned files into images
	for(int i = 0; i < NINE; i++){
	
	 imgMedian[i] = read_ppm(inputMed[i]);
	
	}

   	FILE* out = NULL;
   	out = fopen(argv[2],"w");
	
	//Removes that guy from the picture
	image_t* temp = removeNoiseMedian(imgMedian);
		
	//Outouts image	
	write_p6(out,temp);			
	

   fclose(out);
 }


return 0;
}
