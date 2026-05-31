#include <stdio.h>

int main() {
    float speed_mbps, size_mb, time_seconds;
    printf("Введите скорость загрузки (Мбит/с): ");
    scanf("%f", &speed_mbps);
    printf("Введите размер файла (МБ): ");
    scanf("%f", &size_mb);
    time_seconds = (size_mb * 8) / speed_mbps;
    printf("При скорости загрузки %.2f мегабит в секунду ", speed_mbps);
    printf("файл размером %.2f мегабайт ", size_mb);
    printf("загружается за %.2f секунд(ы)\n", time_seconds);
    return 0;
}