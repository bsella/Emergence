#include "IoPlugin.h"
#include "Node.h"
#include "InputNode.h"
#include "OutputNode.h"
#include "ExportImageDialog.h"

void IoPlugin::updateUI(Ui::MainWindow* ui) const{
	QMenu* ioMenu = new QMenu("Input/Output",ui->menuInsert);
	ui->menuInsert->addAction(ioMenu->menuAction());
	QAction* xAction= new QAction(QIcon(":/x.png"),"X");
	QAction* yAction= new QAction(QIcon(":/y.png"),"Y");
	QAction* ratioAction= new QAction("Ratio");
	QAction* outAction= new QAction(QIcon(":/output.png"),"Output");

	Workspace* ws=(Workspace*)ui->workspace->scene();
	connect(xAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("x"));});
	connect(yAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("y"));});
	connect(ratioAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("ratio"));});
	connect(outAction,&QAction::triggered,ws,[=]{ws->addNode(Node::nodeMalloc("out"));});

	ioMenu->addAction(xAction);
	ioMenu->addAction(yAction);
	ioMenu->addAction(ratioAction);
	ioMenu->addAction(outAction);

	QAction* exportAction= new QAction("Export");
	exportAction->setShortcut(QKeySequence("Ctrl+E"));
	connect(exportAction,&QAction::triggered,ws,[=]{
		for(const auto& node: ws->selectedItems()){
			OutputNode* out = (OutputNode*)node;
			if(out->_type=="out" && *out)
				ExportImageDialog::exportBMP(out);
		}
	});
	ui->menuFile->insertAction(ui->actionOpen,exportAction);
}

void IoPlugin::init()const{
	Node::makeNodeMethods["x"] = &XNode::makeNode;
	Node::makeNodeMethods["y"] = &YNode::makeNode;
	Node::makeNodeMethods["ratio"]= &RatioNode::makeNode;
	Node::makeNodeMethods["out"]= &OutputNode::makeNode;

	NodeBox::addTool("x","X",QIcon(":/x.png"));
	NodeBox::addTool("y","Y",QIcon(":/y.png"));
	NodeBox::addTool("ratio","Width/Height");
	NodeBox::addTool("out","Output",QIcon(":/output.png"));
}
