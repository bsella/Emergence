#include "NodeBox.h"

#include<QLabel>
#include<QLayout>
#include<QPushButton>
#include<QSpacerItem>
#include<QAction>
#include<QDrag>
#include<QMimeData>

Workspace* NodeTool::workspace;
QPointF NodeTool::point;
NodeTool::NodeTool(const std::string& id,const QString& text, const QIcon& icon)
	:id(id),icon(icon){
	setMinimumHeight(30);
	setMaximumHeight(30);
	QLabel *lblIcon= new QLabel;
	lblIcon->setPixmap(icon.pixmap(24,24));
	QLabel *lbl= new QLabel(text);
	QHBoxLayout* hbl= new QHBoxLayout(this);
	hbl->setSpacing(1);
	hbl->setMargin(0);
	hbl->addWidget(lblIcon);
	hbl->addWidget(lbl);
	hbl->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding));
	lbl->setAttribute(Qt::WA_TransparentForMouseEvents);
	setFrameShape(StyledPanel);
	setFrameShadow(Raised);
//	setAutoFillBackground(true);
//	setBackgroundRole(QPalette::Base);
}

void NodeTool::mouseMoveEvent(QMouseEvent *event){
	QDrag* drag= new QDrag(this);
	drag->setPixmap(icon.pixmap(24,24));
	drag->setMimeData(new QMimeData);
	workspace=nullptr;
	drag->exec();
	if(workspace)
		workspace->addNode(Node::nodeMalloc(id),point);
	QWidget::mouseMoveEvent(event);
}

std::vector<NodeBox*> NodeBox::nodeboxes;
std::vector<nodeToolData> NodeBox::tools;
NodeBox::NodeBox(QWidget *parent):QToolBox(parent){
	for(const auto& tool:tools)
		addTool(tool);
	nodeboxes.push_back(this);
}
void NodeBox::addTool(const nodeToolData &tool){
	int i=0;
	while(itemText(i)!=tool.category && itemText(i)!="") i++;
	QVBoxLayout *vbl;
	if(i==count()){ //The Widget-container(page) was not found
		QWidget* page = new QWidget;
		vbl= new QVBoxLayout(page);
		vbl->setSpacing(1);
		vbl->setMargin(0);
		vbl->addWidget(new NodeTool(tool.id,tool.text,tool.icon));
		vbl->addItem(new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::Expanding));
		addItem(page,tool.category);
	}else{
		vbl = (QVBoxLayout*)widget(i)->layout();
		vbl->insertWidget(vbl->count()-1,new NodeTool(tool.id,tool.text,tool.icon));
	}
}
void NodeBox::addTool(const std::string &id, const QString &text, const QString &category){
	addTool(id,text,QIcon(":/no_icon.png"),category);
}
void NodeBox::addTool(const std::string& id, const QString&text,
					  const QIcon& icon, const QString &category){
	tools.push_back({id,text,icon,category});
	for(auto nb:nodeboxes)
		nb->addTool(tools.back());
}
