#include <stdio.h>

struct Owner
{
    char familia[255];
    char name[255];
    char othestvo[255];
};

struct Car
{
    char znak[10];
    char marka[100];
    struct Owner own;
    int year;
};

// void serv (struct Car bently, struct Car renault, struct Car lada, struct Car opel, struct Car toyota)
// {

//     return 1;
// }
int main()
{
    struct Car car[] = {
        {
            .znak = "А111ВС",
            .marka = "bentley ultratank",
            .own.familia = "Заруцкий",
            .own.name = "Константин",
            .own.othestvo = "",
            .year = 2025,
        },
        {
            .znak = "А456ВС",
            .marka = "renault logan",
            .own.familia = "Иванов",
            .own.name = "Иван",
            .own.othestvo = "Иванович",
            .year = 2005,
        },
        {
            .znak = "А789ВС",
            .marka = "lada priora",
            .own.familia = "Иванов",
            .own.name = "Сергей",
            .own.othestvo = "Петрович",
            .year = 2010,
        },
        {
            .znak = "B123MX",
            .marka = "opel astra",
            .own.familia = "Андреев",
            .own.name = "Андрей",
            .own.othestvo = "Андреевич",
            .year = 2012,
        },
        {
            .znak = "А123ВС",
            .marka = "toyota camry",
            .own.familia = "Иванов",
            .own.name = "Иван",
            .own.othestvo = "Иванович",
            .year = 2015,
        }};
    for (int i = 0; i < 5; i++)
    {
        printf("%s, %s %s %s - %s, %d год\n", car[i].marka, car[i].own.familia, car[i].own.name, car[i].own.othestvo, car[i].znak, car[i].year);
    }
    // printf("%s, %s %s %s - %s, %d год\n", renault.marka, renault.own.familia, renault.own.name, renault.own.othestvo, renault.znak, renault.year);
    // printf("%s, %s %s %s - %s, %d год\n", lada.marka, lada.own.familia, lada.own.name, lada.own.othestvo, lada.znak, lada.year);
    // printf("%s, %s %s %s - %s, %d год\n", opel.marka, opel.own.familia, opel.own.name, opel.own.othestvo, opel.znak, opel.year);
    // printf("%s, %s %s %s - %s, %d год\n", toyota.marka, toyota.own.familia, toyota.own.name, toyota.own.othestvo, toyota.znak, toyota.year);
    return 0;
}
