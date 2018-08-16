#include "NodeBox.h"

NodeTool::NodeTool(int id,const QString& text, const QString& iconPath)
	:nodeID(id),icon(iconPath){
	setMinimumHeight(30);
	setMaximumHeight(30);
	QLabel *lbl= new QLabel("<img src=\""+iconPath+"\">  "+text,this);
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
	mime->setData("type",QByteArray::number(nodeID));
	drag->setPixmap(QPixmap::fromImage(QImage(icon)));
	mime->setParent(drag);
	drag->exec();
	QWidget::mouseMoveEvent(event);
}

NodeBox::NodeBox(QWidget *parent):QToolBox(parent){
}
