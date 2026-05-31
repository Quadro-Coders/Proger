#include <stdio.h>

#define STAVKA_1 8.75
#define STAVKA_2 9.33
#define STAVKA_3 10.00
#define STAVKA_4 11.20

#define OVERTIME 40
#define OVERWORK 1.5

#define NALOG_1 300.0f
#define KOF_1 0.15

#define NALOG_2 150.0f
#define KOF_2 0.2

#define KOF_3 0.25

int main(void)
{
	int h = 0;
	int s;
	float stavka = 0.0;
	float total = 0.0;
	float kof = 0.0;
	float zp = 0.0;

	printf("Выберите ставку:\n");
	printf("1) $8.75/час     2) $9.33/час\n");
	printf("3) $10.00/час    4) $11.20/час\n");
	printf("5) выход\n");

	scanf("%d", &s);

	while (s > 5 || s < 1)
	{
		while (getchar() != '\n')
			continue;
		printf("Выберите ставку:\n");
		printf("1) $8.75/час     2) $9.33/час\n");
		printf("3) $10.00/час    4) $11.20/час\n");
		printf("5) выход\n");
		scanf("%d", &s);
	}

	switch (s)
	{
		case 1:
			stavka = STAVKA_1;
			break;
		case 2:
			stavka = STAVKA_2;
			break;
		case 3:
			stavka = STAVKA_3;
			break;
		case 4:
			stavka = STAVKA_4;
			break;
		case 5:
			goto end;
	}

	printf("Введите количество часов, отработанных за неделю (q для выхода): ");

	while (scanf("%d", &h) == 1)
	{
		if (h <= OVERTIME)
			total = (float)h * stavka;
		else
			total = (float)OVERTIME * stavka + (float)(h - OVERTIME) * stavka * OVERWORK;

		if (total <= NALOG_1)
			kof = total * KOF_1;

		if (total > NALOG_1 && total < NALOG_1 + NALOG_2)
		{
			kof = NALOG_1 * KOF_1;
			kof += ((total - NALOG_1) * KOF_2);
		}
		if (total >= NALOG_1 + NALOG_2)
		{
			kof = NALOG_1 * KOF_1;
			kof += (NALOG_2 * KOF_2);
			kof += ((total - (NALOG_1 + NALOG_2)) * KOF_3);
		}
		zp = total - kof;

		printf("Всего: %.0f (-%.0f$ налоги). Заработано: %.0f\n",
			   total, kof, zp);
		printf("Введите количество часов, отработанных за неделю (q для выхода): ");
	}

end:
	printf("До свидания!");

	return 0;
}