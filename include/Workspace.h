#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QGraphicsView>
#include <QDropEvent>
#include <QMimeData>

#define MAGIC_NUMBER 0xa1b2affd
#define SAVE_VERSION 0x00000003

class Workspace : public QGraphicsView{
	Q_OBJECT
public:
	Workspace(QWidget *parent=0);
private:
	constexpr static double scaleFactor=1.05;
	void dropEvent(QDropEvent*);
	void dragMoveEvent(QDragMoveEvent*);
	void dragEnterEvent(QDragEnterEvent*);
	void wheelEvent(QWheelEvent*);
signals:
	void dropped(QDropEvent*);
};

#endif // WORKSPACE_H
