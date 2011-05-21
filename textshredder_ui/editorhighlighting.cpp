#include "editorhighlighting.h"

#include <QtCore>


EditorHighLighting::EditorHighLighting(QObject *parent) :
		QSyntaxHighlighter(parent), editPosition(0)
{
}

EditorHighLighting::EditorHighLighting(QTextEdit *parent) :
		QSyntaxHighlighter(parent), editPosition(0)
{

}

EditorHighLighting::EditorHighLighting(QTextDocument *parent) :
		QSyntaxHighlighter(parent), editPosition(0)

{
}

void EditorHighLighting::highlightBlock(const QString &text)
{

	if(!diffs.isEmpty()){
		int start1 = patches.first().start1;
		int prevDiffSize = diffs.first().text.size();
		qDebug() << "prevDiffSize " << prevDiffSize;
		qDebug() << "diffs first text " << diffs.first().text;
		if(diffs.first().text != ""){
			if(diffs.first().operation == 0 && start1 == 0){
				setFormat(0, prevDiffSize, Qt::darkGreen);
			}
			else if(diffs.at(0).operation == 1){
				setFormat(0, diffs.at(0).text.size(), Qt::red);
			}
			for(int i=1; i < diffs.count(); i++){
				if(diffs.at(i).operation == 0){
					qDebug() << "groen";
					setFormat((patches.first().start1 + prevDiffSize -editPosition), diffs.at(i).text.size(), Qt::darkGreen);
				}else if(diffs.at(i).operation == 1){
					setFormat(patches.first().start1 + prevDiffSize - editPosition, diffs.at(i).text.size(), Qt::red);
				}
				prevDiffSize += diffs.at(i).text.size();
			}
		}
		editPosition += text.size() +1;
	}

}

void EditorHighLighting::setPatches(QList<Patch> patches)
{
	editPosition = 0;
	this->patches = patches;
	this->diffs = patches.first().diffs;
}

void EditorHighLighting::clearPatches()
{
	this->patches.clear();
	this->diffs.clear();
}
