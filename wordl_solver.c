#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<math.h>
extern char dictionary[12969][6];
extern char target[3241][6];
//---------------------------HEADERS------------------------
char* translate(char*,char*);
void copy(char*,char*);
int tocode(char*);
int main(){
printf("Loading...\n");
//----------------------DATA--------------------------------------------
int targetLength=3241,dictionaryLength=12969;int length = targetLength;
//------------------------BOOK MEMORY PLACE-------------------------------------------
int** code=malloc(dictionaryLength*sizeof(int*));
for(int i =0;i<dictionaryLength;i++){
    code[i]=malloc(targetLength*sizeof(int));
}
double** freq=malloc(dictionaryLength*sizeof(double*));
for(int i =0;i<dictionaryLength;i++){
    freq[i]=malloc(243*sizeof(double));
}
double* expectation=malloc(dictionaryLength*sizeof(double));
//---------------------PREPARE ARRAY------------------------------
for(int i = 0 ; i <dictionaryLength;i++){
    for(int j = 0 ;j<targetLength;j++){
      char* temp=translate(dictionary[i],target[j]);
      code[i][j]= tocode(temp);
      free(temp);
    }
}
//-----------------RECALCULATED---------------------------
while(true){
for(int i = 0 ; i <dictionaryLength;i++){
    for(int j = 0 ;j<243;j++){
        freq[i][j]=0.0;
    }
}
for(int i = 0 ; i <dictionaryLength;i++){
    for(int j = 0 ;j<targetLength;j++){
        if(code[i][j]!=-1)freq[i][code[i][j]]++;
    }
}

for(int i = 0 ; i <dictionaryLength;i++){
    for(int j = 0 ;j<243;j++){
        freq[i][j]=(double)freq[i][j]/(double)length;
    }
}
for(int i = 0 ; i <dictionaryLength;i++){
    double sum = 0.0;
    for(int j = 0 ;j<243;j++){
        if(freq[i][j]!=0)sum+=-freq[i][j]*log2(freq[i][j]);
    }
    expectation[i]=sum;
}
double max=expectation[0];int index = 0;
for(int i = 0 ; i <dictionaryLength;i++){
    if(expectation[i]>max){
        max=expectation[i];
        index=i;
    }
}
//-----------------------------CALCULATIONS-------------------------------------------
printf("Prior entropy H(W) = %f\n",log2(length));
printf("Expected posterior entropy H(W|Y) = %f\n",log2(length) - expectation[index]);
printf("Information gain I(W;Y) = %f\n", expectation[index]);
printf("Remaining candidates length :%d\n",length);
printf("Best-guess feedback entropy H(Y) = %s\n",dictionary[index]);
//---------------------------FILTRING------------------------------------
char result[6];
scanf("%s", result);
int resultCode = tocode(result);
for(int i=0;i<targetLength;i++){
  if(code[index][i]!=-1){
    if(code[index][i]!=resultCode){
            for(int j = 0 ; j<dictionaryLength;j++){
                code[j][i]=-1;
            }
        }
    }
}
    length = 0;
    for(int i =0;i<targetLength;i++){
  if(code[index][i]!=-1){
    length++;
  }  
}
  if(length ==1){ 
        for(int i =0;i<targetLength;i++){
      if(code[index][i]!=-1){
        printf("the final answer is :%s\n",target[i]);
        fflush(stdout);
        return 0;
      }  
    }
  }result[5] = '\0';
}


    return 0;
}
//------------------FUNCTIONS----------------------
void copy(char* place,char* answer){
    for(int i = 0 ;i<5;i++){
        place[i]=answer[i];
    }
}
char* translate(char* word,char* answer){
    char temp[6];
    char* result=malloc(sizeof(char) * 6);
    for(int i = 0 ; i <5;i++){
      result[i]='r';
    }
    result[5]='\0';
    for(int i = 0 ; i<5;i++){
        temp[i]=answer[i];
    }
    for (int i = 0 ;i<5;i++){
        if(word[i]==temp[i]){
            temp[i]='\0';
            result[i]='g';
        }
    }
    for (int i = 0 ;i<5;i++){
        if(result[i]!='g'){
            for(int j = 0;j<5;j++){
                if(word[i]==temp[j]){
                    result[i]='y';
                    temp[j] = '\0';
                    break;
                }
            }
        }
    }
    return result;
}
int tocode(char* result){
    int sum = 0;
    for(int i =0;i<5;i++){
        int num = 0;
        switch (result[i])
        {
        case 'g': num =2; break;
        case 'y': num = 1; break;
        default: num = 0; break;
        }
        sum += num*pow(3,i);
    }
    return sum ;
}