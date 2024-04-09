#ifndef __AIRPLANE__UTILS__
#define __AIRPLANE__UTILS__

#include <string.h>
#include <fstream>

#include "../../types/KeyValue.h"
#include "types.h"

//Khoi tao danh sach may bay
void InitListAirplane(ListAir &listAir){
    listAir.size = 0;
}

//Kiem tra danh sach da day
bool ListAirIsFull(ListAir &listAir){
    return listAir.size == MAXAIRPLANE+1;
}

//Kiem tra danh sach chua co may bay
bool ListAirIsNull(ListAir &listAir){
    return listAir.size == 0;
}

//Tao may bay moi
PAirplane CreateAirplane(Airplane &air){
    PAirplane tmp = new Airplane;
    *tmp = air;
    tmp->amount = 0;
    return tmp;
}

//Vi tri may bay
int IndexAirplane(ListAir &list, const char* id){

    for (int i = 0; i < list.size; i++)
        if (stricmp(list.nodes[i]->idAir, id) == 0)
            return i;

    return -1;
}

//Them may bay vao danh sach
bool InsertListAir(ListAir &listAir, Airplane &air){
	if (ListAirIsFull(listAir))
        return false;
	listAir.nodes[listAir.size] = CreateAirplane(air);
	listAir.size++;
	return true;
}

//Xoa may bay
bool RemoveAirplane(ListAir &listAir, int position)
{
    if (position < 0 || position >= listAir.size)
        return false;
    int n = listAir.size;
    delete listAir.nodes[position];
    for (int i = position; i < n; i++)
    {
        listAir.nodes[i] = listAir.nodes[i + 1];
    }
    --listAir.size;
    return true;
}

void RemoveListAir(ListAir &listAir){
    for(int i = 0; i < MAXAIRPLANE+1; i++){
        delete listAir.nodes[i];
    }
}

#endif