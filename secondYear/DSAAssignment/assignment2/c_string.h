//Private like function, only for this library.
int is_null(char* s1, char* s2){
    if (s1 == 0 || s2 == 0){
        return 1;
    }
    return 0;
}



int string_length(char* str){
    if(str==NULL){
        return 0;
    }
    int i=0;
    while (str[i] != '\0') i++;
    return i;
}

void string_copy(char* source, char* destination){
    if(is_null(source,destination)) return;

    int i=0;
    do{
        destination[i] = source[i];
    }while(source[i++]!='\0');

}

void string_concat(char* destination, char* source){
    char* str1 = destination,*str2=source;
    if(is_null(str1,str2)) return;

    //appends str2 at the end of str1
    int len,j=0;
    len = string_length(str1);

    do{
        str1[len + j] = str2[j];
    }while(str2[j++]!='\0');

}

int string_cmp(char* str1,char* str2){
    if(is_null(str1,str2)) return 0;

    int i=0,result=0;
    while(str1[i] != '\0' || str2[i]!='\0'){
        result = str1[i] - str2[i];
        if(result) return result;
        else i++;
    }
    return result;
}

void string_lower(char* str){
    if(str==0) return;

    for(int i=0;str[i]!='\0';i++){
        if(str[i]>=65 && str[i]<=90){
            str[i] += 32;
        }
    }
}

void string_upper(char* str){
    if (str == 0) return;

    for (int i = 0;str[i] != '\0';i++){
        if (str[i] >= 97 && str[i] <= 122){
            str[i] -= 32;
        }
    }
}

