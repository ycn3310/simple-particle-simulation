#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char path[1028];
char new_name[1028];
FILE *picture;
FILE *new_picture;
int width, height;
int max_value;
char ideftifier[5];
unsigned int color;
unsigned int pixel[3];
unsigned int new_pixel;


unsigned int to_grayscale(unsigned int p[]){
    return 0.229*p[0] + 0.587*p[1] + 0.114*p[2];
}


int main(void){
    printf("enter the picture path(PPM format): ");
    scanf("%s",path);
    picture = fopen(path, "r");
    if(picture== NULL){
        printf("picture not found");
        return 1;
    }

    printf("enter new name: ");
    scanf("%s", new_name);

    if(strlen(new_name)==0){
        strcpy(new_name, "default.ppm");
    }

    new_picture = fopen(new_name, "w");

    if(new_picture == NULL){
        printf("cannot create file\n");
        return 1;
    }

    fscanf(picture, "%2s", ideftifier);
    fscanf(picture, "%d %d", &width, &height);
    fscanf(picture, "%d", &max_value);

    fprintf(new_picture, "%s\n", ideftifier);
    fprintf(new_picture, "%d ", width);
    fprintf(new_picture, "%d\n", height);
    fprintf(new_picture, "%d\n", max_value);

    printf("%s %i %i %i",ideftifier, width, height, max_value);
    //C:\Untitled.ppm
   
    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){
            fscanf(picture, "%d %d %d", &pixel[0], &pixel[1], &pixel[2]);
            
            new_pixel = to_grayscale(pixel);
            fprintf(new_picture, "%d %d %d ", new_pixel, new_pixel, new_pixel);
        }
        fprintf(new_picture, "%s", "\n");
    }
    fclose(picture);
    fclose(new_picture);
    
    return 0;
}