#ifndef __TICKET__CONTROLLERS__
#define __TICKET__CONTROLLERS__

#include <cmath>
#include "models.h"
#include "../Passenger/controllers.h"
#include "../../types/KeyValue.h"

int xKeyDisplayTicket[4] = {1, 13, 25, 43};

void ShowTicket(Ticket ticket, int position);
void ShowListTicketOnePage(ListTicket listTicket, int startIndex, bool emptyTicket = false);
void ChangeTicketMenuManagerPage(ListTicket listTicket, bool emptyTicket);
void MenuManageTicket(Airplane air, ListTicket &listTicket, TreePass &rootPass, bool emptyTicket = false);

// Nhap thong tin ve
void InputTicket(Ticket &ticket)
{
	ShowCursor(true);
	CreateForm(ContentTicketInput, 0, 2, 27);

	char *str;
	//Nhap ID hanh khach
	gotoxy(X_Add + 12, Y_Add);
	str = Input(sizeof(SIZE_ID_PASS), Number);
	ticket.idPas = atoi(str);
	freeMemmorry(str);
	//Nhap vi tri ngoi
	gotoxy(X_Add + 12, Y_Add + 3);
	str = Input(sizeof(ticket.seat), ID);
	strcpy(ticket.seat, str);
	freeMemmorry(str);
}

// Xuat thong tin 1 ve
void ShowTicket(Ticket ticket, int position)
{
	gotoxy(xKeyDisplayTicket[0] + 3, Y_Display + position + 3);
	std::cout << std::left << std::setw(8) << ticket.seat;
	gotoxy(xKeyDisplayTicket[1] + 3, Y_Display + position + 3);
	if (ticket.statusTicket == 1)
		std::cout << std::left << std::setw(3) << "Da dat";
	else if (ticket.statusTicket == 0)
		std::cout << std::left << std::setw(3) << "Con ve";
	else
		std::cout << std::left << std::setw(3) << "Da huy";
	gotoxy(xKeyDisplayTicket[2] + 3, Y_Display + position + 3);
	std::cout << std::left << std::setw(SIZE_ID_PASS) << std::setfill('0') << ticket.idPas;
}

// Xuat thong tin danh sach ve trong 1 trang
void ShowListTicketOnePage(ListTicket listTicket, int startIndex, bool emptyTicket)
{

	WORD curColor;
	GetColor(curColor);
	SetColor(WHITE); // cac phan tu hien trong bang se co chu mau trang

	RemoveContent(xKeyDisplayTicket, 3);

	//    for(i = 0 ; i + startIndex < listTicket.sizeTotal && position < NumberPerPage; i++)
	//	{
	//		if(!emptyTicket){
	//			ShowTicket(listTicket.DSV[i+startIndex],position);
	//			position++;
	//		}
	//		else if(emptyTicket && listTicket.DSV[i+startIndex].statusTicket == 0){
	//			ShowTicket(listTicket.DSV[i+startIndex],position);
	//			position++;
	//		}
	//	}

	if (!emptyTicket)
	{
		gotoxy(3, 3);
		std::cout << "Ve: " << listTicket.sizeBooked << "/" << listTicket.sizeTotal;
		for (int i = startIndex; i < listTicket.sizeTotal && i < startIndex + NumberPerPage; i++)
			ShowTicket(listTicket.DSV[i], i - startIndex);
	}
	else
	{
		gotoxy(3, 3);
		std::cout << "Ve trong: " << listTicket.sizeTotal - listTicket.sizeBooked;
		int position = 0;
		int count = 0;
		for (int i = 0; i < listTicket.sizeTotal && position < NumberPerPage; i++)
		{
			if (listTicket.DSV[i].statusTicket == 0)
			{
				if (count < startIndex)
				{
					++count;
					continue;
				}
				ShowTicket(listTicket.DSV[i], position++);
			}
		}
	}

	SetColor(curColor);

	gotoxy(X_Page, Y_Page);
	std::cout << "Trang " << CurPage << "/" << TotalPage;
}

// Thay doi danh sach ve thanh trang khac
void ChangeTicketMenuManagerPage(ListTicket listTicket, bool emptyTicket)
{
	DisplayTest(xKeyDisplayTicket, ContentTicketOutput, sizeof(ContentTicketOutput) / sizeof(std::string));
	ShowListTicketOnePage(listTicket, (CurPage - 1) * NumberPerPage, emptyTicket);
}

// Quan ly ve
void MenuManageTicket(Airplane air, ListTicket &listTicket, TreePass &rootPass, bool emptyTicket)
{
	ShowCursor(false);
	CurPage = 1;

	gotoxy(20, 3);
	if (!emptyTicket)
	{
		std::cout << "_DANH SACH VE_";
		TotalPage = (int)ceil((double)listTicket.sizeTotal / NumberPerPage); // ceil : lam tron
	}
	else
	{
		std::cout << "_DANH SACH CAC VE CON TRONG_";
		TotalPage = (int)ceil((double)listTicket.sizeTotal - listTicket.sizeBooked / NumberPerPage); // ceil : lam tron
	}
	DisplayTest(xKeyDisplayTicket, ContentTicketOutput, sizeof(ContentTicketOutput) / sizeof(std::string));
	ShowListTicketOnePage(listTicket, 0);

	Ticket ticket_tmp;
	Passenger pass_tmp;
	int signal;

	while (true)
	{
		signal = MenuSelect(X_ThaoTac, Y_ThaoTac, 6, ContentTicketSelect2);
		switch (signal)
		{
		case 1: // Dat ve
		{
			if (ListTicketIsFull(listTicket))
			{
				Notification("Da het ve");
				break;
			}
			InputTicket(ticket_tmp);
			RemoveForm(0, 4, 27);
			int vitri = ConvertMSVtoNumber(ticket_tmp.seat, air.col);

			if (listTicket.DSV[vitri].statusTicket == 2)
			{ // ve huy
				Notification("Ve da huy. Khong the dat!");
				break;
			}

			if (CheckSeat(air, listTicket, ticket_tmp) == -1)
			{ // khong ton tai
				Notification("Vi tri nay khong ton tai");
				break;
			}
			else if (CheckSeat(air, listTicket, ticket_tmp) == 0)
			{ // da dat
				Notification("Vi tri nay da co nguoi dat");
				break;
			}
			else
			{ // ve trong
				if (CheckCMND(listTicket, ticket_tmp))
				{
					Notification("Ban da dat ve tren chuyen bay nay");
				}
				else
				{
					if (SearchPass(rootPass, ticket_tmp.idPas) == NULL)
					{
						pass_tmp.id = ticket_tmp.idPas;
						InputPass(rootPass, pass_tmp, true);
					}
					InsertListTicket(air, listTicket, ticket_tmp);
					Notification("Them thanh cong");
				}
			}
			ShowListTicketOnePage(listTicket, (CurPage - 1) * NumberPerPage);
			ShowCursor(false);
			break;
		}
		case 2: // Huy ve
		{
			if (ListTicketIsNull(listTicket))
			{
				Notification("Khong con ve de xoa");
				break;
			}
			// gotoxy(X_Add,Y_Add-1);
			InputTicket(ticket_tmp);
			RemoveForm(0, 4, 27);
			if (CheckSeat(air, listTicket, ticket_tmp) == -1)
			{
				Notification("Vi tri nay khong ton tai");
				break;
			}
			else if (CheckSeat(air, listTicket, ticket_tmp) == 1)
			{
				Notification("Vi tri nay chua duoc dat");
				break;
			}
			else
			{
				CancelTicket(air, listTicket, ticket_tmp);
				Notification("Huy ve thanh cong");
			}
			ShowListTicketOnePage(listTicket, (CurPage - 1) / NumberPerPage);
			break;
		}
		case 3: // Chuyen che do xem full ve va cac ve con trong
		{
			int signal = MenuSelect(X_ThaoTac + 16, Y_ThaoTac + 3, 2, ContentTicketEmpty);
			if (signal == 1)
			{
				emptyTicket = false;
				Clean(20, 3, 20+38, 3);
				// gotoxy(20, 3);
				// std::cout << "                                     ";
				gotoxy(20, 3);
				std::cout << "_DANH SACH VE_";
				ChangeTicketMenuManagerPage(listTicket, emptyTicket);
			}
			else
			{
				emptyTicket = true;
				// gotoxy(20, 3);
				// std::cout << "                                       ";
				Clean(20, 3, 20+40, 3);
				gotoxy(20, 3);
				std::cout << "_DANH SACH CAC VE CON TRONG_";
				ChangeTicketMenuManagerPage(listTicket, emptyTicket);
			}
		}
		case LEFT:
		case 4: // Trang truoc
		{
			if (CurPage == 1)
				break;
			CurPage--;
			ChangeTicketMenuManagerPage(listTicket, emptyTicket);
			break;
		}
		case RIGHT:
		case 5: // Trang sau
		{
			if (CurPage >= TotalPage)
				break;
			CurPage++;
			ChangeTicketMenuManagerPage(listTicket, emptyTicket);
			break;
		}
		default:
			return;
		}
	}
}

#endif