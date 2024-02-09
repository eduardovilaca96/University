#include <stdio.h>
#include <string.h>

//1
void maiorSeq(){
    int maior = 0;
    while(1){

        int num;
        scanf("%d",&num);
        if(num == 0) break;
        if(num > maior) maior = num;

    }
    printf("%d ",maior);
}

//2
void mediaSeq(){
    int count = 0;
    double soma = 0;

    while(1){
        int num;
        scanf("%d",&num);
        if(num == 0) break;
        soma +=num;
        count++;
    }
    double media = soma / count;
    printf("%.5f\n",media);

}

//3
void segundoMaiorSeq(){
    int maior = 0;
    int segundoMaior = 0;

    while(1){

        int num;
        scanf("%d",&num);
        if(num == 0) break;
        if(num > maior){
            segundoMaior = maior;
            maior = num;
        }else if (num > segundoMaior) segundoMaior = num;
    }
    printf("%d ",segundoMaior);
}

//4
int bitsUm(unsigned int num){

    int resto,count = 0;

    if(num != 0){
        while(num >= 1){
            resto = num % 2;
            if(resto == 1){
                count++;
            }
            num = num / 2;
        }
    }
    return count;
}

//5
int trailingZ(unsigned int num){

    int resto,count = 0;

    if(num != 0){
        while(num >= 1){
            resto = num % 2;
            if(resto == 0){
                count++;
            }
            num = num / 2;
        }
    }


    return count;
}

//6
int qDig (unsigned int n){

    int resto,count = 1;
    while (n / 10 >= 1)
    {
        n /= 10;
        count++;
    }
    return count;

}

//7
char* strcat2(char s1[], char s2[]){

    int i =0,j = strlen(s1);
    while(s2[i] != '\0'){
        s1[j] = s2[i];
        i++;j++;
    }

    return s1;
}

//8
char *strcpy2 (char *dest, char source[]){
    int i =0, j = strlen(source);
    while(source[i] != '\0'){
        *dest = source[i];
        dest++;
    }
    return dest;
}

//9
int strcmp2 (char s1[], char s2[]){

    int i =0;
    while(*s1 == *s2 && *s1){
        s1++;
        s2++;
    }
    return *s1 - *s2;

}

//10
char *strstr2 (char s1[], char s2[]){

    while(*s1){
    if(*s1 == *s2){
        char *r = s1;
        char *p = s2;
        while(*s1 == *p && *s1){
            p++;
            s1++;
        }
        if(*p == '\0') return r;
    }
    s1++;
}

}

//11
void strrev2 (char s[]){
    int i, j = strlen(s)-1;
    char s2[j+1];

    for (i =0; i < strlen(s)  ; i++)
    {
        s2[i] = s[j];
        j--;

    }

   for (int i = 0; i < strlen(s); i++)
   {
        s[i] = s2[i];
   }

}

//12
void tail(char* s) {
    while(*s){
        *s = *(s+1);
        s++;
    }
}

void strnoV (char s[]){
    while(*s) {
        if( *s == 'a' || *s == 'e' || *s == 'i' || *s == 'o' || *s == 'u') tail(s);
        else s++;
    }
}

//13
void truncW (char t[], int n){
    int count = 0;
    while (*t)
    {
        if(*t == ' ') {t++; count= 0;}
        else{
            count++;
            if(count >= n) tail(t);
            else t++;

        }
    }
}

//14
char charMaisfreq (char s[]){
    int count,maior;
    char maisFreq = '0';

    for(int i=0; s[i]; i++){
    count = 0;
        for(int j=0; s[j]; j++){
            if (s[i] == s[j])
                count++;
            }
    if(count > maior){
        maior = count;
        maisFreq = s[i];
    }
    }
    return maisFreq;
}

//15
int iguaisConsecutivos(char s[]){
    int count = 1;
    int maior = 0;
    int i = 0;
    while (s[i])
    {
        while(s[i] == s[i+1]){
            count++;
            i++;
        }
        if(count > maior) maior = count;
        count = 1;
        i++;
    }
    return maior;

}

//16
int difConsecutivos(char s[]){
    int count = 1;
    int maior = 0;
    int i = 0;
    while (s[i])
    {
        while(s[i] != s[i+1]){
            count++;
            i++;
        }
        if(count > maior) maior = count;
        count = 1;
        i++;
    }
    return maior;

}

//17
int maiorPrefixo (char s1 [], char s2 []){

    int count = 0;
    for (int i = 0; *s1 ; i++)
    {
        if(*s1 == *s2 && *s1){
            count++;
        }
        s1++;s2++;
    }
    return count;
    
}

//18
int maiorSufixo (char s1 [], char s2 []){

    int i = strlen(s1) -1;
    int j = strlen(s2) -1;
    int count = 0;
    
    while(i>=0){
        if(s1[i] == s2[j]){
            count++;
            i--;
            j--;
        } else 
            return count;
    }
    return count;
}

//20
int contaPal(char s[]){
    int inWord = 0, total = 0,i = 0;

    while(s[i]) {
        if(s[i] == ' ') {
            if(inWord) total++;
            inWord = 0;
        }
        else inWord = 1;
        i++;
    }
    if(inWord) total++;
    return total;
}


int main(){

    // maiorSeq();
    // mediaSeq();
    // segundoMaiorSeq();
    // printf("%d\n",bitsUm(1024));
    // printf("%d\n",trailingZ(4));
    // printf("%d\n",qDig(10));
    // printf("%s",strcat2(str1,str2));
    // printf("%s",strcat2(str2,str1));
    // printf("%s",strstr2(str1,str2));
    // printf("%s",strrev2(str1));
    // printf("%s",truncW(str1,2));
    // printf("%c",charMaisfreq(str1));
    // printf("%d",iguaisConsecutivos(str1));
    // printf("%d",difConsecutivos(str1));
    char str1[] = "ola Mundo";
    char str2[] = "ola mundo";
    // printf("%d",contaPal(str1));
    printf("%d",maiorPrefixo(str1,str2));
    printf("%d",maiorSufixo(str1,str2));
    return 0;

}

