#include "include/Workspace.h"

Workspace::Workspace(QWidget *parent):QGraphicsView(parent){
	setAcceptDrops(true);
	setDragMode(DragMode::RubberBandDrag);
}

void Workspace::dragEnterEvent(QDragEnterEvent *event){
	QGraphicsView::dragEnterEvent(event);
	event->setAccepted(event->mimeData()->text()=="nodeTool");
}

void Workspace::dropEvent(QDropEvent *event){
	emit dropped(event);
}

void Workspace::dragMoveEvent(QDragMoveEvent*){}

void Workspace::wheelEvent(QWheelEvent *event){
	if(event->delta()>0) scale(scaleFactor,scaleFactor);
	else scale(1/scaleFactor,1/scaleFactor);
}
