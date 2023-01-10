#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANO_BUFF 1000

void print_help(char *command){
	printf("Shell basica de Linux recreada con fork() y execvp().\n");
	printf("uso:\n %s \n", command);
	printf(" %s -h\n", command);
	printf("Opciones:\n");
	printf(" -h\t\t\tAyuda, muestra mensaje de como usar el programa\n");
	printf("Al ejecutar el programa aparecera el prompt '>>' \n");
	printf("Con esta shell basica se puede ejecutar cualquier programa o comando (sin incluir builtins como: cd,del,rd,dir)\n");
	printf("Ejemplo:  >>ls -lh /usr\n");
	printf("Para terminar la shell, se utiliza el built-in command: QUIT (o quit)\n");
	printf(">>QUIT or >>quit\n");
}

int main(int argc1, char *argv1[]){
    int argc;
    char cadena[TAMANO_BUFF];
    char* argv[100];
    char pfull[25];
    char* p = "/bin/";

    int opt;
    int index;


    while ((opt = getopt (argc1, argv1, "h")) != -1){
        switch(opt){
            case 'h':
				print_help(argv1[0]);
				return 0;
			case '?':
			default:
				fprintf(stderr, "uso: %s\n", argv1[0]);
				fprintf(stderr, "     %s -h\n", argv1[0]);
				return 1;
        }
    }


    while(1){

        memset(argv,0,100);
        memset(cadena,0,TAMANO_BUFF);

        printf(">>");

        if(!fgets(cadena, TAMANO_BUFF, stdin)){	
   		    break;		 
   		}

        size_t length = strlen(cadena);

        if(cadena[length-1] == '\n'){
    	    cadena[length-1] = '\0';
		}

        if (strcmp(cadena, "QUIT") == 0 || strcmp(cadena, "quit") == 0){				
		printf("BYE!\n");
		break;
		}


        char *token;
        int i = 0;
		token = strtok(cadena," ");

		while(token != NULL){
		    argv[i] = token;
			token = strtok(NULL," ");
			i++;
		}


        argc = i;
        argv[i] = NULL;


        strcpy(pfull, p);
        strcat(pfull, argv[0]);

        for(i=0; i>strlen(pfull); i++){
            if(pfull[i] == "\n"){
                pfull[i] = "\0";

            }
        }

        int pid = fork();

        if(pid == 0){
            execvp(pfull,argv);
			fprintf(stderr,"Este comando no se puede ejecutar por execvp\n");
			exit(0);
        }else{
            wait(NULL);
        }
    }

}