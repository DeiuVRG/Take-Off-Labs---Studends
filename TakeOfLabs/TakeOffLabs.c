#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define LMaxNume 30
#define LMaxFacultate 10

typedef struct nod_note
{
    float nota;
    struct nod_note *urm;
}nod_note;


typedef struct Student
{
    int id;
    char nume[LMaxNume+1];
    char facultate[LMaxFacultate+1];
    int nr_note;
    nod_note *nota;

}student;

/*
void clasament_facultati(student studenti[], int n)
{
    float suma_note[LMaxFacultate] = {0}; //vectorul in care se vor stoca sumele notelor pentru fiecare facultate
    int nr_note[LMaxFacultate] = {0}; //vectorul in care se vor stoca numerele de note pentru fiecare facultate
    float medii[LMaxFacultate]; //vectorul in care se vor stoca mediile pentru fiecare facultate
    int i;

    //calculam suma notelor si numarul total de note pentru fiecare facultate
    for (i = 0; i < n; i++)
    {
        int index_facultate = atoi(studenti[i].facultate) - 1; //indexul facultatii (0 - LMaxFacultate-1)
        nod_note *actual = studenti[i].nota;
        while (actual != NULL)
        {
            suma_note[index_facultate] += actual->nota;
            nr_note[index_facultate]++;
            actual = actual->urm;
        }
    }

    //calculam media pentru fiecare facultate si o stocam in vectorul medii
    for (i = 0; i < LMaxFacultate; i++)
    {
        if (nr_note[i] != 0)
            medii[i] = suma_note[i] / nr_note[i];
        else
            medii[i] = 0;
    }

    //sortam mediile in ordine descrescatoare
    int index[LMaxFacultate];
    for (i = 0; i < LMaxFacultate; i++)
        index[i] = i;
    for (i = 0; i < LMaxFacultate - 1; i++)
    {
        int j;
        for (j = i + 1; j < LMaxFacultate; j++)
        {
            if (medii[index[j]] > medii[index[i]])
            {
                int temp = index[i];
                index[i] = index[j];
                index[j] = temp;
            }
        }
    }

    //afisam clasamentul universitatilor in functie de medie
    printf("Clasamentul universitatilor in functie de medie:\n");
    for (i = 0; i < LMaxFacultate; i++)
    {
        if (nr_note[index[i]] != 0)
            printf("%d. %s: %.1f\n", i + 1, studenti[index[i]].facultate, medii[index[i]]);
    }
}
*/


int main()
{
    int n, m, i, j, id;
    float nota;
    student studenti[LMaxNume];
    FILE *intrare , *iesire;

    //Deschidem fisierele de intrare si se creaza si cel de iesire daca nu exista.
    intrare = fopen("intrare.txt","r");
    iesire = fopen("iesire.txt", "w");

    if(intrare==NULL || iesire==NULL)//se verifica daca s-au deschis fisierele
    {
        printf("Eroare! Nu s-a putut deschide fisierul!\n");
        exit(0);
    }

    //Citire date studenti din fisier
    fscanf(intrare, "%d", &n);//citire numarul de studenti
    for(i=0; i<n; i++)
    {
        fscanf(intrare, "%d %s %s", &studenti[i].id, studenti[i].nume, studenti[i].facultate);
        //initializam nr de note si notele cu 0
        studenti[i].nr_note=0;
        studenti[i].nota=NULL;
        //printf("%d %s %s \n", studenti[i].id, studenti[i].nume, studenti[i].facultate); //verificare
    }

    //Citire note din fisier
    fscanf(intrare, "%d", &m);//citirea numarului de note
    for(i=0; i<m; i++)
    {
        fscanf(intrare, "%f %d", &nota, &id);
        //cautam studentul cu ID-ul specificat pentru a-i atribui nota
        for(j=0; j<n; j++) //se cauta intre studenti, iar nr studentilor e reprezentat de n
        {
            if(studenti[j].id==id)
            {
            //se adauga nota la lista specificului student cu id-ul mentionat la lista lui de note
            nod_note *p = (nod_note*)malloc(sizeof(nod_note));
            p->nota=nota;
            p->urm =studenti[j].nota;
            studenti[j].nota=p;
            studenti[j].nr_note++;

                break;        
            }
        }
    }

    //Calcularea GPA (mediei) fiecarui student + afisare
    for (i = 0; i < n; i++)
    {
        float suma = 0.0;
        nod_note *actual = studenti[i].nota;
        while (actual != NULL)
        {
            suma = suma + actual->nota;
            actual = actual->urm;
        }
        float GPA = suma/studenti[i].nr_note;
        fprintf(iesire, "%d %s %s %.1f\n", studenti[i].id, studenti[i].nume, studenti[i].facultate, GPA);
        actual=studenti[i].nota;
        while (actual != NULL) 
        {
            nod_note *temp = actual;
            actual = actual->urm;
            free(temp);
        }
    }
    //clasament_facultati(studenti, n);

    fclose(intrare);
    fclose(iesire);

    system("pause");
    return 0;
}