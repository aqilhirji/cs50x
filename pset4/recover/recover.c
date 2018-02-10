//CS50X Pset 4 - Recover Images From Memcard Dump 
//May 30, 2017 

#include <stdio.h> 
#include <cs50.h> 
#include <stdlib.h> 
#include <math.h> 
#include <string.h> 
#include <stdint.h>
// define buffer placeholder size 
#define BUFFERSIZE 512

// create an unsigned integer type of 8 bits or 1 byte
typedef uint8_t BYTE;

int main (int argc, char* argv[])
{
    //check for right input arguments 
    if (argc!= 2)
    {
    	fprintf(stderr,"Usage: ./recover infile\n"); 
    	return 1;
    }
    //remember the file name 
    char* infile = argv[1]; 

    // open the memory card 
    FILE* memcard = fopen(infile, "r");
    if (memcard == NULL) 
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    //open output file 
    FILE* outfile = NULL; 

    //name the output files
    int outname = 0; 

    //loop over the entire file 
    while (1)
    {
    	//creates a buffer array of size of buffer as defined at top
    	BYTE buffer_array[BUFFERSIZE] = {}; 

    	//iterate over file searching for each byte. 

	    for (int i = 0; i < BUFFERSIZE; i++)
	    {
	    	// close file if at end 
	    	if (feof(memcard))
		    {
		    	fclose(memcard);
		    	
		    	if (outfile != NULL)
	    	{
	    		fclose(outfile); 
	    	}
	        //return 0; // returns zero when both files are closed successfully 
	    	return 0;
		    }
	    	//read each byte of the memcard
	    	fread(&buffer_array[i], sizeof(BYTE), 1, memcard);
	    }

    	// look at each byte in the file, and iterate through the loop, start new jpg if pattern matches
    	if ((buffer_array[0] == 0xff) && (buffer_array[1] == 0xd8) && ((buffer_array[3] == 0xe0) || buffer_array[3] == 0xe1 || buffer_array[3] == 0xe2 || buffer_array[3] == 0xe3|| buffer_array[3] == 0xe4|| buffer_array[3] == 0xe5 || buffer_array[3] == 0xe6 || buffer_array[3] == 0xe7 || buffer_array[3] == 0xe8 || buffer_array[3] == 0xe9 || buffer_array[3] == 0xea || buffer_array[3] == 0xeb || buffer_array[3] == 0xec || buffer_array[3] == 0xed || buffer_array[3] == 0xee || buffer_array[3] == 0xef))
    	{
    		//close previous output file and pointer 
    		if (outfile != NULL)
    		{
    			fclose(outfile); 
    		}

    		char filename[4]; 

    		//name file in ascending numerical format using outname
    		sprintf(filename, "%03d.jpg", outname); 
    		outname++; 

    		if ((outfile = fopen(filename, "w")) == NULL) // if the output file pointer is null
    		{
    			printf("Could not write image.\n"); 
    			return 1; //returns 1 when file couldn't be written. 
    		}

    		//write the buffer with the photo to the output file. 

    		fwrite(&buffer_array[0], BUFFERSIZE * sizeof(BYTE), 1, outfile); 
    	}

    	else if (outfile != NULL) // if the outfile is already open, write the buffer
    	{
    		fwrite(&buffer_array[0], BUFFERSIZE * sizeof(BYTE), 1, outfile); 
    	}
    }

    	//close files 
    	fclose(memcard); 

    	//return 0 and exit 
    	return 0; 
}