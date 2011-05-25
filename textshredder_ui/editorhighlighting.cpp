#include "editorhighlighting.h"

#include <QtCore>


EditorHighLighting::EditorHighLighting(QObject *parent) :
		QSyntaxHighlighter(parent), editPosition(0), highlightingOn(true)
{
}

EditorHighLighting::EditorHighLighting(QTextEdit *parent) :
		QSyntaxHighlighter(parent), editPosition(0), highlightingOn(true)
{

}

EditorHighLighting::EditorHighLighting(QTextDocument *parent) :
		QSyntaxHighlighter(parent), editPosition(0), highlightingOn(true)

{
}

void EditorHighLighting::highlightBlock(const QString &text)
{
	if(!patches.isEmpty() && highlightingOn == true){

		int prevDiffSize =0;

		for(int i=0; i < diffs.count(); i++){
			if(diffs.at(i).operation == 0){
				setFormat((patches.first().start1 + prevDiffSize -editPosition), diffs.at(i).text.size(), Qt::darkGreen);
				prevDiffSize += diffs.at(i).text.size();

			}else if(diffs.at(i).operation == 1){
				setFormat(patches.first().start1 + prevDiffSize - editPosition, diffs.at(i).text.size(), Qt::red);
				prevDiffSize -= diffs.at(i).text.size();
			}else{
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
