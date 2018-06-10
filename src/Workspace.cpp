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
