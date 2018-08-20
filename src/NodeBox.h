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

class NodeTool : public QFrame{
public:
	NodeTool(const std::string& id,
			 const QString &text,
			 const QIcon&icon);
private:
	std::string id;
	QIcon icon;
	void mouseMoveEvent(QMouseEvent *event);
};

class NodeBox : public QToolBox{
public:
	NodeBox(QWidget* parent=0);
	void addTool(const std::string &id,
				 const QString &text,
				 const QIcon&icon=QIcon(":/no_icon.png"),
				 const QString &category="Miscellaneous");
	void addTool(const std::string &id,
				 const QString &text,
				 const QString &category);
};

#endif // NODEBOX_H
