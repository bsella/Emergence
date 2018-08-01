#ifndef FUNCTIONMANAGER_H
#define FUNCTIONMANAGER_H

#include <QDialog>
#include <QInputDialog>
#include <QListWidgetItem>
#include <QDialogButtonBox>
#include <QUndoCommand>
#include "Function.h"
#include "nodes/FunctionNode.h"

namespace Ui {
class FunctionManager;
}

class FunctionManager : public QDialog{
	Q_OBJECT
public:
	explicit FunctionManager(QWidget *parent = 0);
	~FunctionManager();
	static Function* getFunction(FunctionNode* node=0);
	static FunctionManager* singleton;
	static Function* functionAt(int);
	static int indexOf(Function*);
	static int count();
	void clear();
	friend std::istream& operator>>(std::istream&, FunctionManager&);
private:
	static bool userIntented;
	Ui::FunctionManager *ui;
	QAction del,copy,cut,paste,undo,redo,select_all;
	QUndoStack undoStack;
	void setFunction(QListWidgetItem *,QListWidgetItem*);
	friend class ChangeNbArgsCommand;
	friend class AddFunctionCommand;
	friend class RemoveFunctionCommand;
	friend class RenameFunctionCommand;
private slots:
	void accept();
	void reject();
	void renameFunction(QListWidgetItem*);
	void on_spinBox_valueChanged(int arg1);
	void on_addFunctionButton_clicked();
	void on_removeFunctionButton_clicked();
};

class ChangeNbArgsCommand:public QUndoCommand{
public:
	ChangeNbArgsCommand(Function*, int, int, QUndoCommand* parent=0);
private:
	int _from;
	int _to;
	Function* func;
	void undo();
	void redo();
};

class AddFunctionCommand:public QUndoCommand{
public:
	explicit AddFunctionCommand(QUndoCommand*parent=0);
private:
	Function* func;
	void undo();
	void redo();
};
class RemoveFunctionCommand:public QUndoCommand{
public:
	explicit RemoveFunctionCommand(QUndoCommand*parent=0);
private:
	uint _rank;
	Function* func;
	void undo();
	void redo();
};
class RenameFunctionCommand:public QUndoCommand{
public:
	RenameFunctionCommand(Function*,const QString& to,
						  QUndoCommand* parent=0);
private:
	Function* func;
	QString _from;
	QString _to;
	void undo();
	void redo();
};

#endif // FUNCTIONMANAGER_H
