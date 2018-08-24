#include "PluginManager.h"

#include <QMessageBox>
#include <QDir>
#include <QPluginLoader>

PluginManager::PluginManager(Ui::MainWindow *mw):ui(mw){}

bool PluginManager::loadPlugins(){
	QDir dir(qApp->applicationDirPath());
	dir.cd("lib");
	bool success=false;
	for(const auto& fileName: dir.entryList(QDir::Files)){
		QPluginLoader pluginLoader(dir.absoluteFilePath(dir.absoluteFilePath(fileName)));
		if (auto plugin = pluginLoader.instance()){
			EmergenceInterface* interface= qobject_cast<EmergenceInterface *>(plugin);
			if (interface){
				interface->init();
				interface->updateUI(ui);
				success= true;
				if(interface->redefineSaveLoad())
					plugins.push_back(interface);
			}
		}
	}
	return success;
}

void PluginManager::save(std::ostream &out)const{
	std::vector<std::string> usedPlugins;
	Workspace* ws = (Workspace*)ui->workspace->scene();
	for(const auto& node: ws->nodes())
		if(std::find(usedPlugins.cbegin(),usedPlugins.cend(),node->_type)==usedPlugins.cend())
			usedPlugins.push_back(node->_type);
	out << usedPlugins.size() << '\n';
	for(const auto& x: usedPlugins)
		out << x << '\n';
	for(const auto& plugin: plugins)
		plugin->save(out);
}
void PluginManager::load(std::istream &in)const{
	int nbPlugins;
	in>> nbPlugins;
	std::vector<std::string> known;
	known.reserve(Node::makeNodeMethods.size());
	for(const auto& keyValue : Node::makeNodeMethods)
		known.push_back(keyValue.first);
	std::string tmp;
	for(int i=0; i<nbPlugins;i++){
		in >> tmp;
		if(std::find(known.cbegin(),known.cend(),tmp)==known.cend()){
			const std::string message="A plugin containing the implementation of the \""+tmp+"\" node is missing.";
			QMessageBox::warning(0,"Missing Plugin",QString::fromStdString(message));
			return;
		}
	}
	for(const auto& plugin: plugins)
		plugin->load(in);
}
