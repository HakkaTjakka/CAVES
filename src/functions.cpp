#include <stdio.h>
#include <windows.h>
#include <sys/stat.h>

int repl_str(char *str, char *orig, char *rep)
{
    static char buffer[2000];
    char *p;
    if(!(p = strstr(str, orig)))  // Is 'orig' even in 'str'?
        return false;
    strncpy(buffer, str, p-str); // Copy characters from 'str' start to 'orig' st$
    buffer[p-str] = '\0';
    sprintf(buffer+(p-str), "%s%s", rep, p+strlen(orig));
    strcpy(str,buffer);
    return true;
}

bool file_exists(const char * filename)
{
    struct stat stat_buffer;
    int exist = stat(filename,&stat_buffer);
    if (exist==0)
    {
        return true;
    }
    return false;
}

int toggle_2=0;
void toggle2() {
    toggle_2=(toggle_2+1); if (toggle_2>=5000) toggle_2=0;;
    if (toggle_2==0) printf("/\b");
    else if (toggle_2==1250) {
        static int t=0;
        t++;
        if (t>100) { printf("o-\b"); t=0; }
        else { printf("-\b"); }
    }
    else if (toggle_2==2500) printf("\\\b");
    else if (toggle_2==3750) printf("|\b");
}

int toggle_3=0;
void toggle3() {
    static int toggle=0;
    if (toggle_3++>=10485760) toggle_3=0;
    if (toggle_3==0) printf("/\b");
    else if (toggle_3==2621440) printf("o-\b");
    else if (toggle_3==5242880) printf("\\\b");
    else if (toggle_3==7864320) printf("|\b");
}
