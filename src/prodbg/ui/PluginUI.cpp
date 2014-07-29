#include "PluginUI.h"
#include <PDUI.h>
#include <QListWidget>
#include <QMdiSubWindow>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace prodbg
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PrivateData
{
	QWidget* window;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static PDUIListView listview_create(void* privateData, const char* name, int id)
{
	(void)name;
	(void)id;
	PrivateData* data = (PrivateData*)privateData;
	QListWidget* listWidget = new QListWidget(data->window);
	return (PDUIListView)listWidget; 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int listview_clear(void*, PDUIListView handle)
{
	QListWidget* listWidget = (QListWidget*)handle;
	listWidget->clear();
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int listview_item_add(void*, PDUIListView handle, const char* item)
{
	QListWidget* listWidget = (QListWidget*)handle;
    QListWidgetItem* newItem = new QListWidgetItem;
    newItem->setText(QString(QLatin1String(item)));
    listWidget->insertItem(0, newItem);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int listview_item_remove(void*, PDUIListView handle, int index)
{
	QListWidget* listWidget = (QListWidget*)handle;
	listWidget->removeItemWidget(listWidget->itemAt(0, index));
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PluginUI_init(QWidget* parent, PDUI* uiInstance)
{
	PrivateData* privData = new PrivateData;
	privData->window = new QMdiSubWindow(parent);

	memset(uiInstance, 0, sizeof(PDUI));

	uiInstance->listview_create = listview_create;
	uiInstance->listview_clear = listview_clear;
	uiInstance->listview_item_add = listview_item_add;
	uiInstance->listview_item_remove = listview_item_remove;
	uiInstance->listview_item_text_get = 0;
	uiInstance->privateData = privData;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

