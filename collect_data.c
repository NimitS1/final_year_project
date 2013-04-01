#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define NO_OF_VALUES 8

char *commands[NO_OF_VALUES];
char *error_msg[NO_OF_VALUES];

void read_commands(FILE *command_list)
{
     command_list = fopen("commands.txt","r");
     char cmd[100]={'\0'}, desc[100]={'\0'};
     int i=0;
     
     while(1)
     {
	  if(feof(command_list))
	       break;
	  fgets(cmd,500,command_list);
	  fgets(desc,500,command_list);
	  
	  commands[i] = (char *)malloc(sizeof(char)*(strlen(cmd)+1));
	  strcpy(commands[i], cmd);
	  
	  error_msg[i] = (char *)malloc(sizeof(char)*(strlen(desc)+1));
	  strcpy(error_msg[i], desc);
	  
	  i++;
     }
     
     fclose(command_list);
}

void init_input_files(FILE *usage_files[])
{
    int i;    
    
    for(i=0;i<NO_OF_VALUES;i++)
    {
        usage_files[i] = popen(commands[i], "r");
        if(usage_files[i] == NULL)
        {
            perror(error_msg[i]);
            exit(0);
        }
    }
}

void read_from_data_files(FILE *usage_files[], float *values)
{
    int i;
    
    for(i=0;i<NO_OF_VALUES;i++)
    {
        fscanf(usage_files[i],"%f",&values[i]);
        pclose(usage_files[i]);
    }    

    values[1] = 100.00f - values[1];
    values[2] = values[2]/1024;
}

void clear_arrays()
{
     int i;
     
     for(i=0;i<NO_OF_VALUES;i++)
     {
	  free(commands[i]);
	  free(error_msg[i]);
     }
}

int main()
{
    FILE *usage_files[NO_OF_VALUES], *command_list;    
    float values[NO_OF_VALUES];
    int i;
    
    read_commands(command_list);
    init_input_files(usage_files);
    read_from_data_files(usage_files, values);
    clear_arrays();
    
    for(i=0;i<NO_OF_VALUES;i++)
        printf("%.2f\n",values[i]);
    
    return 0;
}
