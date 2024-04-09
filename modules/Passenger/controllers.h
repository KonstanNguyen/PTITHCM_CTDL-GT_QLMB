#ifndef __PASSENGER__CONTROLLERS__
#define __PASSENGER__CONTROLLERS__

#include <cstring>
#include <conio.h>
#include "..\..\data\routers.h"
#include "models.h"

int xKeyDisplayPas[5] = {1,19,44,62,74};

void InputPass(TreePass &rootPass, Passenger &pass, bool Check = false);
void ShowPass(Passenger &pass, int position);
void ShowListPassOnePage(TreePass root, int startIndex);
void ChangePassMenuManagerPage(TreePass root);
void MenuManagePassenger(TreePass &rootPass );

//Nhap thong tin hanh khach
void InputPass(TreePass &rootPass, Passenger &pass, bool Check)
{
	ShowCursor(true);
	int ordinal = 0;	//thu tu nhap
	int position = -1;	//vi tri hanh khach
	CreateForm(ContentPass, 0, 4, 27);
	if(Check) 
	{
		RemoveRow(X_Add,Y_Add,ContentPass[0],27);
		ordinal = 1;
	}
	while(true){
		switch(ordinal){
			case 0:{	//Nhap CMND
				gotoxy(X_Add+10,Y_Add);
				char *str = Input(SIZE_ID_PASS, Number);
				pass.id = atoi(str);
				freeMemmorry(str);

				if(pass.id < 1){
					Notification("Vui long khong bo trong");
					break;
				}
				if(SearchPass(rootPass, pass.id)){
					Notification("CMND da ton tai");
					break;
				}
				ordinal++;
				break;
			}
			case 1:{	//Nhap Ho
				gotoxy(X_Add+10,Y_Add+3);      

				char *str = Input(sizeof(pass.firstName), Text);
				strcpy(pass.firstName, str);
				freeMemmorry(str);

				if(strlen(pass.firstName) == 0){
					Notification("Vui long khong bo trong");
					break;
				}
				ordinal++;
				break;
			}
			case 2:{	//Nhap Ten
				gotoxy(X_Add+10,Y_Add+6);
				char *str = Input(sizeof(pass.lastName), Text);
				strcpy(pass.lastName, str);
				freeMemmorry(str);

				if(strlen(pass.lastName) == 0){
					Notification("Vui long khong bo trong");
					break;
				}
				ordinal++;
				break;
			}
			case 3:{	//Nhap gioi tinh
				int signal = MenuSelect(X_Add+9,Y_Add+9,2,ContentGender);
				pass.gender = --signal;
				ordinal++;
				break;
			}
			case 4:{
				InsertPass(rootPass, pass);
				RemoveForm(0, 4, 27);
				RemoveBox(X_Add+9,Y_Add+9,16,4);
				ShowCursor(false);
				return;
			}
		}
	}
}

void EditPass(TreePass &rootPass, Passenger &pass)
{
	ShowCursor(false);
	int ordinal = 0;	//thu tu nhap
	int position = -1;	//vi tri hanh khach
	char *str;
	PPassNode temp;

	CreateRow(X_Add, Y_Add, ContentAirplane[0], 27);
	while(true){
		Clean(X_Add+10,Y_Add,X_Add+21,Y_Add);
		gotoxy(X_Add+10,Y_Add);
		str = Input(SIZE_ID_PASS, ID);
		pass.id = atoi(str);
		freeMemmorry(str);
		
		temp = SearchPass(rootPass, pass.id);
		if(!temp)
			Notification("ID khong ton tai");
		else
			break;
	}
	
	CreateForm(ContentPass, 0, 4, 27);
	SetBGColor(BLUE_LIGHT);
	
	gotoxy(X_Add+10,Y_Add);
	std::cout << std::setw(16) << std::left << temp->data.id;
	gotoxy(X_Add+10,Y_Add+3);
	std::cout << std::setw(16) << std::left << temp->data.firstName;
	gotoxy(X_Add+10,Y_Add+6);
	std::cout << std::setw(16) << std::left << temp->data.lastName;
	gotoxy(X_Add+9,Y_Add+9);
	std::cout << std::setw(16) << std::left << (temp->data.gender) ? "Nu" : "Name";

	while(true){
		SetBGColor(BLACK);
		switch(ordinal){
			case 0:{	//Nhap CMND
				while(true){
					ShowCursor(true);
					gotoxy(X_Add+10,Y_Add);
					char *str;
					if(kbhit()){
						Clean(X_Add+10,Y_Add, X_Add+20,Y_Add);
						str = Input(SIZE_ID_PASS, Number);

						if(strcmp(str, "") == 0){
							gotoxy(X_Add+10,Y_Add);
							std::cout << std::setw(10) << std::left << temp->data.id;
							freeMemmorry(str);
							break;
						}else{
							pass.id = atoi(str);
							freeMemmorry(str);
							if(SearchPass(rootPass, pass.id)){
								Notification("CMND da ton tai");
								Clean(X_Add+10,Y_Add, X_Add+20,Y_Add);
							}else{
								break;
							}
						}
					}	
				}
				ShowCursor(false);
				ordinal++;
				break;
			}
			case 1:{	//Nhap Ho
				if(kbhit()){
					ShowCursor(true);
					Clean(X_Add+10, Y_Add+3, X_Add+21, Y_Add+3);
					gotoxy(X_Add+10,Y_Add+3);      
					str = Input(sizeof(pass.firstName), Text);
					if(strcmp(str, "") == 0){
						gotoxy(X_Add+10, Y_Add+3);
						std::cout << std::setw(10) << std::left << temp->data.firstName;
						freeMemmorry(str);
						break;
					}else{
						strcpy(pass.firstName, str);
						freeMemmorry(str);

						if(strcmp(pass.firstName, "") == 0){
							Notification("Vui long khong bo trong");
							Clean(X_Add+10, Y_Add+3, X_Add+21, Y_Add+3);
							gotoxy(X_Add+10, Y_Add+3);
							break;
						}
					}
				}
				ShowCursor(false);
				ordinal++;
				break;
			}
			case 2:{	//Nhap Ten
				gotoxy(X_Add+10,Y_Add+6);
				char *str = Input(sizeof(pass.lastName), Text);
				strcpy(pass.lastName, str);
				freeMemmorry(str);

				if(strlen(pass.lastName) == 0){
					Notification("Vui long khong bo trong");
					break;
				}
				ordinal++;
				break;
			}
			case 3:{	//Nhap gioi tinh
				int signal = MenuSelect(X_Add+9,Y_Add+9,2,ContentGender);
				pass.gender = --signal;
				ordinal++;
				break;
			}
			case 4:{
				InsertPass(rootPass, pass);
				RemoveForm(0, 4, 27);
				RemoveBox(X_Add+9,Y_Add+9,16,4);
				ShowCursor(false);
				return;
			}
		}
	}
}

//Xuat thong tin 1 hanh khach
void ShowPass(Passenger &pass, int position)
{
	gotoxy(xKeyDisplayPas[0] + 3, Y_Display + position + 3);
    std::cout << std::left << std::setw(SIZE_ID_PASS) << std::setfill('0') << pass.id;
    gotoxy(xKeyDisplayPas[1] + 3, Y_Display + position + 3);
    std::cout << std::left << pass.firstName;
    gotoxy(xKeyDisplayPas[2] + 3, Y_Display + position + 3);
    std::cout << std::left << pass.lastName;
    gotoxy(xKeyDisplayPas[3] + 3, Y_Display + position + 3);
	std::cout << std::left << (pass.gender ? "Nu" : "Nam");
}

//Xuat danh sach hanh khach trong 1 trang
//void ShowListPassOnePage(TreePass root, int startIndex)
//{
//	WORD curColor;
//	GetColor(curColor);
//	SetColor(WHITE); //cac phan tu hien trong bang se co chu mau trang
//
//	int position = 0;
//	int count = 0;
//	
//	PPassenger temp;
//	PPassNode node;
//	Queue<Passenger> queue;
//	InitQueue(queue);
//	pushQueue(queue, root->data);
//	RemoveContent(xKeyDisplayPas,4);
//	PreOrder(root, position);
//	
//	SetColor(curColor);
//	gotoxy(3,3);
//	std::cout << " So luong hanh khach : " << countPass(root);
//	gotoxy(X_Page,Y_Page);
//	std::cout <<" Trang " << CurPage <<"/"<< TotalPage;
//}

void ShowListPassOnePage(TreePass root, int startIndex)
{
	WORD curColor;
	GetColor(curColor);
	SetColor(WHITE); //cac phan tu hien trong bang se co chu mau trang
	int position = 0;
	int count = 0;
	
	gotoxy(3,3);
	std::cout << " So luong hanh khach : " << countPass(root);
	
	PPassenger temp;
	PPassNode node;
	Queue<Passenger> queue;
	InitQueue(queue);
	pushQueue(queue, root->data);

	RemoveContent(xKeyDisplayPas, 4);
	while (!emptyQueue(queue))
	{
		temp = frontQueue(queue);
		popQueue(queue);
		node = (PPassNode)(temp);
		if(node->pLeft != NULL){
			pushQueue(queue, node->pLeft->data);
		}
		if(node->pRight != NULL){
			pushQueue(queue, node->pRight->data);
		}
		if(count < startIndex){
			count++;
			continue;
		}
		ShowPass(*temp, position);
		++position;
		
		if(position >= NumberPerPage){
			break;
		}
	}
	
	SetColor(curColor);
	gotoxy(X_Page,Y_Page);
	std::cout <<" Trang " << CurPage <<"/"<< TotalPage; 
}

//Thay doi danh sach hanh khach sang trang khac
void ChangePassMenuManagerPage(TreePass root)
{
	DisplayTest(xKeyDisplayPas, ContentPass,sizeof(ContentPass)/sizeof(std::string) );
	ShowListPassOnePage(root,(CurPage-1)*NumberPerPage);
}

//Quan ly hanh khach
void MenuManagePassenger(TreePass &rootPass ){
	CurPage = 1;
	TotalPage = (int)ceil((double)countPass(rootPass)/NumberPerPage); 	//ceil : lam tron 
	
	DisplayTest(xKeyDisplayPas, ContentPass, sizeof(ContentPass)/sizeof(std::string));
	ShowListPassOnePage(rootPass, 0);
	
	gotoxy(X_TitlePage,Y_TitlePage);
	std::cout << "QUAN LY HANH KHACH";
	
	int signal;
	Passenger pass;

	while(true)
	{
		signal = MenuSelect(X_ThaoTac,Y_ThaoTac,5,ContentPassSelect);
		switch(signal) {
			case 1: // Them hanh khach
			{
				if(CurPage == 0) CurPage = 1;
				InputPass(rootPass, pass);

				TotalPage = (int)ceil((double)countPass(rootPass)/NumberPerPage);
				ShowListPassOnePage(rootPass, (CurPage-1)*NumberPerPage);
				ShowCursor(false);
				break;
			}
			case 2:
			{
				ShowCursor(false);
				if(CurPage == 0) CurPage = 1;

				EditPass(rootPass, pass);

				TotalPage = (int)ceil((double)countPass(rootPass)/NumberPerPage);
				ShowListPassOnePage(rootPass, (CurPage-1)*NumberPerPage);
				break;
			}
			case LEFT:
			case 3: //Chuyen trang truoc
			{
				if(CurPage == 1) break;
				else{
					CurPage--;
					ChangePassMenuManagerPage(rootPass);
				}
				break;
			}
			case RIGHT:
			case 4:	//Chuyen trang tiep
			{
				if(CurPage >= TotalPage) break;
				else{
					CurPage++;
					ChangePassMenuManagerPage(rootPass);
				}
				break;
			}
			case 5:
				return;
			default: 
				break;
			
		}
	}
}

#endif