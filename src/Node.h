#ifndef NODE_H
#define NODE_H

#include <QGraphicsObject>
#include <QPen>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QGraphicsScene>
#include <QMenu>

#include "data_t.h"
#include "signalManager.h"

class Node: public QGraphicsObject{
	Q_OBJECT
public:
	Node(const std::string& type, unsigned w=50, unsigned h=50, QColor c=Qt::white, uint n=0, bool spec=false);
	~Node();
	unsigned width, height;
	const std::string _type;
	virtual data_t eval();
	static Node* nodeMalloc(const QString&, void* arg=nullptr);
	QVector<Node*> iNodes;		//INPUT NODES
	static SignalManager sm;
	virtual operator bool()const;
	static std::map<const QString, Node*(*)(void*)> makeNodeMethods;
	static QList<const QString> knownTypes;
	friend std::ostream& operator<<(std::ostream& out, const Node&);
	friend std::ostream& operator<<(std::ostream& out, const QList<Node*>&);
	friend std::istream& operator>>(std::istream& in , QList<Node*>&);
private:
	friend class MainWindow;
	friend class Workspace;
	friend class DeleteNodeCommand;
	friend class ConnectNodeCommand;
	friend class DisconnectNodeCommand;
	friend class MoveNodeCommand;
	friend class Function;
	bool special;
	QPointF initialPos;
	static QPointF tmpPos;
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	virtual data_t kernel()const=0;
	bool isLooping(Node *n)const;
	void updateConstant();
	virtual void toBin(std::ostream&)const;
	virtual void fromBin(std::istream&,void*)const;
protected slots:
	void updateLines()const;
	void updateVal();
protected:
	struct Socket : public QGraphicsObject{
		Socket(unsigned i, double y, Node *parent);
		~Socket();
		QGraphicsLineItem line;
		unsigned rank;
		double iy;
		static Node *hover;
		Node *parent;
		bool visible=true;
		static const int headSize=8;
		QPen pen=QPen(Qt::black);
		void connectToNode(Node*n);
		void disconnectNode();
		QRectF boundingRect() const;
		void updateLine();
		Node* collidesWithNode()const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
		void hoverEnterEvent(QGraphicsSceneHoverEvent*);
		void hoverLeaveEvent(QGraphicsSceneHoverEvent*);
		void mouseMoveEvent(QGraphicsSceneMouseEvent*);
		void mousePressEvent(QGraphicsSceneMouseEvent*);
		void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
		void reset();
	};
	static const int socketSize=5;
	static uint widthByHeight;
	static ulong pixelID;
	ulong lastPixelID=0;
	data_t cache;		//value returned by node
	bool constant=false;		//value is constant
	QColor color;
	QMenu *menu=nullptr;
	QPen pen;
	uint nbArgs;
	QList<QPair<Node*,uint>> oConnections;
	QVector<Socket*> sockets;
	QAction* actionDelete;

	QRectF boundingRect()const;
	virtual void paint(QPainter* painter,
			const QStyleOptionGraphicsItem* option,
			QWidget* widget);
	virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
	void drawIcon(QPainter *painter, QString filename);
signals:
	void connected(Node::Socket* s,Node* n);
	void disconnected(Node::Socket* s);
	void moved();
};

#endif
