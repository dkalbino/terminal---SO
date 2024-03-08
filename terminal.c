#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <sys/wait.h>

void separate(char *vect);

int main()
{
    //fork();
    printf("BEM VINDO AO TERMINAL:\n");
    char comando[100], ext[100] = "exit\n", **mat;
    int check;
    while(1)
    {
        fgets(comando, 100, stdin);
        check = strcmp(comando, ext);
        int frk = fork();
        //printf("%d\n", frk);
        if(check == 0)
        {
            break;
        }
        else if(frk == 0)
        {
            //printf("entrou\n");
            separate(comando);
            exit(frk);
        }
        //waitpid(fork, NULL, 0);
    }    
    return 0;
}

void separate(char *vect)
{
    //printf("entrou2\n");
    int i = 0, bol = 1, j = 0,check = 0, n = 0, pos = 0, num = 0, posvet = 0;
    //char **mat = (char**) malloc(sizeof(char*) * 100); //criando uma matriz com 100 linhas
    char ***vtmt = (char***) malloc(sizeof(char**) * 10);

    for(int i = 0; i < 10; i++)
    {
        vtmt[i] = (char**) malloc(sizeof(char*) * 100);
    }

        while(1)
        {
            if(vect[i] == '\n')
            {
                vect[i] = '\0';
                num = i;
                break;
            } else if(vect[i] == ';')
            {
                vect[i] ='\0';
            }
            i++;
        }

        //printf("num: %d\n", num);

        while (vect[pos] != '\0' || pos != num)
        {
            if(pos != 0)
            {
                i = pos + 1;
            } else{
                i = pos;
            }
            
        //printf("entrou\n");
        
        for( i = i,j = 0, n = 0; vect[i] != '\0'; i++, j++)
        {
            if(vect[i] == ' ')
            {
                //printf("achou\n");
                vtmt[posvet][n] = (char*) malloc(sizeof(char) * j);
                n++;
                j = 0;
            }

            if(vect[i + 1] == '\0')
            {
                vtmt[posvet][n] = (char*) malloc(sizeof(char) * (j + 1));
                vtmt[posvet][n + 1] = (char*) malloc(sizeof(char));
                vtmt[posvet][n + 1] = '\0'; // vc era o problema se fdp mat[n+1][0] = '\0'
            }
        }

        if(pos != 0)
            {
                i = pos + 1;
            } else{
                i = pos;
            }
    
        for( i = i, j = 0, n = 0; vect[i] != '\0'; i++)
        {
            if(vect[i] == ' ')
            {
                n++;
                j = 0;
                continue;
            }
            vtmt[posvet][n][j] = vect[i];
            //printf("%c -- [%d][%d]\n", mat[n][j], n, j);
            j++;
        }
        pos = i;
        //printf("pos: %d\n num: %d\n", pos, num);
        posvet++;
        }

        //vtmt[0] = mat;
        int pid = fork();

        if(pid == 0)
        {
            for(int i = 0; i<posvet; i = i + 2)
            {
                if(fork() == 0)
                {
                execvp(vtmt[i][0], vtmt[i]);
                }
            }
        } 
        if(pid != 0)
        {
            for(int i = 1; i<posvet; i = i + 2)
            {
                if(fork() == 0)
                {
                execvp(vtmt[i][0], vtmt[i]);
                }
            }
        }

        waitpid(pid, NULL, 0);
}