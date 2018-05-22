#ifndef NODEBOX_H
#define NODEBOX_H

#include<QToolBox>
#include<QLabel>
#include<QLayout>
#include<QPushButton>
#include<QSpacerItem>
#include<QAction>
#include<QDrag>
#include<QMimeData>

#include"include/nodes/Node.h"

class NodeTool : public QFrame{
public:
	NodeTool(int id,const QString &text="", const QString &iconPath=":/icons/no_icon.png");
private:
	int nodeID;
	QString icon;
	void mouseMoveEvent(QMouseEvent *event);
};

class NodeBox : public QToolBox{
public:
	NodeBox(QWidget* parent=0);
	NodeTool *x, *y, *ratio, *output;
};

#endif // NODEBOX_H
