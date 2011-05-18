#include "clienthighlighting.h"
#include <QtCore>


ClientHighlighting::ClientHighlighting(QObject *parent) :
		QSyntaxHighlighter(parent)
{
}

ClientHighlighting::ClientHighlighting(QTextEdit *parent) :
		QSyntaxHighlighter(parent)
{

}

ClientHighlighting::ClientHighlighting(QTextDocument *parent) :
		QSyntaxHighlighter(parent)

{
}

void ClientHighlighting::highlightBlock(const QString &text)
{
	if(!diffs.isEmpty()){
		if(diffs.first().text != ""){
			int start1 = patches.first().start1;
			int firstDiffSize = diffs.first().text.size();

			for(int i=0; i<text.length(); i++){
				if(diffs.first().operation == 0 && start1 == 0){
					setFormat(0, firstDiffSize, Qt::darkGreen);
				}else if(text.mid(i, firstDiffSize), i == start1){
					setFormat((i + firstDiffSize), patches.first().length1 - patches.first().length2, Qt::darkGreen);
				}else if(diffs.at(1).operation == 1){
					setFormat(patches.first().start1 + firstDiffSize, patches.first().length2 - patches.first().length1, Qt::red);
					qDebug() << "like a mother fucking bitch?";
				}else if(diffs.at(0).operation == 1){
					setFormat(0, patches.first().length2 - patches.first().length1, Qt::red);
					qDebug() << "just like the biggest mother fucking bitch?";
				}
			}
		}
	}

}

void ClientHighlighting::setPatches(QList<Patch> patches)
{
	this->patches = patches;
	this->diffs = patches.first().diffs;
}

void ClientHighlighting::clearPatches()
{
	this->patches.clear();
	this->diffs.clear();
}





