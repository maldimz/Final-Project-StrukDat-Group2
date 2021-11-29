#include <iostream>
#include <malloc.h>

using namespace std;

typedef int typeinfo;
typedef struct lotter *typelotter;

typedef struct users *typeuser;


bool isload = false;

struct lotter {
    typeinfo luckNumber;
    typelotter up, down;
};

struct users{
    typeinfo number;
    char name[30];
    char nim[20];

    typeuser next, prev;
};

typelotter top, bottom;
typeuser front, back;

bool isStack(){
    if(top==NULL){
        return false;
    }else{
        return true;
    }
}

bool isQueue(){
    if(front==NULL){
        return false; 
    }else{
        return true;
    }
}

bool isAdmin(string user, string pass);

void nStack();
void addStack(typeinfo add);
void deStack();
void printStack();

void nQueue();
void addQueue(users add);
void regist();
void printQueue();

void getData();

char choice;



int main(){
    typeinfo number;
    int many;
    string user, pass;

    nStack();
    getData();

    while(choice != 'n' && choice !='N'){
        system("cls");

        puts("MENU");
        puts("1. Add Stack");
        puts("2. Print Stack");
        puts("3. Regis");
        puts("4. Cek Queue");
        printf("Choice : "); cin >> choice;

        switch (choice)
        {
        case '1':
            puts("=== ADMIN LOGIN ===");
            cin.ignore();
            printf("Username   : "); getline(cin, user);
            printf("Password   : "); getline(cin, pass);
            if(isAdmin(user, pass)){
                puts("\n=== Login Success ===\n");
                printf("How many number do you want input? : "); cin >> many;

                for(int i=0;i<many;i++){
                    printf("Input number %d : ", i+1); cin >> number;
                    addStack(number);
                }

                puts("\nInput Success");
            }else{
                puts("\nUsername / Password is wrong!");
            }
            break;

        case '2':
            printStack();
            break;
        case '3':
            regist();
            break;

        case '4':
            printQueue();
            break;
        default:
        
            break;
        }

        printf("\nBack to menu? (y/n) : "); cin >> choice;
    }

    return 0;
}

bool isAdmin(string user, string pass){
    if(user == "admin" && pass == "admin123"){
        return true;
    }else{
        return false;
    }
}

void getData(){
    lotter lotterData;
    users userData;

    FILE *fp;
    fp = fopen("stack.dat", "r");
    if(fp != NULL){
        while(fread(&lotterData, sizeof(lotter), 1, fp)){
            addStack(lotterData.luckNumber);
        }
    }
    
    fclose(fp);

    fp = fopen("queue.dat", "r");
    if(fp != NULL){
        while(fread(&userData, sizeof(users), 1, fp)){
            addQueue(userData);
        }
    }
    
    fclose(fp);

    isload = true;
}

void nStack(){
    typelotter first;

    first = (lotter*)malloc(sizeof(lotter));
    first = NULL;

    top = first;
    bottom = first;
}

void addStack(typeinfo add){
    typelotter NI;

    lotter input;
    input.luckNumber = add;

    NI = (lotter*)malloc(sizeof(lotter));
    NI->luckNumber = input.luckNumber;
    NI->down=NULL;
    NI->up=NULL;

    if(isStack()){
        NI->down = top;
        top->up = NI;
        top=NI;
    }else{
        top = NI;
        bottom = NI; 
    }

    // file input
    if(isload){
        FILE *fp;
        fp = fopen("stack.dat", "a");
        fwrite(&input, sizeof(lotter), 1, fp);
        fclose(fp);
    }
}

void deStack(){
    typelotter del, helper;
    lotter input;
    if(isStack()){
        del = top;
        top=top->down;

        if(top!=NULL){
            top->up=NULL;
            free(del);
        }else{
            free(top);
            free(bottom);
            nStack();
        }

        if(isload){
            FILE *fp;
            fp = fopen("stack.dat", "w");
            helper=bottom;
            if(fp!=NULL){
                while(helper!=NULL){
                    input.luckNumber = helper->luckNumber;
                    fwrite(&input, sizeof(lotter), 1, fp);
                    helper=helper->up;
                }
                
            }

            fclose(fp);
        }
    }
}

void nQueue(){
    typeuser first;

    first = (users*)malloc(sizeof(users));
    first = NULL;

    front = first;
    back = first;
}

void addQueue(users add){
    typeuser NI;
    
    NI = (users*)malloc(sizeof(users));

    if(isload){
        NI->number = top->luckNumber;
    }else{
        NI->number = add.number;
    }

    for(int i=0;i<30;i++){
        NI->name[i] = add.name[i];
    }

    for(int i=0;i<20;i++){
        NI->nim[i] = add.nim[i];
    }

    NI->next = NULL;
    NI->prev = NULL;

    if(isQueue()){
        NI->next = back;
        back->prev = NI;
        back = NI;
    }else{
        front = NI;
        back = NI;
    }

    if(isload){
        add.number = top->luckNumber;
        FILE *fp;
        fp = fopen("queue.dat", "a");
        fwrite(&add, sizeof(users), 1, fp);
        fclose(fp);
    }
}

void regist(){
    users input;
    if(isStack()){
        puts("=== REGISTRATION ==="); cin.ignore();
        printf("Name    : "); cin.getline(input.name, 30);
        printf("NIM     : "); cin.getline(input.nim, 20);
        puts("Success, please get in the queue");
        addQueue(input);
        deStack();
    }else{
        puts("\n Sorry, our lottre is out of stock");
    }
}

void printStack(){
    if(isStack()){
        typelotter helper;
        helper=top;
        puts("\n=== Lottre Number Stack ===");
        while(helper!=NULL){
            printf("   %d \n", helper->luckNumber);
            helper=helper->down;
        }
    }else{
        puts("\nNO DATA");
    }
}

void printQueue(){
    if(isQueue()){
        int x=1;
        typeuser helper;
        helper = front;
        puts("=== Queue Data ===\n");
        printf("%-3s %-31s %-s\n","No","Name","NIM");
        while(helper!=NULL){
            printf("%-3d %-31s %-s\n",x++, helper->name, helper->nim);
            helper = helper->prev;
        }
    }else{
        puts("\nNO DATA");
    }
}
