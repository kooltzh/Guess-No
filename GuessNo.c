#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int main(void)
{
    int counter;
    char state;

    //Welcome message and instruction
    printf("Welcome to Guess Number!\n\n");
    printf("A random four digits (1-9) with no repeat number will be generated!\n");
    printf("Eg. 1234, 5678, 1934, 1294\n");
    printf("Can you guess it in 10 turns?\n\n");
    printf("R indicate Right number in Right location\n");
    printf("L indicate Right number in Wrong location\n");
    printf("W indicate Wrong number\n");
    printf("You must guess it in 10 guesses!\n\n");

    //set state and start
    //state, Y playing, W win, L lose
    do
    {   printf("Are you ready to take the challenge? (y/n)  ");
        fflush(stdin);
        state = toupper(getchar());
    } while(state != 'Y');

    do
    {
        //Generate non-repeating random number
        int temp[4];
        printf("\nLets start!\n");
        srand(time(NULL));

        int i, j, c = 0;
        int arrNum[9];
        int noNum;
        for (i=0; i<9; i++)
        {
            arrNum[i]=i+1;
        }
        for (i=0, noNum=9; i<4; i++, noNum--)
        {
            c=rand()%noNum;
            temp[i]=arrNum[c];
            arrNum[c]=arrNum[noNum-1];
        }
        counter = 0;

        while (state=='Y')
        {
            // Process input
            int input=0;
            int ans[4];
            for(i=0; i<4; i++)
            {
                ans[i]=0;
            }
            do
            {
                printf("Your guess: ");
                scanf("%d", &input);
                fflush(stdin);
            }while(input<1111 || input>9999);

            for (i=3; i>0; i--)
            {
                ans[i] = (input / myPow(10,i));
                if (input>9)
                {
                    input = input % myPow(10,i);
                }
            }
            ans[0] = input;

            //Calculate input RLW
            int couR, couL, couW;
            couR = 0;
            couL = 0;
            couW = 0;
            for (i=0; i<4; i++)
            {
                if (ans[i]==temp[i])
                {
                    couR++;
                }

                for (j=0; j<4; j++)
                {
                    if(ans[i]==temp[j])
                    {
                        couL++;
                    }
                }
            }
            couL = couL - couR;
            couW = 4 - couL - couR;
            if (couW < 0 || couW > 4)
            {
                printf("An error had occured!\n");
            }
            if (couR == 4)
            {
                state = 'W';
            }
            counter++;
            if (counter > 9)
            {
                state = 'L';
            }

            //print gaming interface
            printf("%d%d%d%d  %dR%dL%dW  %d try\n\n", ans[3], ans[2], ans[1], ans[0], couR, couL, couW, counter);
        }

        switch (state)
        {
            case 'W' : printf("\nCongratulation! you got the number in %d tries.\n\n", counter);
            break;
            case 'L' : printf("\nToo bad that you cant guess it in 10 rounds \nThe answer is %d%d%d%d\n\n", temp[3], temp[2], temp[1], temp[0]);
            break;
        }

        //prompt to play again
        do
        {
            printf("Do you want to play again? (y/n)  ");
            fflush(stdin);
            state = toupper(getchar());
        }while(state != 'Y' || state != 'N');

    }while(state =='Y');

    //final prompt to exit
    printf("\nPress any key to exit.");
    fflush(stdin);
    getchar();
}

int myPow(int x, int y)
{
    int i;
    int no = 1;
    for (i=0; i<y; i++)
    {
        no *= x;
    }

    return(no);
}
