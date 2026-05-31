# -*- coding: utf-8 -*-
# Исправленный скрипт для results.txt с пустыми строками
# Запуск: gnuplot plot_all.gp

set encoding utf8
set decimalsign "."
set datafile separator "\t"
set datafile missing "NaN"

# Убираем предупреждения о пустых строках
set style data linespoints

# Общие настройки оформления
set terminal pngcairo size 1200,700 font "Times New Roman,14" enhanced
set style line 1 lc rgb "#E41A1C" lt 1 lw 2 pt 7 ps 1.2
set style line 2 lc rgb "#377EB8" lt 1 lw 2 pt 5 ps 1.2
set style line 3 lc rgb "#4DAF4A" lt 1 lw 2 pt 9 ps 1.2
set border lw 1.5
set grid
set key top left font "Times New Roman,12"

# ============================================================
# График 1: Эксперимент 1 — Поиск в BST и хеш-таблице
# ============================================================
set output "exp1_plot.png"
set xlabel "Количество элементов, шт." font "Times New Roman,14"
set ylabel "Время выполнения, с" font "Times New Roman,14" rotate by 90
set title "Эксперимент 1: Сравнение времени поиска (lookup)" font "Times New Roman,16"
set format x "%.0f"
set format y "%.1e"
set yrange [0:*]

# Пропускаем первые 2 строки (заголовок эксперимента + имена колонок)
# Берём 20 строк данных, игнорируя нечисловые
plot "results.txt" every ::2 using 1:2 title "bstree_lookup" with linespoints ls 1, \
     "results.txt" every ::2 using 1:3 title "hashtab_lookup" with linespoints ls 2

# ============================================================
# График 2: Эксперимент 5 — bstree_max
# ============================================================
set output "exp5_plot.png"
set title "Эксперимент 5: Время поиска максимума (bstree_max)" font "Times New Roman,16"
set format y "%.1e"
set yrange [0:*]

# Данные начинаются после строки "Эксперимент №5" и заголовка колонок
# Используем индекс строки для фильтрации (только числа >= 20000)
plot "results.txt" using ($1 >= 20000 ? $1 : 1/0):2 title "bstree_max (худший случай)" with linespoints ls 1, \
     "results.txt" using ($1 >= 20000 ? $1 : 1/0):3 title "bstree_max (средний случай)" with linespoints ls 2

# ============================================================
# График 3: Эксперимент 6 — Время поиска (KP vs XOR)
# ============================================================
set output "exp6_time_plot.png"
set title "Эксперимент 6: Время поиска (хеш-функции)" font "Times New Roman,16"
set format y "%.1e"
set yrange [0:*]

plot "results.txt" using ($1 >= 20000 ? $1 : 1/0):2 title "KP (время)" with linespoints ls 1, \
     "results.txt" using ($1 >= 20000 ? $1 : 1/0):4 title "XOR (время)" with linespoints ls 2

# ============================================================
# График 4: Эксперимент 6 — Коллизии
# ============================================================
set output "exp6_collisions_plot.png"
set title "Эксперимент 6: Количество коллизий" font "Times New Roman,16"
set ylabel "Количество коллизий" font "Times New Roman,14" rotate by 90
set format y "%.0f"
set yrange [0:*]

plot "results.txt" using ($1 >= 20000 ? $1 : 1/0):3 title "KP (коллизии)" with linespoints ls 1, \
     "results.txt" using ($1 >= 20000 ? $1 : 1/0):5 title "XOR (коллизии)" with linespoints ls 2

print "Готово! Графики сохранены в файлы *.png"
