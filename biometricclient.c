#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>


int main()
{
        FILE *biometricinput, *maskdb;
        biometricinput = fopen("Biometric_Input", "r");
        if(biometricinput == NULL)
                printf("Biometric_Input file not found\n");
        else
        {
                printf("Biometric_Input file is opened for reading\n");      

        }

        fclose(biometricinput);
        printf("Biometric_Input file is closed successfully\n");     

}
