#include <iostream>
#include <string.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int MAX = 9;


int main(int argc, char* argv[]) {
    if (argc!=3)
    {
        cout<<"E0"<<endl;
        return 0;
    }
     char c[2];
    int size;//for random number
   
    int num;
    int secret_num[9];
    int random_num[9];//number thar user entered
    
    strcpy(c, argv[1]);
    int len_argv=strlen(argv[2]);// Number length control next to -r


    //E0 control
    if (strcmp(c, "-r") == 0) {
        size = atoi(argv[2]);//convert to integer number from string 
        if (size > 9 || size<1 || len_argv>1) {
            cout<<"E0"<<endl;
            return 0;
        }
        
        
         srand(time(0));

    for (int i = 0; i < size; ++i) {
        secret_num[i] = rand() % 10;
        for (int j = 0; j < i; ++j) // generating unique random number
        {
            if (secret_num[j] == secret_num[i] && secret_num[0] != 0)
            {
                i--;
                break;
            }
        }
    }
        
        
    }




    else if (strcmp(c, "-u") == 0) {
         size=strlen(argv[2]);//find the length of string

        num = atoi(argv[2]);
        int temp2=num;  //keep num value in another variable
       for (int i = size-1; i >= 0; --i) {//assigned each digit to an array
        secret_num[i] = num % 10;
        num = (num - secret_num[i])/10;
        }
       
       
        
        //control E0
        for (int i = 0; i < size; ++i) {
        
            for (int j = i+1; j < size; ++j) 
            {
                if (secret_num[i] == secret_num[j] || secret_num[0] == 0 || temp2<0 || size==10)
                {
                    cout<<"E0"<<endl;
                    return 0;
                }
            }
        }
        

          

        }
        else{
            cout<<"E0"<<endl;
            return 0;
        }
        


        int count=0;
        int user_num;
        char char_num[8];
        int flag1=0,flag2=0,len,clen;

       while(flag1<size && count<100){
         flag1=0,flag2=0;
         len=0;
         
         
        
        cin>>char_num;//entered number as a string;
        clen=strlen(char_num);
        //E0 conrtol
            if (char_num[0]=='-' || char_num[0]=='0')
            {
                cout<<"E0"<<endl;
                return 0;
            }
            //E2 control
        for (int i = 0; i <clen ; ++i)
        {
            if (char_num[i]<48 || char_num[i]>57 ) //Check if there is a character value less than '1' or greater than '9'
            {
                cout<<"E2"<<endl;
                return 0;
            }
        }
        user_num=atoi(char_num);//convert to user_num from char_num

        int temp=user_num;
        while (temp != 0) {//find the number of digits of the entered number
            temp = temp / 10;
            len++;
         }
        for (int i = len-1; i >= 0; --i) {//assigned each digit to an array
        random_num[i] = user_num % 10;
        user_num = (user_num - random_num[i])/10;
        }
        //

       
        //E1 control
        if (size!=len)
        {
           cout<<"E1"<<endl;
           return 0;
        }

        //E0 control

        for (int i = 0; i < len; ++i) {
        
            for (int j = i+1; j < len; ++j) 
            {
                if (random_num[i] == random_num[j] || random_num[0] == 0 || user_num<0 || random_num[i]<0 || random_num[i]>9)
                {
                    cout<<"E0"<<endl;
                    return 0;
                }
            }
        }
      

        //start game
        
        for (int j = 0; j < size; ++j)
        {
            if (random_num[j]==secret_num[j])//If the same digit has the same digit value, the flag1 is increased
            {
                flag1++;
            }
        }
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                
            if (random_num[j]==secret_num[i] && i!=j)//flag2 increases  if there is the same digit value that is not in the same digit
            {
                flag2++;
            }
            }
        }
        cout<<flag1<<" "<<flag2<<endl;
        count++;
    }

    if (flag1==size)
    {
        cout<<"FOUND "<<count<<endl;
    }

        

    
    return 0;
}

