#include <iostream>
#include <malloc.h>
#include <cstring>

using namespace std;

typedef int typeinfo;
typedef struct lotter *typelotter;

typedef struct users *typeuser;

typedef struct recap *typerecap;

bool isload = false;
int totalData = 0;

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

struct recap{
    typeinfo numberLotter;
    typeinfo numberAnswer;
    char name[30];
    char nim[20];
    char status[10];

    typerecap next;
};

typelotter top, bottom;
typeuser front, back;
typerecap head;

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

bool isCircle(){
    if(head->next==head){
        return false;
    }else{
        return true;
    }
}

bool invalid(){
    if(cin.fail()){

        puts("\nWrong Input ");
        cin.clear();
        cin.ignore(1000,'\n');
        puts("\nPlese Input Integer Only!");

        return true;
    }else{
        return false;
    }
}

bool isTrue(char *input, int max){
    int size;
    size = strlen(input);
    if(size>=max){
        printf(" --Max Allowed char is %d \n", max);
        cin.clear();
        fflush(stdin);
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
void deQueue();
void printQueue();

void nCircle();
void addCircle(typeuser add, int answer, bool isWin);

void regist();
void playLotter();


void getData();

char loop;
int choice;



int main(){
    typeinfo number;
    int many;
    string user, pass;

    nStack();
    getData();

    while(loop != 'n' && loop !='N'){
        system("cls");

        puts("MENU");
        puts("1. Add Stack");
        puts("2. Print Stack");
        puts("3. Regis");
        puts("4. Cek Queue");
        puts("5. Play lotter");
        printf("Choice : "); cin >> choice;
        if(!invalid()){
            switch (choice)
            {
            case 1:
                puts("=== ADMIN LOGIN ===");cin.ignore();

                printf("Username   : "); getline(cin, user);
                printf("Password   : "); getline(cin, pass);

                if(isAdmin(user, pass)){
                    puts("\n=== Login Success ===\n");
                    printf("How many number do you want input? : "); cin >> many;
                    if(!invalid()){
                        for(int i=0;i<many;i++){
                            printf("Input number %d : ", i+1); cin >> number;
                            if(invalid()){
                                puts("   -- Input Failed");
                                break;
                            }else{
                                addStack(number);
                                puts("   -- Input Success\n");
                            }
                        }
                    }
                }else{
                    puts("\nUsername / Password is wrong!");
                }
                break;

            case 2:
                printStack();
                break;
            case 3:
                regist();
                break;

            case 4:
                printQueue();
                break;

            case 5:
                playLotter();
                break;
            default:
                if(cin.fail()){
                    puts("\n\nWrong Inpu");
                    cin.clear();
                    cin.ignore(1000,'\n');
                    puts("\nPlese Input Integer Only!");
                }
                break;
            }
        }
        

        printf("\nBack to menu? (y/n) : "); cin >> loop;
    }

    return 0;
}

// Admin Login
bool isAdmin(string user, string pass){
    if(user == "admin" && pass == "admin123"){
        return true;
    }else{
        return false;
    }
}


// Get ALL File Data
void getData(){
    lotter lotterData;
    users userData;
    recap recapData;
    typeuser add;
    int answer;
    bool isWin;

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

    fp = fopen("recap.dat", "r");
    if(fp != NULL){
        while(fread(&recapData, sizeof(recap), 1, fp)){
            add->number = recapData.numberLotter;
            answer = recapData.numberAnswer;

            for(int i=0;i<30;i++){
                add->name[i] = recapData.name[i];
            }

            for(int i=0;i<20;i++){
                add->nim[i] = recapData.nim[i];
            }

            if(recapData.status[0]=='W'){
                isWin = true;
            }else{
                isWin = false;
            }

            addCircle(add, answer, isWin);
        }
    }

    isload = true;
}

// Circle
void nCircle(){
    head = (recap*)malloc(sizeof(recap));
    head->numberLotter = totalData;
    head->next = head;
}

void addCircle(typeuser add, int answer, bool isWin){
    typerecap NI, helper;
    string s;
    totalData++;

    NI = (recap*)malloc(sizeof(recap));

    //insert data recap
    NI->numberLotter = add->number;
    NI->numberAnswer = answer;

    for(int i=0;i<30;i++){
        NI->name[i] = add->name[i];
    }

    for(int i=0;i<20;i++){
        NI->nim[i] = add->nim[i];
    }

    if(isWin){
        s = "Win";
    }else{
        s = "Lose";
    }
    strcpy(NI->status, s.c_str());

    NI->next=NULL;

    if(isCircle()){
        helper=head;

        while(strcmp(helper->next->name, NI->name) < 0 && helper->next != head)
            helper = helper->next;

        if(helper->next!=head){
            NI->next = helper->next;
            helper->next = NI;
        }else{
            NI->next = head;
            helper->next = NI;
        }

    }else{
        NI->next = head;
        head->next = NI;
        totalData=1;
        head->numberLotter=totalData;
    }

    if(isload){
        recap input;
        FILE *fp;

        input.numberAnswer = NI->numberAnswer;
        input.numberLotter = NI->numberLotter;
        for(int i=0;i<30;i++){
            input.name[i] = NI->name[i];
        }

        for(int i=0;i<20;i++){
            input.nim[i] = NI->nim[i];
        }

        for(int i=0;i<10;i++){
            input.status[i] = NI->status[i];
        }

        fp = fopen("recap.dat", "a");
        fwrite(&input, sizeof(recap), 1, fp);
        fclose(fp);
    }
}


// Stack
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


// Queue
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

void deQueue(){
    typeuser del, helper;
    users input;
    if(isQueue()){
        del = front;
        front=front->prev;

        free(del);

        if(isload){
            FILE *fp;
            fp = fopen("queue.dat", "w");
            helper=front;
            if(fp!=NULL){
                while(helper!=NULL){
                    input.number = helper->number;
                    for(int i=0;i<30;i++){
                        input.name[i] = helper->name[i];
                    }

                    for(int i=0;i<20;i++){
                        input.nim[i] = helper->nim[i];
                    }

                    fwrite(&input, sizeof(users), 1, fp);
                    helper=helper->prev;
                }
            }

            fclose(fp);
        }
    }
}


// Print Data
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


// Registration
void regist(){
    users input;
    if(isStack()){
        puts("=== REGISTRATION ==="); cin.ignore();
        printf("Name    : "); cin.getline(input.name, 35);

        if(isTrue(input.name, 30)){
            printf("NIM     : "); cin.getline(input.nim, 30);

            if(isTrue(input.nim, 20)){
                puts("Success, please get in the queue");
                addQueue(input);
                deStack();
            }else{
                puts(" --Failed!");
            }
        }else{
            puts(" --Failed!");
        }
        
    }else{
        puts("\n Sorry, our lottre is out of stock");
    }
}

//Play Lotter
void playLotter(){
    puts("Play Succes!");
    deQueue();
}