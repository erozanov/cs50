#include <stdio.h>
#include <cs50.h>
#include <math.h>


int getReminder(int input, int *count) {
       
       int devider;
        if (input >= 25) {
            devider = 25;
        }else if(input>=10) {
            devider = 10;
        }else if (input >=5) {
            devider = 5;
        } else {
            devider = 1;
        }
        int reminder = input % devider;
        *count += reminder == 0 ? input / devider : (input - reminder) / devider;
        return reminder;
    }

int main(void)
{
    int count = 0, roundedInput;
    float input;
    do {
       
        printf("O hai! How much change is owed?\n");
        input = GetFloat();
       
    } while(input < 0);
      roundedInput = round(input * 100);
      
    do {
        roundedInput = getReminder(roundedInput, &count);
    } while(roundedInput != 0);
    printf("%i\n", count);

}

   

