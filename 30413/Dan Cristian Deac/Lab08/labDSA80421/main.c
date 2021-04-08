#include <stdio.h>
#include <stdlib.h>

int main()
{
    /// fraction 8/9 = 1/2 + 1/3 + 1/18
    int sol[100];
    int up, down, newup, newdown;
    int seal;


    printf("insert numerator: ");
    scanf("%d", &up);
    printf("insert denominator: ");
    scanf("%d", &down);

    int i = 0;

    newup = up;
    newdown = down;

    if(up >= down){
        printf("the fraction isn't less then 1");
        return 0;
    }

    printf("%d / %d = ", up, down);

    do
    {
        down = newdown;
        up = newup;
        seal = (int)ceil((float)newdown/newup);
        sol[i] = seal;
        i++;

        //printf("top is %d, bot is %d\n", newup, newdown);
        if (down == seal)
        {
            newup = up - 1;
            newdown = down;
        }
        else
        {
             newup = up * seal - down;
             newdown = down * seal;
        }
        if( newdown % newup == 0)
        {

            newdown = newdown/newup;
            newup = 1;
        }
        else
        {

            for(int d = newup/2; d>=2 ; d--) /// if i understood correctly the fractions are always less then 1 so i can only look in the divisors of the numerator
                if(newup%d == 0 && newdown%d == 0)
                {
                    newup = newup/d;
                    newdown = newdown/d;
                }
        }
        //printf("newtop is %d, newbot is %d\n", newup, newdown);

        //printf(" while %d, %f != %f \n", ceil((float)newdown/newup)!= (float)newdown,ceil((float)newdown/newup),(float)newdown  );

    }while(ceil((float)newdown/newup) != (float)newdown);

    sol[i] = newdown;

    ///printing result
    for(int j=0; j<=i; j++)
    {
        printf("1/%d ", sol[j]);
        if (j < i)
            printf("+ ");
    }

    return 0;
}
