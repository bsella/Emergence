#include "NodeBox.h"

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
	QMimeData* mime = new QMimeData;
	drag->setMimeData(mime);
	mime->setText("nodeTool");
	mime->setData("type",QByteArray(id.c_str()));
	drag->setPixmap(icon.pixmap(24,24));
	mime->setParent(drag);
	drag->exec();
	QWidget::mouseMoveEvent(event);
}

NodeBox::NodeBox(QWidget *parent):QToolBox(parent){}
void NodeBox::addTool(const std::string &id, const QString &text, const QString &category){
	addTool(id,text,QIcon(":/no_icon.png"),category);
}
void NodeBox::addTool(const std::string& id, const QString&text,
					  const QIcon& icon, const QString &category){
	int i=0;
	while(itemText(i)!=category && itemText(i)!="") i++;
	QVBoxLayout *vbl;
	if(i==count()){ //The Widget-container(page) was not found
		QWidget* page = new QWidget;
		vbl= new QVBoxLayout(page);
		vbl->setSpacing(1);
		vbl->setMargin(0);
		vbl->addWidget(new NodeTool(id,text,icon));
		vbl->addItem(new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::Expanding));
		addItem(page,category);
	}else{
		vbl = (QVBoxLayout*)widget(i)->layout();
		vbl->insertWidget(vbl->count()-1,new NodeTool(id,text,icon));
	}
}
