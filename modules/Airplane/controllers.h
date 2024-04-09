#ifndef __AIRPLANE__CONTROLLERS__
#define __AIRPLANE__CONTROLLERS__

#include <iostream>
#include <cstring>
#include <iomanip>
#include <math.h>

#include "../../utils/String.h"
#include "../../data/routers.h"
#include "../../utils/UserInterface.h"
#include "models.h"

int xKeyDisplayAir[6] = {1,19,37,50,63,76};

//Nhap thong tin may bay
void InputAirplane(ListAir &list, Airplane &air, bool Edit = false, bool Delete = false){
	int ordinal = 0;	// thu tu nhap	
	int position = -1;	// vi tri may bay
	char *str;
	if(Edit == false && Delete == false)
		CreateForm(ContentAirplaneInput,0,3,27);
	if(Edit == true){

	}
	while(true){
		ShowCursor(true);
		switch(ordinal){
			case 0:{	//Nhap so hieu may bay			
				do{
					CreateRow(X_Add, Y_Add, ContentAirplane[0], 27);

					gotoxy(X_Add+10,Y_Add);
					str = Input(sizeof(air.idAir), ID);
					strcpy(air.idAir, str);
					freeMemmorry(str);

					position = IndexAirplane(list, air.idAir);
					if(strlen(air.idAir) == 0)
						Notification("Vui long khong bo trong");		
					if(position > -1 && Edit == false && Delete == false)
						Notification("ID da ton tai");
					if(position < 0 && (Edit == true || Delete == true) && (strlen(air.idAir) != 0))
						Notification("ID khong ton tai");
					if(position > -1 && Delete == true){
						ShowCursor(false);
//						if(IndexAirplane(list, fli.idAir) < 0){
							Box(X_Notification,Y_Notification, 27, 3, "Ban co chac muon xoa khong? ");
							gotoxy(X_Notification+1,Y_Notification+2);
							std::cout << "ESC: Huy - ENTER: Xoa";
						
							char c = _getch();
							RemoveRow(X_Add, Y_Add, ContentAirplane[0], 27);
							RemoveBox(X_Notification,Y_Notification, 27, 3);
						
							if (c == ESC)
								Notification("Xoa that bai!");
							else if (c == ENTER){
								RemoveAirplane(list, position);
								Notification("Xoa thanh cong!");
							}		
//						}else Notification("May bay da thuc hien chuyen bay");
										
						return;
					}
					if(
						(position > -1 && Edit == true) ||
						(position < 0 && Edit == false && Delete ==  false && (strlen(air.idAir) != 0)) 
					)break;
				}while(true);
				
				if(Edit){
					ShowCursor(false);
					CreateForm(ContentAirplaneInput,0,3,27);
					Box(X_Add-3,Y_Add-4, 44, 2, "Phan nao khong muon chinh sua. Hay bo trong!");
					gotoxy(X_Add+15,Y_Add+6);
					std::cout << "    x    ";
					
					WORD current;
					GetColor(current);
					SetBGColor(YELLOW);
					
					Airplane temp = *list.nodes[position];

					gotoxy(X_Add+10,Y_Add);
					std::cout << std::setw(strlen(temp.idAir)) << std::left << temp.idAir;
					gotoxy(X_Add+11,Y_Add + 3);
					std::cout << std::setw(strlen(temp.typeAir)) << std::left << temp.typeAir;
					gotoxy(X_Add+15,Y_Add+6);
					std::cout << std::setw(3) << std::left << temp.col;
					gotoxy(X_Add+21,Y_Add+6);
					std::cout << std::setw(3) << std::left << temp.row;

					SetBGColor(BLACK);
					while (true){
						SetBGColor(BLACK);
						gotoxy(X_Add+10,Y_Add);
						ShowCursor(true);
						if(kbhit()){
							Clean(X_Add+10,Y_Add, X_Add+20,Y_Add);
							str = Input(sizeof(air.idAir), ID);
							if(strcmp(str,"") == 0){
								gotoxy(X_Add+10,Y_Add);
								std::cout << std::setw(strlen(temp.idAir)) << std::left << temp.idAir;
								freeMemmorry(str);
								break;
							}else{
								strcpy(air.idAir, str);
								freeMemmorry(str);
								if (IndexAirplane(list, air.idAir) > -1){
									Notification("ID da ton tai");
									Clean(X_Add+10,Y_Add, X_Add+20,Y_Add);
								}else
									break;
							}
						}						
					}
				}
				ShowCursor(false);
				ordinal++;
				break;
			}
			case 1:{	//Nhap loai may bay
			
				Clean(X_Add+11,Y_Add + 3, X_Add+27,Y_Add + 3);
				gotoxy(X_Add+11,Y_Add+3);
				str = Input(sizeof(air.typeAir), Text);
				strcpy(air.typeAir, str);
				freeMemmorry(str);

				if(strlen(air.typeAir) == 0 && Edit == false){
					Notification("Vui long khong bo trong");
					break;
				}
				ordinal++;
				break;
			}
			case 2: { //Nhap so cot va so hang
				gotoxy(X_Add+15,Y_Add+6);
				std::cout << "    x    ";

				gotoxy(X_Add+15,Y_Add+6);
				str = Input(5, Number);
				air.col = atoi(str);
				freeMemmorry(str);
				
				gotoxy(X_Add+15+7,Y_Add+6);
				str = Input(5, Number);
				air.row = atoi(str);
				freeMemmorry(str);
				
				if((air.col < 1 || air.row < 1) && Edit == false){
					Notification("Vui long khong bo trong");
					break;
				}	
				if((air.col >= 0 || air.row >= 0) && (air.col*air.row < MINSEAT)){
					Notification("So cho phai >= 20");	
					break;
				}
				ordinal++;
				break;
			}
			case 3:{
				//Chinh sua
				if(Edit) {
					if(strlen(air.idAir) != 0)
						strcpy(list.nodes[position]->idAir, air.idAir);					
					if (strlen(air.typeAir) != 0)
						strcpy(list.nodes[position]->typeAir, air.typeAir);
					if (air.col >= 1)
						list.nodes[position]->col = air.col;
					if (air.row >= 1)
						list.nodes[position]->row = air.row;
					Notification("Chinh sua thanh cong");
				}
				//Them moi
				else 
				{
					InsertListAir(list, air);
					Notification("Them thanh cong");
				}
				RemoveForm(0, 3, 27);
				RemoveBox(X_Add-3,Y_Add-4, 44, 2);
			}
			return;
		}
	}	
	ShowCursor(false);
}

//Xuat thong tin 1 may bay
void ShowAirplane(PAirplane pAir, int position)
{	
	
	gotoxy(xKeyDisplayAir[0] + 3, Y_Display + position +3);
    std::cout << std::left << std::setw(8) << pAir->idAir;
    gotoxy(xKeyDisplayAir[1] + 3, Y_Display + position +3);
    std::cout << std::left << std::setw(14) << pAir->typeAir;
    gotoxy(xKeyDisplayAir[2] + 3, Y_Display + position +3);
    std::cout << std::left << std::setw(4) << pAir->col;
    gotoxy(xKeyDisplayAir[3] + 3, Y_Display + position +3);
    std::cout << std::left << std::setw(4) << pAir->row;
    gotoxy(xKeyDisplayAir[4] + 3, Y_Display + position +3);
    std::cout << std::left << std::setw(4) << (pAir->col * pAir->row);
}

//Xuat danh sach may bay trong 1 trang
void ShowListAirplaneOnePage(ListAir list, int startIndex)
{
	gotoxy(3,3);
	std::cout << " So luong may bay : " << list.size;
	int i;
	WORD curColor;
	GetColor(curColor);
	SetColor(WHITE); //cac phan tu hien trong bang se co chu mau trang
	RemoveContent(xKeyDisplayAir,5);
	for(i = 0 ; i + startIndex < list.size && i < NumberPerPage; i++)
	{
		ShowAirplane(list.nodes[i+startIndex], i); 
	} 
	SetColor(curColor);

	gotoxy(X_Page,Y_Page);
	std::cout <<" Trang " << CurPage <<"/"<< TotalPage; 
}

//Thay doi danh sach may bay qua trang khac
void ChangeAirplaneMenuManagerPage(ListAir list)
{
	DisplayTest(xKeyDisplayAir, ContentAirplane,sizeof(ContentAirplane)/sizeof(std::string) );
	ShowListAirplaneOnePage(list,(CurPage-1)*NumberPerPage);
}

//Quan ly may bay
void MenuManageAirplane(ListAir &list){
	ShowCursor(false);
	CurPage = 1;
	TotalPage = (int)ceil((double)list.size/NumberPerPage); 	//ceil : lam tron 
	
	DisplayTest(xKeyDisplayAir, ContentAirplane, sizeof(ContentAirplane)/sizeof(std::string));
	ShowListAirplaneOnePage(list, 0);
	
	gotoxy(X_TitlePage,Y_TitlePage);
	std::cout << "QUAN LY MAY BAY";
	
	int signal;
	Airplane air;

	while(true)
	{
		signal = MenuSelect(X_ThaoTac,Y_ThaoTac,6,ContentAirSelect);
		switch(signal) {
			case 1: // Them may bay
			{
				if(CurPage == 0) CurPage = 1;
				if(list.size == MAXAIRPLANE) 
				{	
					Notification("Danh sach da day, khong the them");
					return;
				}
				InputAirplane(list, air);
				
				TotalPage = (int)ceil((double)list.size/NumberPerPage);
				ShowListAirplaneOnePage(list, (CurPage-1)*NumberPerPage);
				ShowCursor(false);
				break;
			}
			case 2: //Xoa may bay
			{
				if(list.size == 0)
				{
					Notification("Danh sach rong, khong the xoa");
					break;
				}
				
				InputAirplane(list, air, false, true);
				
				TotalPage = (int)ceil((double)list.size / NumberPerPage);
				if (ListAirIsNull(list))  { //neu nhu danh sach khong co phan tu, trang 0/0
					CurPage = 0;
					ShowListAirplaneOnePage(list, 0);
				} else {
					if (CurPage > TotalPage) CurPage--;
					ShowListAirplaneOnePage(list, (CurPage-1) * NumberPerPage);
				}
				break;
			}
			case 3: //Chinh sua
			{
				if(list.size == 0)
				{
					Notification("Danh sach rong, khong the chinh sua");
					break;
				}
								
				InputAirplane(list, air, true, false);
				
				TotalPage = (int)ceil((double)list.size/NumberPerPage);
				ShowListAirplaneOnePage(list, (CurPage-1)*NumberPerPage);
				break;
			}
			case LEFT:
			case 4: //Chuyen trang truoc
			{
				if(CurPage == 1) break;
				else{
					CurPage --;
					ChangeAirplaneMenuManagerPage(list);
					break;
				}
			}
			case RIGHT:
			case 5:	//Chuyen trang sau
			{
				if(CurPage >= TotalPage) break;
				CurPage ++;
				ChangeAirplaneMenuManagerPage(list);
				break;
			}
			case 6:
			case -1:
				return;
			default:
				break;
		}
	}
}

#endif