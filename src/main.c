#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//global scope so evaluateVariable can have
//access to the arrays and counter for variables

int main()
{
	//file pointer
    FILE *file;
    
    //variable to parse script variables into
    char* varname;
	int varvalue;

    //we use this to read line by line
    char line[128];
    
    //attempt to open the file
    file=fopen("example/superbash","r");

    if(file != NULL)
    {
        //we can open the file
        while(fgets(line, sizeof(line), file) != NULL)
        {
			//start the long list of conditionals
			
			//this handles the num=5 and other possible variable assignments
            if(strchr(line,'=') != NULL) 
            {
					//token for when I tokenize the string
					char* token;
				
					//variable name
					token = strtok(line, " ");
					//save the name so I can spit it out later
					varname = token;
				
					//bypass the = sign
					token = strtok(NULL, " ");
				
					//hop over to what the variable is assigned to
					token = strtok(NULL, " ");
					//cast it to an integer (probably not safe, but I don't think it matters on this assignment)
					varvalue = atoi(token);
					
					//print in valid bash syntax
					printf("%s=%i\n\n",varname,varvalue);
			}
			
			//handle if statement logic
            if(strstr(line,"if") != NULL)
            {
					//more character arrays
					char* conditional;
					char buffer[128];
					
					//separate the line by the $
					conditional = strtok(line, "$");
					
					//skip over one increment and stash it in buffer
					conditional = strtok(NULL, line);
					strcat(buffer,conditional);
					
					//append a space to make it valid syntax
					strcat(buffer," ");
					
					//more parsing and grabbing
					conditional = strtok(NULL, line);
					strcat(buffer,conditional);
					strcat(buffer," ");
					
					conditional = strtok(NULL, line);
					strcat(buffer,conditional);
					
					//print it out in valid format as well
					//as a correpsonding "then" on the following line
					printf("if[ $%s ]\n",buffer);
					printf("then\n");
					
					//print out everything after "then" and before "fi"
					while(fgets(line, sizeof(line), file) != NULL && strstr(line, "fi") == NULL)
					{
						printf(line);
					}
					
					
					//add the "fi"
					printf("fi\n\n");
					
            }
			
			//handle the while/loop part
            if(strstr(line, "repeat") != NULL)
            {
				//storage
				char* whilec;
				
				//split it up by a space
				whilec = strtok(line, " ");
				whilec = strtok(NULL, line);
				
				//add something to increment
				printf("repeatIndex=0\n\n");
				
				//print the valid while loop format
				printf("while [ $repeatIndex -lt %s]\n",whilec);
				printf("do");
				
				fgets(line, sizeof(line), file);
				
				//print everything between the  { and }
				while(fgets(line, sizeof(line), file) != NULL && strstr(line, "}") == NULL)
				{
					if(strstr(line, "{") == NULL)
					{
						printf(line);
					}
				}
				
				//increment so the loop doesn't run indefinitely and close the loop
				printf("\trepeatIndex=$[repeatIndex + 1]\n");
				printf("done\n");				
				
            }
        }
        //close our stream
        fclose(file);
    }

	//we can't open the file
    else
    {
        printf("Error opening file\n");
    }
    return 0;
}
