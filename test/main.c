#include"stdio.h"

void f()
{
    char ch;
    ch=getchar();
    if(ch!='\n')
        {
        f();
        printf("%c",ch);
        }
}

int main(void){
    f();
    printf("\n");
    return 0;
}
