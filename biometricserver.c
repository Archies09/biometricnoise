#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>


int main()
{
	FILE *biometricdb, *maskdb;
	int totalusers, copies, margin, uid, maskbits;
	char userchar[1];
	biometricdb = fopen("Biometric_Database", "r");
	if(biometricdb == NULL)
		printf("Biometric_Database file not found\n");
	else
	{
		printf("Biometric_Database file is opened for reading\n");	

		fscanf(biometricdb,"%d %d %d", &totalusers, &copies, &margin);
		printf("%d %d %d\n", totalusers, copies, margin);
		char *biometricdatabase[totalusers][copies];
		for(int i=0;i<totalusers;i++)
		{
			fscanf(biometricdb,"%s %d", userchar, &uid);
			//printf("%s, %d\n", userchar, uid);
			for(int j=0;j<copies;j++)
			{
				char databasebiometric[2050];
				biometricdatabase[i][j] = malloc(sizeof (char) * 2048);
				fscanf(biometricdb,"%s",biometricdatabase[i][j]);
				//printf("%s\n",biometricdatabase[i][j]);
			}
		}

		//printf("\n%c\n",biometricdatabase[0][0][11]);
		int numerator, denominator, maskcriteria;
		printf("Enter the mask criteria numerator : ");
		scanf("%d",&numerator);
		printf("Enter the mask criteria denominator : ");
		scanf("%d",&denominator);
		maskcriteria = (copies*numerator)/denominator;
		char finalcopy[totalusers][2050];
		char mask[totalusers][2050];
		for(int i=0;i<totalusers;i++)
		{
			char copytemp[2050];
			char masktemp[2050];
			for(int j=0;j<2048;j++)
			{
				int count0=0,count1=0;
				for(int k=0;k<copies;k++)
        	                {
//					printf("\n%c\n",biometricdatabase[i][k][j]);	
                                	if(biometricdatabase[i][k][j] == '1')
						count1++;
					else	count0++;
	                        }
				if(count1>=count0)
				{
					copytemp[j]='1';
					if(count1>=maskcriteria)
						masktemp[j]='1';
					else	masktemp[j]='0';
				}
				else{
					copytemp[j]='0';
					if(count0>=maskcriteria)
                                                masktemp[j]='1';
                                        else    masktemp[j]='0';
				}
			}
			copytemp[2048]='\0';
			masktemp[2048]='\0';
			strcpy(finalcopy[i],copytemp);
			strcpy(mask[i],masktemp);
			printf("Merged copy of user %d : \n%s\n",i+1,finalcopy[i]);
			printf("Mask of user %d : \n%s\n",i+1,mask[i]);
		}
		
	}

//NO SEPARATE MASK FILE
/*	maskdb = fopen("Mask_Database", "r");
        if(maskdb == NULL)
                printf("Mask_Database file not found\n");
        else
        {
                printf("Mask_Database file is opened for reading\n");      

                fscanf(maskdb,"%d", &maskbits);
                printf("%d\n", maskbits);
                char mask[2050];
                fscanf(maskdb,"%s",mask);
                printf("%s\n",mask);
                
        }
*/
	fclose(biometricdb);
//	fclose(maskdb);
	printf("Biometric_Database file is closed successfully\n");	
//	printf("Mask_Database file is closed successfully\n");

}
