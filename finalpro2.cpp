#include <iostream>
#include <malloc.h>
#include <cstring>

using namespace std;

// typeinfo is an int
typedef int typeinfo;

//pointer declaration for struct
typedef struct lotter *typelotter;

typedef struct users *typeuser;

typedef struct recap *typerecap;


//status file is load at the first time program running
bool isload = false;

//declaration total data on circle linkedlist
int totalData = 0;

struct lotter {
    typeinfo luckNumber;
    typelotter up, down;
};

struct users{
    typeinfo number;
    char name[30];
    char nim[20];

    typeuser next;
};

struct recap{
    typeinfo numberLotter;
    typeinfo numberAnswer;
    char name[30];
    char nim[20];
    char status[10];

    typerecap next;
};

//declaration for stack top and bottom
typelotter top, bottom;

//declaration for queue front and back
typeuser front, back;

//declaration head an circle linkedlist
typerecap head;


//checking is the stack empty or not
bool isStack(){
    if(top==NULL){
        return false;
    }else{
        return true;
    }
}

//checking is the queue empty or not
bool isQueue(){
    if(front==NULL){
        return false; 
    }else{
        return true;
    }
}

//checking is the circle Linkedlist empty or not
bool isCircle(){
    if(head->next==head){
        return false;
    }else{
        return true;
    }
}

//error handling if the input is not an integer
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

//checking is the input character is not more than max
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
void printCircle();

void regist();
void cancelRegistration();
void playLotter();


void getData();

char loop;
int choice;



int main(){
    typeinfo number;
    int many;
    string user, pass;

    //create all the linkedlist
    nStack();
    nQueue();
    nCircle();

    //load the data in file
    getData();

    while(loop != 'n' && loop !='N'){
        system("cls");
        
        //The program menu
        puts("======  FP LOTTERY  ======");
        puts(" MENU : ");
        puts(" 1. Admin Menu"); //Admin menu must login
        puts(" 2. Registration"); //Registration if the stack not empty
        puts(" 3. Cek Queue"); //checking queue after registration
        puts(" 4. Play Lottery"); //play the lottery according to the queue and it will dequeue
        puts(" 5. Cancel Registration"); //for canceling registration Lottery
        puts(" 6. Exit");
        printf(" Choice : "); cin >> choice;
        if(!invalid()){
            switch (choice)
            {
            case 1:
                puts("=== ADMIN LOGIN ===");cin.ignore();

                printf("Username   : "); getline(cin, user);
                printf("Password   : "); getline(cin, pass);

                if(isAdmin(user, pass)){
                    char loop='y';
                    puts("\n=== Login Success ===\n");

                    system("pause");
                    while(loop!='n' && loop!='N'){
                        system("cls");
                        puts("         MENU         ");
                        puts("1. Add Lottery Stock");
                        puts("2. Print Lottery Stock");
                        puts("3. Recap Data");
                        puts("4. Back To Menu");
                        printf("Choice : "); cin >> choice;
                        if(!invalid()){
                            if(choice==1){
                                printf("\nHow many number do you want input? : "); cin >> many; //input data stack
                                if(!invalid()){
                                    for(int i=0;i<many;i++){
                                        printf("Input number %d : ", i+1); cin >> number; //if not error the input success
                                        if(invalid()){
                                            puts("   -- Input Failed");
                                            break;
                                        }else{
                                            addStack(number);
                                            puts("   -- Input Success\n");
                                        }
                                    }
                                }
                            }else if(choice==2){
                                printStack();
                            }else if(choice==3){
                                puts("\n=== Recap Data ===");
                                printCircle();
                            }else if(choice==4){
                                loop='n';
                            }else{
                                puts("Wrong Input! Please Input [1..3]\n");
                            }
                        }
                        
                        if(choice!=4){
                            printf("\nBack to admin menu? (y/n) : "); cin >> loop;
                            fflush(stdin);
                        }
                        
                    }
                    
                }else{
                    puts("\nUsername / Password is wrong!");
                }
                break;

            case 2:
                regist();
                break;

            case 3:
                printQueue();
                break;

            case 4:
                playLotter();
                break;

            case 5:
                cancelRegistration();
                break;
            
            case 6: //program exit
                system("cls");
                puts("\n\n      Program Exit! \n");
                system("pause");
                exit(0);
                break;

            default: //error handling if the input not an integer
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
        fflush(stdin);//clear input char on keyboard
    }

    return 0;
}

// Admin Login check
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
    add = (users*)malloc(sizeof(users));
    int answer;
    bool isWin;

    FILE *fp;
    fp = fopen("stack.dat", "r"); //read stack.dat
    if(fp != NULL){
        while(fread(&lotterData, sizeof(lotter), 1, fp)){
            addStack(lotterData.luckNumber);
        }
    }
    
    fclose(fp);

    fp = fopen("queue.dat", "r"); //read queue.dat
    if(fp != NULL){
        while(fread(&userData, sizeof(users), 1, fp)){
            addQueue(userData);
        }
    }
    
    fclose(fp);

    fp = fopen("recap.dat", "r"); //read recap.dat
    if(fp != NULL){
        while(fread(&recapData, sizeof(recap), 1, fp)){
            add->number = recapData.numberLotter;
            answer = recapData.numberAnswer;

            strncpy(add->name, recapData.name, 30);
            strncpy(add->nim, recapData.nim, 20);

            if(recapData.status[0]=='W'){
                isWin = true;
            }else{
                isWin = false;
            }

            addCircle(add, answer, isWin);
        }
    }
    fclose(fp);

    free(add);
    isload = true;
}

// Create Cicle Linkedlist
void nCircle(){
    head = (recap*)malloc(sizeof(recap));
    head->numberLotter = totalData;
    head->next = head;
}

// Add node Cicle Linkedlist
void addCircle(typeuser add, int answer, bool isWin){ //it use the users data, the answer, and win/lose
    typerecap NI, helper;
    string s;
    totalData++;

    NI = (recap*)malloc(sizeof(recap));

    //insert data recap
    NI->numberLotter = add->number;
    NI->numberAnswer = answer;

    strncpy(NI->name, add->name, 30);
    strncpy(NI->nim, add->nim, 20);

    if(isWin){
        s = "Win";
    }else{
        s = "Lose";
    }
    strcpy(NI->status, s.c_str());

    NI->next=NULL;

    if(isCircle()){
        helper=head;

        while((strcmp(helper->next->name, NI->name) < 0) && helper->next != head) //to sort the data base on the name user
            helper = helper->next; //the max loop until last data before head

        if(helper->next!=head){ //if the data in middle
            NI->next = helper->next;
            helper->next = NI;
        }else{ //if the data on back
            NI->next = head;
            helper->next = NI;
        }

    }else{ //if the circle empty
        NI->next = head;
        head->next = NI;
        totalData=1;
        head->numberLotter=totalData;
    }

    if(isload){ //function to write file to save recap data after load the data at the first time
        recap input;
        FILE *fp;

        input.numberAnswer = NI->numberAnswer;
        input.numberLotter = NI->numberLotter;

        strncpy(input.name, NI->name, 30);
        strncpy(input.nim, NI->nim, 20);
        strncpy(input.status, NI->status, 10);

        fp = fopen("recap.dat", "a");
        fwrite(&input, sizeof(recap), 1, fp);
        fclose(fp);
    }
}
//print the data on circle linkedlist
void printCircle(){
    typerecap helper;
    int i=1;

    helper = head->next;
    if(isCircle()){
        printf("%-3s %-30s %-20s %-15s %-15s %-s\n","No","Name","NIM","Lottery Number", "Guess Number", "Status");
        while (helper != head){
            printf("%-3d %-30s %-20s %-15d %-15d %-s\n",i++,helper->name,helper->nim,helper->numberLotter, helper->numberAnswer, helper->status);
            helper = helper->next;
        }
        
    }else{ //if empty
        puts("\nNO DATA");
    }
}

// Create New Stack
void nStack(){
    typelotter first;

    first = (lotter*)malloc(sizeof(lotter));
    first = NULL;

    top = first;
    bottom = first;
}

// Add stack
void addStack(typeinfo add){
    typelotter NI;

    lotter input;
    input.luckNumber = add;

    NI = (lotter*)malloc(sizeof(lotter));
    NI->luckNumber = input.luckNumber;
    NI->down=NULL;
    NI->up=NULL;

    if(isStack()){ //if the stack not empty
        NI->down = top;
        top->up = NI;
        top=NI;
    }else{ //if empty
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

//Get top stack data
void deStack(){
    typelotter del, helper;
    lotter input;
    if(isStack()){//if not empty
        del = top;
        top=top->down; //make top into the bottom of the top

        if(top!=NULL){
            top->up=NULL;
            free(del);
        }else{ //if the data only 1
            free(del);
            free(top);
            nStack();
        }

        //file input from bottom
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


//Create Queue
void nQueue(){
    typeuser first;

    first = (users*)malloc(sizeof(users));
    first = NULL;

    front = first;
    back = first;
}


//Add queue
void addQueue(users add){
    typeuser NI;
    
    NI = (users*)malloc(sizeof(users));

    if(isload){ //get top stack data
        NI->number = top->luckNumber;
    }else{//error handling to load file at the first time
        NI->number = add.number;
    }

    //data registration input
    strncpy(NI->name, add.name, 30);
    strncpy(NI->nim, add.nim, 20);

    NI->next = NULL;


    if(isQueue()){//if not empty
        back->next = NI;
        back=NI;
    }else{ //if empty
        front = NI;
        back = NI;
    }

    //file input
    if(isload){
        add.number = top->luckNumber;
        FILE *fp;
        fp = fopen("queue.dat", "a");
        fwrite(&add, sizeof(users), 1, fp);
        fclose(fp);
    }
}

//Delete front queue
void deQueue(){
    typeuser del, helper;
    users input;
    if(isQueue()){ //if not empty
        del = front;
        front=front->next; //the front go into the next front data

        if(front!=NULL){
            free(del);
            
        }else{//if the data only 1
            free(front); free(del);
            nQueue();
        }
        
        //file input
        if(isload){
            FILE *fp;
            fp = fopen("queue.dat", "w");
            helper=front;
            if(fp!=NULL){
                while(helper!=NULL){
                    input.number = helper->number;

                    strncpy(input.name, helper->name, 30);
                    strncpy(input.nim, helper->nim, 20);

                    fwrite(&input, sizeof(users), 1, fp);
                    helper=helper->next;
                }
            }

            fclose(fp);
        }
    }
}


// Print Stack Data
void printStack(){
    if(isStack()){//if not empty
        typelotter helper; //print from the top
        helper=top;
        puts("\n=== Lottery Number Stack ===");
        while(helper!=NULL){
            printf("   %d \n", helper->luckNumber);
            helper=helper->down;
        }
    }else{
        puts("\nNO DATA");
    }
}

//Print queue data
void printQueue(){
    if(isQueue()){//if not empty
        int x=1;
        typeuser helper;//print from the front
        helper = front;
        puts("=== Queue Data ===\n");
        printf("%-3s %-31s %-s\n","No","Name","NIM");
        while(helper!=NULL){
            printf("%-3d %-31s %-s\n",x++, helper->name, helper->nim);
            helper = helper->next;
        }
    }else{
        puts("\nNO DATA");
    }
}


// Registration
void regist(){
    int pay;
    char loop_regis='y';
    users input;
    if(isStack()){ //if stack not empty
        puts("=== REGISTRATION ==="); cin.ignore(); //input data and some error handling
        printf("Name    : "); cin.getline(input.name, 35);

        if(isTrue(input.name, 30)){
            printf("NIM     : "); cin.getline(input.nim, 30);

            if(isTrue(input.nim, 20)){
                while(loop_regis != 'n' && loop_regis != 'N'){
                    system("cls");
                    puts("=== PAYMENT ===");
                    puts("Ticket Price Rp. 100000");
                    printf("Pay        : Rp. "); cin >> pay;

                    if(!invalid()){
                        if(pay >= 100000){ //if the transactation complete
                            printf("Change    : Rp. %d\n", pay-100000);
                            puts("Success, please get in the queue");
                            loop_regis='n';
                            addQueue(input); //add into queue
                            deStack(); // delete top data stack
                        }else{
                            printf("Failed! Pay Again (y/n) ? "); cin >> loop_regis;
                            fflush(stdin);
                        }
                    }
                }        
            }else{
                puts(" --Failed!");
            }
        }else{
            puts(" --Failed!");
        }
        
    }else{ //if the stack is empty
        puts("\n Sorry, our lottery is out of stock");
    }
}

//Cancel the registration
void cancelRegistration(){
    char searchName[30], searchNim[20];
    typeuser helper, del;
    users input;
    bool found = false;
    

    if(isQueue()){
        puts("\n=== Menu Cancel Registration ===");
        printQueue();

        puts("\nPlease input Name and Nim!"); cin.ignore(); //name and nim input
        printf("Name  : "); cin.getline(searchName, 30);
        printf("Nim   : "); cin.getline(searchNim, 20);

        helper = front; // cek the data from front queue

        //search the data if on the front queue
        if(strcmp(searchName, helper->name)==0 && strcmp(searchNim, helper->nim)==0){
            addStack(helper->number);
            found=true;
            del = front;
            front=front->next;

            if(front!=NULL){
                free(del);
            
            }else{ ///if the queue data only 1
                free(front); free(del);
                nQueue();
            }
                
        }

        //search the data if on the middle and back of queue
        while(helper!=back&&!found){
            //it search based on the next helper name
            if(strcmp(searchName, helper->next->name)==0 && strcmp(searchNim, helper->next->nim)==0){
                found=true;
                del=helper->next;
                addStack(del->number);
                if(del!=back){
                    helper->next=del->next;
                    free(del);
                }else{ //if the data at back
                    back=helper;
                    back->next=NULL;
                    free(del);
                }
                        
            }else{
                helper = helper->next;
            }
            
        } 
           
        
        if(found){ //if the data found
            puts("Cancel Registration Success!");
            if(isload){
                FILE *fp;
                fp = fopen("queue.dat", "w");
                helper=front;

                //file update the queue data
                if(fp!=NULL){
                    while(helper!=NULL){
                        input.number = helper->number;

                        strncpy(input.name, helper->name, 30);
                        strncpy(input.nim, helper->nim, 20);

                        fwrite(&input, sizeof(users), 1, fp);
                        helper=helper->next;
                    }
                }

                fclose(fp);
            }
        }else{
            puts("Data Not Found!");
        }
    }else{
        puts("\n No Registration Data");
    }
}

//Play Lotter
void playLotter(){
    int guess;
    bool isWin;
    if(isQueue()){
        system("cls");
        puts("===== Welcome to Lottery Games =====");
        puts("  Rules : ");
        puts("   - Input the number ");
        puts("   - If your guess correct you win ");
        puts("   - If your guess wrong you loss ");
        printf("  Start . . .\n\n"); system("pause");
        puts("-----------------------------------");

        printf("Hello %s\n", front->name);
        printf("Input your luck number : "); cin >> guess; //the user input the number
        if(!invalid()){
            if(guess == front->number){ //if the user input is correct so it will win the game
                puts("Congratulation! You win the game, and get free UKT ");
                isWin=true;
            }else{  //the it wrong it will lose
                puts("Sorry better luck next time!");
                isWin=false;
            }

            addCircle(front, guess, isWin);
            deQueue();
        }
    }else{
        puts("\n  -- No Participant!");
    }
}