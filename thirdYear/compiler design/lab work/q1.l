%option noyywrap
%{
unsigned long count = 0,ic=0,linec=1,wc=0;
#define isVowel(c) ( ( (c)=='a') || ((c)=='e') || ((c)=='i') || ((c)=='o') || ((c)=='u') || ((c)=='A') || ((c)=='E') || ((c)=='I') || ((c)=='O') || ((c)=='U') )
int checkOrder(char*);
%}

%%
[^ \t\n\r\f]+ {
    ic=0;wc++;

    if(checkOrder(yytext)){
        printf("Exact order word: %s, pos:%lu %lu\n",yytext,linec,wc);
    }

    for(int i=0;yytext[i]!='\0';i++){
        if(isVowel(yytext[i])) ic++;
        if(ic==2){
            printf("two vowel:%s, position:%lu,%lu\n",yytext,linec,wc);
            break;
        }
    }

    if(isVowel(*yytext)){ printf("word starting with vowel: %s, pos: %lu,%lu",yytext,linec,wc);count++;ic++;}
    printf("\n");
}

[\n] {linec++;wc=0;}
%%

int checkOrder(char* txt){
    int c=5;
    for(int i=0;txt[i]!='\0';i++){
        switch(c){
            case 5:{
                if(txt[i] == 'a' || txt[i]=='A') c--;
            } break;
            case 4:{
                if(txt[i] == 'e' || txt[i]=='E') c--;
            } break;
            case 3:{
                if(txt[i] == 'i' || txt[i]=='I') c--;
            } break;
            case 2:{
                if(txt[i] == 'o' || txt[i]=='O') c--;
            } break;
            case 1:{
                if(txt[i] == 'U' || txt[i]=='u') c--;
            } break;
        }

        if(!c) return 1;
    }
    return 0;
}

#include<stdio.h>
int main(int argc,char* argv[]){
    argv++; argc--; /* Exclude program name */
    if(argc>0){
        yyin = fopen(argv[0],"r");

    }else{

    }

    yylex();
    printf("total number of matched words: %lu\n",count);
}

