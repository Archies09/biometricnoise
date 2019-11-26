#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>

#define FEATURES 20
#define MARGIN 307 //15% of 2048

void setSeedFromCpuUtil()
{
    FILE *statptr;
    unsigned long long statArray[4];
    statptr=fopen("/proc/stat","r");
    char noUse[10];
    fscanf(statptr,"%s %llu %llu %llu %llu",noUse,&statArray[0],&statArray[1],&statArray[2],&statArray[3]);
    unsigned long long finalrandomnumber = (statArray[0]+statArray[1]+statArray[2]+statArray[3])/3;
    srand(finalrandomnumber%13121);
    fclose(statptr);
    //printf("%d\n",(int)(finalrandomnumber%13121));
    //Now rand can be used
}

/*
void vectorduplication()
{
	for(int k=1;k<FEATURES;k++)
        {
        	char dupvector[2050] = "";
                for(int j=0;j<2048;j++)
                {
                	int randomnum = rand();
                        randomnum = randomnum % 2;
                        char binarydigit = randomnum + '0';
                        strncat(dupvector, &binarydigit, 1);
                }
                fprintf(biometricdb, "%s\n", dupvector);
       	}
	return 0;
}
*/
int main()
{
//	setSeedFromCpuUtil();
	srand(time(NULL));
	FILE *biometricdb;
	int totalusers;
	printf("Enter Number of users : ");
	scanf("%d",&totalusers);

	biometricdb = fopen("Biometric_Database", "w");
	if(biometricdb == NULL)
		printf("Cannot write Biometric_Database\n");
	else
	{
		printf("Biometric_Database opened for writing\n");
		fprintf(biometricdb, "%d %d %d\n", totalusers, FEATURES, MARGIN);
		for(int i=0;i<totalusers;i++)
		{
			fprintf(biometricdb, "U %d\n",i+1);
//			createSyntheticData(biometricdb);
			char vector[2050] = "";
                        for(int j=0;j<2048;j++)
                        {
				int randomnum = rand();
                               	randomnum = randomnum % 2;
                                char binarydigit = randomnum + '0';
                                strncat(vector, &binarydigit, 1);
                        }
                        fprintf(biometricdb, "%s\n", vector);

			for(int k=1;k<FEATURES;k++)
        		{
				int marginindex[MARGIN];
                        	for(int m=0;m<MARGIN;m++)
                        	{
                                	marginindex[m] = rand()%2048;
                        	}

                		char dupvector[2050] = "";
				strncat(dupvector, vector, 2048);
		                for(int j=0;j<MARGIN;j++)
		                {
					if(dupvector[marginindex[j]]=='0')
						dupvector[marginindex[j]]='1';
					else	dupvector[marginindex[j]]='0';
		                }
		        	fprintf(biometricdb, "%s\n", dupvector);
			}	
		}
	}

	fcloseall();
	printf("Biometric_Database closed successfully.\n");

return 0;
}
