#include <stdio.h>
#include <string.h>

//global scope so evaluateVariable can have
//access to the arrays and counter for variables

int main()
{
    FILE *file;
    char* varname;
	int varvalue;

    //we use this to read line by line
    char line[128];
        
    //for handling loops
    int bracketCheck = 0;
    int bracketFound = 0;
    int foundProperLoop = 0;
    
	//printf("DEBUG: Trying to find file....\n");
    file=fopen("example/superbash","r");

    if(file != NULL)
    {
		//printf("DEBUG: Found the file!\n");
        //we can open the file
        while(fgets(line, sizeof(line), file) != NULL)
        {
            if(strchr(line,'=') != NULL) 
            {
					//printf("DEBUG: Found a =\n");
				
					char* token;
				
					//variable name
					token = strtok(line, " ");
					//add the name to a array list for possible script evaluation
					varname = token;
				
					//bypass the = sign
					token = strtok(NULL, " ");
				
					//hop over to what the variable is assigned to
					token = strtok(NULL, " ");
					varvalue = atoi(token);
					//printf("\n\nDEBUG: Variable %s is set to %s", varnames[varcounter],varvalues[varcounter]);
									
					//increment the counter AFTER we give the name
					//and value to the respective arrays, that way
					//they stay in sync
					printf("%s=%i\n\n",varname,varvalue);
			}
			
            if(strstr(line,"if") != NULL)
            {
					//handle if statement logic
					char* conditional;
					char buffer[128];
					
					conditional = strtok(line, "$");
					
					conditional = strtok(NULL, line);
					strcat(buffer,conditional);
					strcat(buffer," ");
					conditional = strtok(NULL, line);
					strcat(buffer,conditional);
					strcat(buffer," ");
					conditional = strtok(NULL, line);
					strcat(buffer,conditional);
					
					printf("if[ $%s ]\n",buffer);
					printf("then\n");
					
					//ifline = line;
					while(fgets(line, sizeof(line), file) != NULL && strstr(line, "fi") == NULL)
					{
						printf(line);
					}
					
					printf("fi\n\n");
					
            }

            if(strstr(line, "repeat") != NULL)
            {
				char* whilec;
				char whileb[128];
				
				whilec = strtok(line, " ");
				whilec = strtok(NULL, line);
				
				printf("repeatIndex=0\n\n");
				printf("while [ $repeatIndex -lt %s]\n",whilec);
				printf("do");
				
				fgets(line, sizeof(line), file);
				
				while(fgets(line, sizeof(line), file) != NULL && strstr(line, "}") == NULL)
				{
					if(strstr(line, "{") == NULL)
					{
						printf(line);
					}
				}
				
				printf("\trepeatIndex=$[repeatIndex + 1]\n");
				printf("done\n");				
				
								
                //printf("DEBUG: Found a loop start (repeat)\n");
            }
            //do stuff
        }
        fclose(file);
    }

    else
    {
        printf("Error opening file\n");
    }

    return 0;
}
