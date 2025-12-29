#include <stdio.h>

int main(void)
{
    int friends = 5;
    int week;
    const int dunbar = 150;

    for (week = 1; (friends - week) * 2 < dunbar; week++)
    {
        friends = (friends - week) * 2;
    }

    printf("На %d неделе у профессора Робинса было %d друзей\n", week, friends);
    
    return 0;
}