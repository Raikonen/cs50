// Recover JPEG Images from memory

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <stdint.h>

// Definition
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Initialise an array called buffer which contains 512 byte
    BYTE buffer[512];
    
    // Check for proper usage
    if (argc !=2)
        {
         fprintf (stderr,"Usage: ./recover file\n");
         return 1;
        }
        
    // Name inputs
    char *file_name=argv[1];
    
    // Open card file
    FILE *raw_file = fopen(file_name, "r");
    
    // Check if able to open file
    if (raw_file == NULL)
    {
        fprintf(stderr, "Could not open file\n");
        return 2;
    }
    
    // Boolean check if writing JPEG File
    int is_writing = 0;
    
    // Count for the JPEG Filename
    int count = 0; 
    FILE *img;
    
    // Read the first 512 bytes into the buffer array 
    fread(buffer, 1, 512, raw_file);
    
    // Repeat until end of card using do..while loop until fread for 1x 512bytes returns NULL
    do
    {
        // Check if its the beginning of a JPEG using the first 4 bytes
        if (buffer[0]==0xff && buffer[1]==0xd8 && buffer[2]==0xff && (buffer[3] & 0xf0)==0xe0)
        {
            // Open an output JPEG File if one is not already open
            if (is_writing == 0)
            {
                // Create character array named filename of size 7
                char filename[6];
                
                // Create a filename for the JPEG
                sprintf(filename, "%03i.jpg", count);
                img = fopen (filename,"w");
                
                // Check for error in opening file
                if (img == NULL)
                {
                fprintf(stderr, "Could not create %s.\n", filename);
                return 3;
                }
            
            // Write the 512 bytes in buffer into the output file
            fwrite(buffer, 1, 512, img);
            is_writing = 1;
            }
            
            // If file is already open but new JPEG found, close current image and open new one with the next count
            else if (is_writing == 1)
            {
                fclose(img);
                count++;
                fprintf (stdout, "%i", count);
                is_writing = 0;
                fseek (raw_file, -512, SEEK_CUR);
            }
        }
        
        // Check if is the start of the next image
        else
        {
            if (is_writing == 1)
            {
            // Write the 512 bytes in buffer into the output file
            fwrite(buffer, 1, 512, img);
            }
        }
    }
    while (fread(buffer, 512, 1, raw_file));
    
    // close infile
    fclose(raw_file);
    
    // success
    return 0;
}