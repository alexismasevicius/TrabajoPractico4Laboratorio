/*
    utest example : Unit test examples.
    Copyright (C) <2018>  <Mauricio Davila>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../testing/inc/main_test.h"
#include "../inc/LinkedList.h"

typedef struct
{
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;
}Employee;

Employee* employee_new();
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldoStr);

int mostrarEmpleado(Employee* aux);
int employee_list(LinkedList* pArrayListEmployee, int len);
int employee_listDos(LinkedList* pArrayListEmployee, int len);

int employee_setId(Employee* this,int id);
int employee_getId(Employee* this,int* id);

int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);

int employee_setSueldo(Employee* this,int sueldo);
int employee_getSueldo(Employee* this,int* sueldo);

int employee_CompareByName(void* e1, void* e2);

int employee_FilterSalary(void* pElement);

void* employee_MapSalary(void* pElement);


int main(void)
{
       // startTesting(1);  // ll_newLinkedList
      // startTesting(2);  // ll_len
        //startTesting(3);  // getNode - test_getNode
     // startTesting(4);  // addNode - test_addNode
     // startTesting(5);  // ll_add
       // startTesting(6);  // ll_get
       // startTesting(7);  // ll_set
      //  startTesting(8);  // ll_remove
      //  startTesting(9);  // ll_clear
      //  startTesting(10); // ll_deleteLinkedList
     //  startTesting(11); // ll_indexOf
     // startTesting(12); // ll_isEmpty
      // startTesting(13); // ll_push
    //   startTesting(14); // ll_pop
    //  startTesting(15); // ll_contains
      //  startTesting(16); // ll_containsAll
     //   startTesting(17); // ll_subList
     //  startTesting(18); // ll_clone
      //  startTesting(19); // ll_sort


    LinkedList* miLista;
    LinkedList* miListaDos;
    LinkedList* miListaTres;
    LinkedList* miListaCuatro;
    LinkedList* miListaSueldosMayores=NULL;
    LinkedList* miListaBajandoSalarios=NULL;



    miLista = ll_newLinkedList();
    miListaDos = ll_newLinkedList();
    //miListaTres = ll_newLinkedList();


    FILE* pFile;
    pFile = fopen("data.csv", "r");
    int i=0;
    int cont;
    char id[50];
    char nombre[50];
    char horas[50];
    char sueldo[50];
    Employee* miEmpleado;
    Employee nuevoEmpleado={9999,"Alexis Masevicius",50,20};
    Employee nuevoEmpleadoDos={8888,"Christian Baus",80,25};
    Employee nuevoEmpleadoTres={7777,"Mauricio Davila",10,25};

    int indexAlexis;
    int auxLen;
    int aux;




    cont = fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]",id,nombre,horas,sueldo);
    while(!feof(pFile))
    {
        cont = fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]",id,nombre,horas,sueldo);

        if(cont==4)
        {
            miEmpleado=employee_newParametros(id,nombre,horas,sueldo);

            ll_add(miLista, miEmpleado);
            ll_add(miListaDos, miEmpleado);

            i++;
        }

    }
    fclose(pFile);

    printf("\nLISTA ORIGINAL:\n");

    employee_list(miLista,ll_len(miLista));

    ll_add(miLista,&nuevoEmpleado);
    printf("\nEl empleado agregado es: \n");
    mostrarEmpleado(&nuevoEmpleado);
    employee_list(miLista,ll_len(miLista));



    printf("\nEl largo de la lista es: %d\n\n\n",ll_len(miLista));



    ll_set(miLista,998,&nuevoEmpleadoDos);
    miEmpleado=ll_get(miLista,998);
    employee_list(miLista,ll_len(miLista));
    printf("\nEmpleado modificado con set es: %s\n",miEmpleado->nombre);


    ll_remove(miLista,998);
    ll_remove(miListaDos,998);
    printf("\nEmpleado removido es: %s\n",miEmpleado->nombre);
    employee_list(miLista,ll_len(miLista));

    indexAlexis=ll_indexOf(miLista,&nuevoEmpleado);
    printf("\nEl indice de Alexis es: %d\n",indexAlexis);

    printf("\nPush de Mauricio Davila:\n");
    ll_push(miLista,998,&nuevoEmpleadoTres);
    employee_list(miLista,ll_len(miLista));

    printf("\nPop de Mauricio Davila:\n");
    ll_pop(miLista,998);
    employee_list(miLista,ll_len(miLista));

    aux=ll_contains(miLista,&nuevoEmpleado);
    if(aux==1)
    {
        printf("\nEl empleado Alexis esta contenido en la lista\n");
    }


    aux=ll_containsAll(miLista,miListaDos);
    if(aux==1)
    {
        printf("Los empleados de la lista Dos estan contenidos en la uno");
    }

    miListaTres=ll_subList(miLista,0,997);
    printf("\nLa sublista copiada hasta el anteultimo es:\n");
    employee_list(miListaTres,ll_len(miLista));

    miListaCuatro=ll_clone(miLista);
    printf("\nLa lista clonada es:\n");
    employee_list(miListaCuatro,ll_len(miListaCuatro));

    ll_sort(miLista,employee_CompareByName,1);
    printf("\nLa lista ordenada es:\n");
    employee_list(miLista,ll_len(miLista));

    miListaSueldosMayores=ll_filter(miLista,employee_FilterSalary);
    printf("\nLa lista filtrada es:(primeros 20)\n");
    employee_listDos(miListaSueldosMayores,ll_len(miListaSueldosMayores));

    miListaBajandoSalarios=ll_map(miLista,employee_MapSalary);
    printf("\nLa lista mapeada, descontando el 25 a los salarios es:(primeros 20)\n");
    employee_list(miListaBajandoSalarios,ll_len(miListaBajandoSalarios));





    ll_clear(miLista);
    auxLen=ll_len(miLista);
    printf("\nLista vaciada, tamanio de la lista: %d\n", auxLen);




    ll_deleteLinkedList(miLista);
    ll_deleteLinkedList(miListaDos);
    ll_deleteLinkedList(miListaTres);
    ll_deleteLinkedList(miListaCuatro);

    return 0;
}

Employee* employee_new()
{
    Employee* miEmpleado;

    miEmpleado=(Employee*) malloc (sizeof(Employee));

    return miEmpleado;

}

Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldoStr)
{
    Employee* miEmpleado;


    miEmpleado=employee_new();


    if(employee_setId(miEmpleado,atoi(idStr))==0 ||
        employee_setNombre(miEmpleado,nombreStr)==0 ||
        employee_setHorasTrabajadas(miEmpleado,atoi(horasTrabajadasStr))==0 ||
        employee_setSueldo(miEmpleado,atoi(sueldoStr))==0)
    {
        free(miEmpleado);
        miEmpleado=NULL;
    }

    return miEmpleado;// retornar mieEmpleado // si no miEmpleado=NULL

}


int employee_setId(Employee* this,int id)
{
    if(id>0 && this!=NULL)
    {
        this -> id = id;
        return 1;
    }
    else
    {
        return 0;
    }
}

int employee_getId(Employee* this,int* id)
{
    if(this!=NULL && id!=NULL)
    {
        *id = this->id;
        return 1;
    }
    else
    {
        return 0;
    }
}

int employee_setNombre(Employee* this,char* nombre)
{
    if(this!=NULL && nombre!=NULL)
    {
        strcpy(this->nombre,nombre);
        return 1;
    }
    else
    {
        return 0;
    }
}
int employee_getNombre(Employee* this,char* nombre)
{
    if(this!=NULL && nombre!=NULL)
    {
        strcpy(nombre,this->nombre);
        return 1;
    }
    else
    {
        return 0;
    }
}

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
    if(this!=NULL)
    {
        this -> horasTrabajadas = horasTrabajadas;
        return 1;
    }
    else
    {
        return 0;
    }
}

int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
    if(this!=NULL && horasTrabajadas!=NULL)
    {
        *horasTrabajadas = this->horasTrabajadas;
        return 1;
    }
    else
    {
        return 0;
    }

}

int employee_setSueldo(Employee* this,int sueldo)
{
    if(this!=NULL)
    {
        this -> sueldo = sueldo;
        return 1;
    }
    else
    {
        return 0;
    }
}

int employee_getSueldo(Employee* this,int* sueldo)
{
    if(this!=NULL && sueldo!=NULL)
    {
        *sueldo = this->sueldo;
        return 1;
    }
    else
    {
        return 0;
    }
}


int employee_list(LinkedList* pArrayListEmployee, int len)
{
    int i;
    Employee* aux;

    printf("ID   |        NOMBRE  | HORAS   |  SUELDO\n");
    for(i=993; i<len; i++)
    {
        aux=(Employee*)ll_get(pArrayListEmployee, i);
        mostrarEmpleado(aux);
    }

    return 0;
}

int employee_listDos(LinkedList* pArrayListEmployee, int len)
{
    int i;
    Employee* aux;

    printf("ID   |        NOMBRE  | HORAS   |  SUELDO\n");
    for(i=0; i<20; i++)
    {
        aux=(Employee*)ll_get(pArrayListEmployee, i);
        mostrarEmpleado(aux);
    }

    return 0;
}

int mostrarEmpleado(Employee* aux)
{
    int todoOk=0;
    int id;
    int horas;
    char nombre[50];
    int sueldo;
    int auxInt;
    int auxNom;
    int auxHoras;
    int auxSueldo;


    auxInt=employee_getId(aux, &id); //PONER LA VALIDACION DENTRO IF
    auxNom=employee_getNombre(aux, nombre);
    auxHoras=employee_getHorasTrabajadas(aux, &horas);
    auxSueldo=employee_getSueldo(aux,&sueldo);

    if(auxInt==1 && auxNom==1 && auxHoras==1 && auxSueldo==1)
    {
        printf("%4d |%15s |%8d | %4d\n",id,nombre,horas,sueldo);
        todoOk=1;
    }

    return todoOk;
}



int employee_CompareByName(void* e1, void* e2)
{
    Employee* auxEmpleado;
    Employee* auxEmpleadoDos;
    char nombreUno[50];
    char nombreDos[50];


    int resultado;
    auxEmpleado=e1;
    auxEmpleadoDos=e2;

    if(e1!=NULL && e2!=NULL)
    {
        employee_getNombre(auxEmpleado,nombreUno);
        employee_getNombre(auxEmpleadoDos,nombreDos);
        resultado=strcmp(nombreUno,nombreDos);
    }

    return resultado;
}

int employee_FilterSalary(void* pElement)
{
    return ((Employee*) pElement)->sueldo>40000;
}

void* employee_MapSalary(void* pElement)
{
    Employee* AuxEmployee;
    int auxSueldo;
    int auxDescuento;

    AuxEmployee=employee_new();

    AuxEmployee->id=((Employee*)pElement)->id;
    strcpy(AuxEmployee->nombre,((Employee*)pElement)->nombre);
    AuxEmployee->sueldo=((Employee*)pElement)->sueldo;
    AuxEmployee->horasTrabajadas=((Employee*)pElement)->horasTrabajadas;

    auxSueldo=AuxEmployee->sueldo;

    if(auxSueldo>0)
    {
        auxDescuento=auxSueldo*0.25;
        auxSueldo=auxSueldo-auxDescuento;
        AuxEmployee->sueldo=auxSueldo;
    }



    return AuxEmployee;
}













