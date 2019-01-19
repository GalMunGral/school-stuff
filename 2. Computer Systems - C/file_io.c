#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

// Your program will only support BMP files that
// have a max size that is equivalent to the size
// of the GBA screen.
#define MAX_BMP_FILE_SIZE (0x36 + 240 * 160 * 4)
char data_arr[MAX_BMP_FILE_SIZE];
unsigned int getWidth(char*);
unsigned int getHeight(char*);

int main(int argc, char *argv[]) {
  if (argc != 2) return 1;

  FILE *infile;
  infile = fopen(argv[1], "r");
  if (infile == NULL) {
    printf("an error occured: %s\n", strerror(errno));
    return 1;
  }
  fread(data_arr, 1, MAX_BMP_FILE_SIZE, infile);
  fclose(infile);

  unsigned int width = getWidth(data_arr);
  unsigned int height = getHeight(data_arr);
  
  FILE *outheader;
  char filename[100];
  strcpy(filename, argv[1]);
  int fname_len = strlen(filename);
  filename[fname_len - 3] = 'h';
  filename[fname_len - 2] = '\0'; // file.bmp -> file.h-
  if(!(outheader = fopen(filename, "w"))) {
    printf("Error creating file %s: %s\n", filename, strerror(errno));
  }
  filename[fname_len - 4] = '\0';
  char *ptr = filename;
  while(*ptr) {
    *ptr = toupper(*ptr); // file.h -> FILE
    ++ptr;
  }

  /* File format:
   *
   *  #define FILE_WIDTH 100
   *  #define FILE_HEIGHT 150
   *  const unsigned short file_data[15000];
   */
  fprintf(outheader, "#define %s_WIDTH %d\n", filename, width);
  fprintf(outheader, "#define %s_HEIGHT %d\n", filename, height);
  strcpy(filename, argv[1]);
  filename[fname_len - 4] = '\0';
  fprintf(outheader, "const unsigned short %s_data[%d];\n", filename, width * height);
  fclose(outheader);

  FILE *outdata;
  strcpy(filename, argv[1]);
  filename[fname_len - 3] = 'c';
  filename[fname_len - 2] = '\0';
  if(!(outdata = fopen(filename, "w"))) {
    printf("Error creating file %s: %s\n", filename, strerror(errno));
  }

  /* File format:
   *
   *  const unsigned short file_data[15000] = {
   *    0x4521, 0x5B2F, 0x1F69, ...
   *  };
   */
  filename[fname_len - 4] = '\0';
  fprintf(outdata, "const unsigned short %s_data[%d] = {\n", filename, width * height);
  int *pixels = (int *) &data_arr[0x36];
  for (int row = 0; row < (int) height ; row++) {
    for (int col = 0; col < (int) width; col++) {
      unsigned char *pixel = (unsigned char *) &pixels[width * ((int)height-1-row) + col];
      unsigned short pxData = pixel[0]/8<<10 | pixel[1]/8<<5 | pixel[2]/8;
      fprintf(outdata, "0x%x,\n", pxData);
    }
  }
  fprintf(outdata, "};");
  fclose(outdata);
  return 0;
}

/*
 *
 * Format of a bmp header (data_arr)
 * file offset  |   length   |     field
 * 0x12         |  4 bytes   |  image width
 * 0x16         |  4 bytes   |  image height
 *
 */
unsigned int getWidth(char *data_arr) {
  return *((int *) &data_arr[0x12]);
}

unsigned int getHeight(char *data_arr) {
  return *((int *) &data_arr[0x16]);
}
