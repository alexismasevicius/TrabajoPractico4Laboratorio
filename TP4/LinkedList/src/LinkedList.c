#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"

static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this;

    this = (LinkedList*) malloc(sizeof(LinkedList)); // guarda la direccion de memoria de la LL creada
    if(this!=NULL)
    {
        this->size = 0;                              //tamanio 0
        this->pFirstNode = NULL;                     //primer nodo vacio
    }

    return this;                                       //devuelve el puntero a la nueva LL
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
        returnAux = this->size;
    }


    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* pNode = NULL;
    int aux;
    int i;

    if(this!=NULL)
    {
        aux=ll_len(this);
        if(nodeIndex>=0 && aux>nodeIndex)       // verifica si el indice es mayor o igual a cero y menor al largo de la lista
        {
            pNode=this->pFirstNode;             //asigno pNode al primer lugar de la LL.
            for(i=0; i<nodeIndex; i++)          //recorre todos los nodos de LL hasta el indice anterior al recibido por parametro
            {
                pNode= pNode->pNextNode;        // devuelve el puntero al proximo nodo (el nodo que se pide devolver)
            }
        }
    }

    return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* nuevoNodo = NULL;

    if(this!=NULL && nodeIndex >=0 && nodeIndex<= ll_len(this))
    {
        nuevoNodo=(Node*)malloc(sizeof(Node));
        if(nuevoNodo!=NULL)
        {
            nuevoNodo->pElement = pElement;
            nuevoNodo->pNextNode = getNode(this, nodeIndex);
            if(nodeIndex==0)
            {
                this->pFirstNode=nuevoNodo;
            }
            else
            {
                 (getNode(this,nodeIndex-1))->pNextNode = nuevoNodo;
            }


            this->size++;
            returnAux=0;
        }

    }

    return returnAux;
}


/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int indice = 0;
    //Node* actual; ???

    if(this!=NULL)
    {
        indice=ll_len(this);                        //cantidad de elementos = indice nuevo elemento
        returnAux=addNode(this,indice,pElement);       //AddNode: Agrega y enlaza un nuevo nodo a la lista (Puntero a lista, indice, carga)
    }

    return returnAux;
}


/** \brief Devuelve el elemento gurdado en el indice especificado
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* nodoAux;

    if(this!=NULL && index>=0 && index<ll_len(this))
    {
        nodoAux=getNode(this, index);          //traigo en nodo del indice especificado
        if(nodoAux!=NULL)
        {
            returnAux=nodoAux->pElement;        //retorno el puntero a la carga
        }
    }


    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* actual;

    if(this!=NULL && index>=0 && index<ll_len(this))
    {
        actual=getNode(this,index);         //traigo el nodo que voy a modificar

        if(actual!=NULL)
        {
            actual->pElement=pElement;      //modifico la carga
            returnAux=0;
        }
    }


    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* actual;
    Node* prev;

    if(this!=NULL && index>=0 && index<ll_len(this))
    {
        actual=getNode(this,index);             //traigo el nodo
        if(index==0)                            //Si es el primer elemento de la LL
        {
            this->pFirstNode = actual->pNextNode;  //engancho la lista con el siguiente nodo
            returnAux=0;
        }
        else                                    //si es otro elemento
        {
            prev=getNode(this,index-1);         //traigo en nodo anterior
            prev->pNextNode=actual->pNextNode;  //engancho en nodo anterior al siguiente nodo
        }
        this->size--;
        free(actual);
        returnAux=0;
    }


    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    //Node* nodo;
    int flag = 1;

    if(this!=NULL)
    {
        for(int i=ll_len(this)-1; i>=0 ; i--)       //voy removiendo de atras para adelante
        {
            if(ll_remove(this, i) == -1)            //si falla
            {
                flag = 0;                           //salgo de la iteracion
                break;
            }
        }
        if(flag)                                // si todoOK retorno 0
        {
            returnAux=0;
        }
    }


    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
        if(ll_clear(this)==0)
        {
            free(this);
            returnAux = 0;
        }
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int i;
    int len;



    if(this!=NULL)
    {
        len=ll_len(this);
        for(i=0;i<len;i++)
        {
            if(ll_get(this,i) == pElement)  //devuelve el elemento guardado en el indice especificado y compara su direccion de memoria con pElement
            {
                returnAux=i;            //devuelve el indice del elemento
                break;
            }
        }
    }

    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        returnAux=0;
        if(!ll_len(this))
        {
            returnAux=1;
        }

    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    int len;

    len=ll_len(this);

    if(this!=NULL)
    {
        if(index>=0 && index<=len)          // menor o igual porque puede querer agregar al final
        {

           addNode(this, index, pElement);

            returnAux=0;
        }
    }

    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;

    int len;

    len=ll_len(this);

   if(this!=NULL && index>=0 && index<len)
    {
        returnAux=ll_get(this,index);
        ll_remove(this,index);
    }

    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this!=NULL)
    {
        returnAux=0;
        if(ll_indexOf(this,pElement)!=-1)
        {
            returnAux=1;
        }

    }

    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int lenDos;

    if(this!=NULL && this2!=NULL)
    {
        returnAux=1;
        lenDos=ll_len(this2);
        for(int i=0;i<lenDos;i++)
        {
            if(!ll_contains(this,ll_get(this2,i)))
            {
                returnAux=0;
                break;
            }

        }
    }

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    int i;
    void* pElement;
    int len;

    len=ll_len(this);
    if(this!=NULL && from>=0 && from<=to && to<=len)
    {
        cloneArray=ll_newLinkedList();

            for(i=from;i<to;i++)   //copiar solo los elementos pasados de from a to
            {
                pElement=ll_get(this,i);
                ll_add(cloneArray,pElement);
            }
    }


    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    int len;

    if(this!=NULL)
    {
        len=ll_len(this);
        cloneArray=ll_subList(this,0,len);
    }

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void*,void*), int order)
{
    int returnAux =-1;
    void* pAux;
    void* pAuxTwo;
    void* aux;
    int i;
    int j;
    int len;

    if(this!=NULL && pFunc!=NULL && order>-1 && order<2)
    {
        returnAux=0;

        len=ll_len(this);

        for(i=0;i<len-1;i++)
        {
            for(j=i+1;j<len;j++)
            {
                pAux=ll_get(this, i);
                pAuxTwo=ll_get(this, j);
                if(order==1)                                //Si el orden es ascendente
                {
                    if(pFunc(pAux,pAuxTwo)==1)              //siPfuncion me devuelve uno hace swap (ES DECIR SI ES MAYOR HACE SWAP)
                    {
                        aux=pAux;
                        ll_set(this,i,pAuxTwo);
                        ll_set(this,j,aux);
                    }
                }
                if(order==0)                            //si el orden es descendiente
                {
                    if(pFunc(pAux,pAuxTwo)==-1)         //si Pfuncion me devuelve -1 hace swap (ES DECIR SI ES MENOR HACE SWAP)
                    {
                        aux=pAux;
                        ll_set(this,i,pAuxTwo);
                        ll_set(this,j,aux);
                    }
                }

            }
        }

    }



    return returnAux;
}

/** \brief devuelve un nuevo linkedList cargado con los elementos que pasan la funcion filtro
 *
 * \param LinkedList* Puntero a la lista
 * \param void*(*pFunc) Puntero a la funcion que filtra (1=si entra | 0=no entra)
 * \return LinkedList* Nuevo puntero a linkedlist con los elementos que pasaron la funcion filtro
 *
 */
LinkedList* ll_filter (LinkedList* this, int (*pFunc)(void*) )
{
    LinkedList* filterList=NULL;
    void* aux = NULL;
    int len;

    if(this!=NULL && pFunc!=NULL)
    {
        filterList=ll_newLinkedList();
        len=ll_len(this);
        if(filterList!=NULL)
        {
            for(int i=0;i<len;i++)
            {
                aux=ll_get(this,i);
                if(pFunc(aux))
                {
                    if(ll_add(filterList,aux))
                    {
                       free(filterList);
                       filterList=NULL;
                       break;
                    }
                }
            }
        }
    }
    return filterList;
}


LinkedList* ll_map(LinkedList* this, void* (*pFunc)(void*))
{
    LinkedList* mapList=NULL;
    void* aux = NULL;
    void* auxDos = NULL;
    int len;

    if(this!=NULL && pFunc!=NULL)
    {
        mapList=ll_newLinkedList();
        len=ll_len(this);
        for(int i=0; i<len; i++)
        {
            aux=ll_get(this,i);
            auxDos=pFunc(aux);
            ll_add(mapList,auxDos);
        }
    }
    return mapList;
}
