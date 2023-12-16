// CMyTreeView.cpp: файл реализации
//

#include "pch.h"
#include "demo.h"
#include "demoDoc.h"
#include "CMyTreeView.h"
#include "demoView.h"
#include "CMyListView.h"

// CMyTreeView

IMPLEMENT_DYNCREATE(CMyTreeView, CTreeView)

CMyTreeView::CMyTreeView()
{

}

CMyTreeView::~CMyTreeView()
{
}

BEGIN_MESSAGE_MAP(CMyTreeView, CTreeView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// Диагностика CMyTreeView

#ifdef _DEBUG
void CMyTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// Обработчики сообщений CMyTreeView


int CMyTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style |= TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_SHOWSELALWAYS | TVS_CHECKBOXES;

	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания

	return 0;
}

void CMyTreeView::FillTree()
{

	CTreeCtrl& tree = GetTreeCtrl();
	tree.DeleteAllItems();

	m_hSpares = tree.InsertItem(L"Запчасти", -1, -1, NULL, TVI_FIRST);
	m_hOrders = tree.InsertItem(L"Заказы", -1, -1, NULL, TVI_FIRST);
	m_hClients = tree.InsertItem(L"Клиенты", -1, -1, NULL, TVI_FIRST);

	tree.SetCheck(m_hSpares, m_pDoc->spares);
	tree.SetCheck(m_hOrders, m_pDoc->orders);
	tree.SetCheck(m_hClients, m_pDoc->clients);

	tree.Expand(m_hSpares, TVE_EXPAND);
	tree.Expand(m_hOrders, TVE_EXPAND);
	tree.Expand(m_hClients, TVE_EXPAND);

}

void CMyTreeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
		// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CTreeView::OnLButtonDown(nFlags, point);

	CTreeCtrl& tree = GetTreeCtrl();

	CRect rc;

	tree.GetItemRect(m_hSpares, &rc, false);
	if (rc.PtInRect(point)) {
		tree.SelectItem(m_hSpares);
		m_pList->DisplayTables("SELECT * FROM spares");
		m_pDoc->tableName = "spares";
	}

	tree.GetItemRect(m_hOrders, &rc, false);
	if (rc.PtInRect(point)) {
		tree.SelectItem(m_hOrders);
		m_pList->DisplayTables("SELECT * FROM orders");
		m_pDoc->tableName = "orders";
	}

	tree.GetItemRect(m_hClients, &rc, false);
	if (rc.PtInRect(point)) {
		tree.SelectItem(m_hClients);
		m_pList->DisplayTables("SELECT * FROM clients");
		m_pDoc->tableName = "clients";
	}

	if (tree.GetSelectedItem() == m_hSpares)
	{
		tree.SetCheck(m_hClients, false);
		tree.SetCheck(m_hOrders, false);
	}
	else
	{
		tree.SetCheck(m_hSpares, false);
	}

	if (tree.GetSelectedItem() == m_hClients)
	{
		tree.SetCheck(m_hSpares, false);
		tree.SetCheck(m_hOrders, false);
	}
	else
	{
		tree.SetCheck(m_hClients, false);
	}

	if (tree.GetSelectedItem() == m_hOrders)
	{
		tree.SetCheck(m_hClients, false);
		tree.SetCheck(m_hSpares, false);
	}
	else
	{
		tree.SetCheck(m_hOrders, false);
	}

	m_pDoc->spares = tree.GetCheck(m_hSpares);
	m_pDoc->orders = tree.GetCheck(m_hOrders);
	m_pDoc->clients = tree.GetCheck(m_hClients);

}
