#include <random.h>
#include <bstree.h>
#include <hashtab.h>
#include <string.h>

// Объявления функций для XOR хеширования (Эксперимент 6)
unsigned int hashtab_hash_XOR(char *key);
void hashtab_add_XOR(struct listnode **hashtab, char *key, uint32_t value, int *col);
struct listnode *hashtab_lookup_XOR(struct listnode **hashtab, char *key);

// Эксперимент 1: Сравнение поиска в BST и хеш-таблице (время в секундах)
void run_experiment_1()
{
    listnode *hashTab[SIZE_HASH_TAB];
    bstree *tree;
    char (*mas)[32] = (char (*)[32])malloc(500000 * 32);
    if (!mas)
        exit(EXIT_FAILURE);

    FILE *fp = fopen("word.txt", "r");
    if (!fp)
    {
        free(mas);
        exit(EXIT_FAILURE);
    }

    hashtab_init(hashTab);
    fscanf(fp, "%31s", mas[0]);
    hashtab_add(hashTab, mas[0], 0);
    tree = bstree_create(mas[0], 0);

    int i = 1, n = 1;
    printf("Эксперимент №1\n");
    printf("Количество элементов\tВремя bstree_lookup, с\tВремя hashtab_lookup, с\n");

    while (1)
    {
        for (; i < 20000 && n < 400000; i++, n++)
        {
            fscanf(fp, "%31s", mas[n]);
            hashtab_add(hashTab, mas[n], n);
            bstree_add(tree, mas[n], n);
        }

        // Замер времени для BST (в секундах)
        double t = wtime();
        for (int k = 0; k < 1000000; k++)
            bstree_lookup(tree, mas[getrand(0, n - 1)]); // сделать рандом
        t = (wtime() - t) / 1000000;

        // Замер времени для HashTable (в секундах)
        double t2 = wtime();
        for (int k = 0; k < 1000000; k++)
            hashtab_lookup(hashTab, mas[getrand(0, n - 1)]);
        t2 = (wtime() - t2) / 1000000;

        printf("%d\t%.10lf\t%.10lf\n", n, t, t2);

        i = 0;
        if (n >= 400000)
            break;
    }

    fclose(fp);
    free(mas);
    clearHash(hashTab);
    clearBstree(tree);
}

// Эксперимент 5: Поиск максимального элемента (худший и средний случай, время в секундах)
void run_experiment_5()
{
    bstree *treeB = NULL, *treeM = NULL;
    char masB[32], masM[32];

    FILE *fpB = fopen("bad.txt", "r");
    FILE *fpM = fopen("word.txt", "r");
    if (!fpB || !fpM)
    {
        if (fpB)
            fclose(fpB);
        if (fpM)
            fclose(fpM);
        exit(EXIT_FAILURE);
    }

    fscanf(fpB, "%31s", masB);
    fscanf(fpM, "%31s", masM);
    treeB = bstree_create(masB, 0);
    treeM = bstree_create(masM, 0);

    int i = 1, n = 1;
    printf("\nЭксперимент №5\n");
    printf("Количество элементов\tВремя bstree_max в худшем случае, с\tВремя bstree_max в среднем случае, с\n");

    while (1)
    {
        for (; i < 20000 && n < 400000; i++, n++)
        {
            fscanf(fpB, "%31s", masB);
            bstree_add(treeB, masB, n);
            fscanf(fpM, "%31s", masM);
            bstree_add(treeM, masM, n);
        }

        // Худший случай: отсортированные данные (вырожденное дерево)
        double tB = wtime();
        for (int k = 0; k < 1000; k++)
            bstree_max(treeB);
        tB = (wtime() - tB) / 1000;

        // Средний случай: случайные данные
        double tM = wtime();
        for (int k = 0; k < 1000; k++)
            bstree_max(treeM);
        tM = (wtime() - tM) / 1000;

        printf("%d\t%.10lf\t%.10lf\n", n, tB, tM);

        i = 0;
        if (n >= 400000)
            break;
    }

    fclose(fpB);
    fclose(fpM);
    clearBstree(treeM);

    // Очистка вырожденного дерева (правосторонняя цепочка)
    while (treeB)
    {
        bstree *tmp = treeB->right;
        free(treeB->key);
        free(treeB);
        treeB = tmp;
    }
}

// Эксперимент 6: Сравнение хеш-функций KP и XOR (время в секундах)
void run_experiment_6()
{
    listnode *hashKP[SIZE_HASH_TAB], *hashXOR[SIZE_HASH_TAB];
    char (*mas)[32] = (char (*)[32])malloc(500000 * 32);
    if (!mas)
        exit(EXIT_FAILURE);

    FILE *fp = fopen("word.txt", "r");
    if (!fp)
    {
        free(mas);
        exit(EXIT_FAILURE);
    }

    hashtab_init(hashKP);
    hashtab_init(hashXOR);

    int collisions_KP = 0, collisions_XOR = 0;
    int i = 1, n = 1;

    fscanf(fp, "%31s", mas[0]);
    hashtab_add_KR(hashKP, mas[0], 0, &collisions_KP);
    hashtab_add_XOR(hashXOR, mas[0], 0, &collisions_XOR);

    printf("\nЭксперимент №6\n");
    printf("Количество элементов\tВремя KP, с\tКоллизии KP\tВремя XOR, с\tКоллизии XOR\n");

    while (1)
    {
        for (; i < 20000 && n < 400000; i++, n++)
        {
            fscanf(fp, "%31s", mas[n]);
            hashtab_add_KR(hashKP, mas[n], n, &collisions_KP);
            hashtab_add_XOR(hashXOR, mas[n], n, &collisions_XOR);
        }

        // Замер для KP
        double tKP = wtime();
        for (int k = 0; k < 1000000; k++)
            hashtab_lookup(hashKP, mas[getrand(0, n - 1)]);
        tKP = (wtime() - tKP) / 1000000;

        // Замер для XOR
        double tXOR = wtime();
        for (int k = 0; k < 1000000; k++)
            hashtab_lookup_XOR(hashXOR, mas[getrand(0, n - 1)]);
        tXOR = (wtime() - tXOR) / 1000000;

        printf("%d\t%.10lf\t%d\t%.10lf\t%d\n", n, tKP, collisions_KP, tXOR, collisions_XOR);

        i = 0;
        if (n >= 400000)
            break;
    }

    fclose(fp);
    free(mas);
    clearHash(hashKP);
    clearHash(hashXOR);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Использование: %s <exp1|exp5|exp6|all>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "exp1") == 0 || strcmp(argv[1], "all") == 0)
        run_experiment_1();

    if (strcmp(argv[1], "exp5") == 0 || strcmp(argv[1], "all") == 0)
        run_experiment_5();

    if (strcmp(argv[1], "exp6") == 0 || strcmp(argv[1], "all") == 0)
        run_experiment_6();

    return 0;
}
