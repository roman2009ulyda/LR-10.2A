#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;
enum Specialnist { KOMP_NAUKY, INFORMATYKA, MAT_EKON, FIZ_INF, TRUD_NAVCH };
string specStr[] = {
    "Комп'ютерні науки",
    "Інформатика",
    "Математика та екон. ",
    "Фізика та інформ.",
    "Трудове навчання"
};
struct Student
{
    string prizv;
    unsigned kurs;
    Specialnist spec;
    int fizyka;
    int matematyka;
    int informatyka;
};
void Create(Student* p, const int N);
void Print(const Student* p, const int N);
void Sort(Student* p, const int N);
int* IndexSort(const Student* p, const int N);
void PrintIndexSorted(const Student* p, const int* I, const int N);
int BinSearch(const Student* p, const int N, const string prizv, const Specialnist spec, const int informatyka);
#ifndef UNIT_TEST
int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    int N;
    cout << "Введіть кількість студентів N: ";
    cin >> N;
    Student* p = new Student[N];
    int menuItem;
    do {
        cout << "\nВиберіть дію:" << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - фізичне впорядкування даних" << endl;
        cout << " [4] - індексне впорядкування та вивід даних" << endl;
        cout << " [5] - бінарний пошук студента" << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl;
        cout << "Введіть значення: ";
        cin >> menuItem;
        cout << endl;

        switch (menuItem)
        {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            Sort(p, N);
            Print(p, N);
            break;
        case 4:
            PrintIndexSorted(p, IndexSort(p, N), N);
            break;
        case 5:
        {
            int ispec;
            int informatyka;
            string prizv;
            cout << "Введіть ключі пошуку:" << endl;
            cout << " спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
            cin >> ispec;
            cout << " оцінка з інформатики: ";
            cin >> informatyka;
            cin.get();
            cin.sync();
            cout << " прізвище: ";
            getline(cin, prizv);

            int found = BinSearch(p, N, prizv, (Specialnist)ispec, informatyka);
            if (found != -1)
                cout << "Знайдено студента в позиції " << found + 1 << endl;
            else
                cout << "Шуканого студента не знайдено" << endl;
            break;
        }
        case 0:
            break;
        default:
            cout << "Ви ввели помилкове значення! Спробуйте ще раз." << endl;
        }
    } while (menuItem != 0);

    delete[] p;
    return 0;
}
#endif
void Create(Student* p, const int N)
{
    int spec;
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;
        cin.get();
        cin.sync();
        cout << " прізвище: ";
        getline(cin, p[i].prizv);
        cout << " курс: ";
        cin >> p[i].kurs;
        cout << " спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, "
            << "2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
        cin >> spec;
        p[i].spec = (Specialnist)spec;
        cout << " оцінка з фізики: ";
        cin >> p[i].fizyka;
        cout << " оцінка з математики: ";
        cin >> p[i].matematyka;
        cout << " оцінка з інформатики: ";
        cin >> p[i].informatyka;
    }
}
void Print(const Student* p, const int N)
{
    cout << "========================================================================================" << endl;
    cout << "| №  |   Прізвище   | Курс |     Спеціальність     | Фізика | Математика | Інформатика |" << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++)
    {
        int prizvWidth = 13 + p[i].prizv.length() / 2;
        int specWidth = 22;
        if (p[i].spec == KOMP_NAUKY)  specWidth = 22 + 15;
        if (p[i].spec == INFORMATYKA) specWidth = 22 + 11;
        if (p[i].spec == MAT_EKON)    specWidth = 22 + 15;
        if (p[i].spec == FIZ_INF)     specWidth = 22 + 14;
        if (p[i].spec == TRUD_NAVCH)  specWidth = 22 + 15;
        cout << "| " << setw(2) << right << i + 1 << " ";
        cout << "| " << setw(prizvWidth) << left << p[i].prizv;
        cout << "| " << setw(4) << right << p[i].kurs << " ";
        cout << "| " << setw(specWidth) << left << specStr[p[i].spec];
        cout << "| " << setw(6) << right << p[i].fizyka << " ";
        cout << "| " << setw(10) << right << p[i].matematyka << " ";
        cout << "| " << setw(11) << right << p[i].informatyka << " |" << endl;
    }
    cout << "========================================================================================" << endl;
    cout << endl;
}
void Sort(Student* p, const int N)
{
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
    {
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
        {
            if ((specStr[p[i1].spec] > specStr[p[i1 + 1].spec]) ||
                (specStr[p[i1].spec] == specStr[p[i1 + 1].spec] && p[i1].informatyka > p[i1 + 1].informatyka) ||
                (specStr[p[i1].spec] == specStr[p[i1 + 1].spec] && p[i1].informatyka == p[i1 + 1].informatyka && p[i1].prizv > p[i1 + 1].prizv))
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
        }
    }
}
int* IndexSort(const Student* p, const int N)
{
    int* I = new int[N];
    for (int i = 0; i < N; i++)
        I[i] = i;
    int i, j, value;
    for (i = 1; i < N; i++)
    {
        value = I[i];
        for (j = i - 1;
            j >= 0 && ((specStr[p[I[j]].spec] > specStr[p[value].spec]) ||
                (specStr[p[I[j]].spec] == specStr[p[value].spec] && p[I[j]].informatyka > p[value].informatyka) ||
                (specStr[p[I[j]].spec] == specStr[p[value].spec] && p[I[j]].informatyka == p[value].informatyka && p[I[j]].prizv > p[value].prizv));
            j--)
        {
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
    }
    return I;
}
void PrintIndexSorted(const Student* p, const int* I, const int N)
{
    cout << "===========================================================================================" << endl;
    cout << "| №  |   Прізвище   | Курс |     Спеціальність     | Фізика | Математика | Інформатика |" << endl;
    cout << "-------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++)
    {
        int prizvWidth = 13 + p[I[i]].prizv.length() / 2;
        int specWidth = 22;
        if (p[I[i]].spec == KOMP_NAUKY)  specWidth = 22 + 16;
        if (p[I[i]].spec == INFORMATYKA) specWidth = 22 + 11;
        if (p[I[i]].spec == MAT_EKON)    specWidth = 22 + 15;
        if (p[I[i]].spec == FIZ_INF)     specWidth = 22 + 14;
        if (p[I[i]].spec == TRUD_NAVCH)  specWidth = 22 + 15;
        cout << "| " << setw(2) << right << i + 1 << " ";
        cout << "| " << setw(prizvWidth) << left << p[I[i]].prizv;
        cout << "| " << setw(4) << right << p[I[i]].kurs << " ";
        cout << "| " << setw(specWidth) << left << specStr[p[I[i]].spec];
        cout << "| " << setw(6) << right << p[I[i]].fizyka << " ";
        cout << "| " << setw(10) << right << p[I[i]].matematyka << " ";
        cout << "| " << setw(11) << right << p[I[i]].informatyka << " |" << endl;
    }
    cout << "===========================================================================================" << endl;
    cout << endl;
}
int BinSearch(const Student* p, const int N, const string prizv, const Specialnist spec, const int informatyka)
{
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        if (p[m].prizv == prizv && p[m].spec == spec && p[m].informatyka == informatyka)
            return m;
        if ((specStr[p[m].spec] < specStr[spec]) ||
            (specStr[p[m].spec] == specStr[spec] && p[m].informatyka < informatyka) ||
            (specStr[p[m].spec] == specStr[spec] && p[m].informatyka == informatyka && p[m].prizv < prizv))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);
    return -1;
}