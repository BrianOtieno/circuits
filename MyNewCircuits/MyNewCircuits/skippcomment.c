#include <string.h>

typedef enum bool // false = 0 and true = 1
{ false,true}bool;
int main(int argc, char *argv[])
{
     // Openning the file
     FILE* file=fopen("file","r");
     //flag comment to false
     bool comment=false;
     char str[1001]; // string that will contain portion of the file each time

     if (file!=NULL)
     {
         while (fgets(str,sizeof(str),file)!=NULL)
         {
             int i=0;
             for (i=0;i<strlen(str);i++)
             {
                 if (str[i]=='/' && str[i+1] == '*')
                 {
                     comment=true; // comment true we will ignore till the end of comment
                     i++; // skip the * character
                 }
                 else if (str[i]=='*' && str[i+1] == '/')
                 {
                     comment=false;
                     i++; // skip the / character
                 }
                 else if (comment==false)
                 {
                     printf("%c",str[i]); // if the character not inside comment print it
                 }
             }
         }
         fclose(file);
     }

     return 0;
}
