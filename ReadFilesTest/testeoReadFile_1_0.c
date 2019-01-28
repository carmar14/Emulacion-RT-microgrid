

#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(){
	
	const char *delimiter_characters = "\t";
	const char *filename = "perfiles_meteo_consum/myData7_5min.txt";
	FILE *input_file = fopen(filename, "r");
	char buffer[BUFFER_SIZE];
	char *last_token;
	char *year;
	char *day;
	char *time;
	char *outhum;
	char *windspd;
	char *rain;
	char *solarrad;
	char *tempout;
	char *consumpt;
	
	
	if (input_file == NULL){
		fprintf(stderr, "Unable to open file %s\n",filename);
	}else{
		
			//Read each line into the buffer
		fgets(buffer, BUFFER_SIZE, input_file);	//First line for the labels
		
		while(fgets(buffer, BUFFER_SIZE, input_file) != NULL){
			//fgets(buffer, BUFFER_SIZE, input_file);
			// Gets each token as a string and prints it
			year=strtok(buffer, delimiter_characters);
			printf("year: %s\n",year);
			day = strtok(NULL, delimiter_characters);
			printf("day: %s\n",day);
			time = strtok(NULL, delimiter_characters);
			printf("time: %s\n",time);
			outhum = strtok(NULL, delimiter_characters);
			printf("outhum: %s\n",outhum);
			windspd = strtok(NULL, delimiter_characters);
			printf("windspd: %s\n",windspd);
			rain = strtok(NULL, delimiter_characters);
			printf("rain: %s\n",rain);
			solarrad = strtok(NULL, delimiter_characters);
			printf("solarrad: %s\n",solarrad);
			tempout = strtok(NULL, delimiter_characters);
			printf("tempout: %s\n",tempout);
			consumpt = strtok(NULL, delimiter_characters);
			printf("consumption: %s\n",consumpt);
			while(last_token != NULL){
				printf("%s\n",last_token);
				last_token = strtok(NULL, delimiter_characters);
			}
		}
		if(ferror(input_file)){
			perror("The following error ocurred");
		}
		fclose(input_file);
	}
	return 0;
}
