#include "editorhighlighting.h"

#include <QtCore>


EditorHighLighting::EditorHighLighting(QObject *parent) :
		QSyntaxHighlighter(parent), editPosition(0), highlightingOn(true)
{
	HighlightingRule rule;

		 keywordFormat.setForeground(Qt::darkBlue);
		 keywordFormat.setFontWeight(QFont::Bold);
		 QStringList keywordPatterns;
		 keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
						 << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
						 << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
						 << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
						 << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
						 << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
						 << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
						 << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
						 << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
						 << "\\bvoid\\b" << "\\bvolatile\\b";
		 foreach (const QString &pattern, keywordPatterns) {
			 rule.pattern = QRegExp(pattern);
			 rule.format = keywordFormat;
			 highlightingRules.append(rule);
		 }
		 classFormat.setFontWeight(QFont::Bold);
			 classFormat.setForeground(Qt::darkMagenta);
			 rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
			 rule.format = classFormat;
			 highlightingRules.append(rule);

			 quotationFormat.setForeground(Qt::darkGreen);
			 rule.pattern = QRegExp("\".*\"");
			 rule.format = quotationFormat;
			 highlightingRules.append(rule);

			 functionFormat.setFontItalic(true);
			 functionFormat.setForeground(Qt::blue);
			 rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
			 rule.format = functionFormat;
			 highlightingRules.append(rule);

			 singleLineCommentFormat.setForeground(Qt::red);
				 rule.pattern = QRegExp("//[^\n]*");
				 rule.format = singleLineCommentFormat;
				 highlightingRules.append(rule);

				 multiLineCommentFormat.setForeground(Qt::red);

				 commentStartExpression = QRegExp("/\\*");
				 commentEndExpression = QRegExp("\\*/");
}

EditorHighLighting::EditorHighLighting(QTextEdit *parent) :
		QSyntaxHighlighter(parent), editPosition(0), highlightingOn(true)
{

	HighlightingRule rule;

		 keywordFormat.setForeground(Qt::darkBlue);
		 keywordFormat.setFontWeight(QFont::Bold);
		 QStringList keywordPatterns;
		 keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
						 << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
						 << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
						 << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
						 << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
						 << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
						 << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
						 << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
						 << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
						 << "\\bvoid\\b" << "\\bvolatile\\b";
		 foreach (const QString &pattern, keywordPatterns) {
			 rule.pattern = QRegExp(pattern);
			 rule.format = keywordFormat;
			 highlightingRules.append(rule);
		 }
		 classFormat.setFontWeight(QFont::Bold);
			 classFormat.setForeground(Qt::darkMagenta);
			 rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
			 rule.format = classFormat;
			 highlightingRules.append(rule);

			 quotationFormat.setForeground(Qt::darkGreen);
			 rule.pattern = QRegExp("\".*\"");
			 rule.format = quotationFormat;
			 highlightingRules.append(rule);

			 functionFormat.setFontItalic(true);
			 functionFormat.setForeground(Qt::blue);
			 rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
			 rule.format = functionFormat;
			 highlightingRules.append(rule);

			 singleLineCommentFormat.setForeground(Qt::red);
				 rule.pattern = QRegExp("//[^\n]*");
				 rule.format = singleLineCommentFormat;
				 highlightingRules.append(rule);

				 multiLineCommentFormat.setForeground(Qt::red);

				 commentStartExpression = QRegExp("/\\*");
				 commentEndExpression = QRegExp("\\*/");
}

EditorHighLighting::EditorHighLighting(QTextDocument *parent) :
		QSyntaxHighlighter(parent), editPosition(0), highlightingOn(true)

{
	HighlightingRule rule;

		 keywordFormat.setForeground(Qt::darkBlue);
		 keywordFormat.setFontWeight(QFont::Bold);
		 QStringList keywordPatterns;
		 keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
						 << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
						 << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
						 << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
						 << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
						 << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
						 << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
						 << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
						 << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
						 << "\\bvoid\\b" << "\\bvolatile\\b";
		 foreach (const QString &pattern, keywordPatterns) {
			 rule.pattern = QRegExp(pattern);
			 rule.format = keywordFormat;
			 highlightingRules.append(rule);
		 }
		 classFormat.setFontWeight(QFont::Bold);
			 classFormat.setForeground(Qt::darkMagenta);
			 rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
			 rule.format = classFormat;
			 highlightingRules.append(rule);

			 quotationFormat.setForeground(Qt::darkGreen);
			 rule.pattern = QRegExp("\".*\"");
			 rule.format = quotationFormat;
			 highlightingRules.append(rule);

			 functionFormat.setFontItalic(true);
			 functionFormat.setForeground(Qt::blue);
			 rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
			 rule.format = functionFormat;
			 highlightingRules.append(rule);

			 singleLineCommentFormat.setForeground(Qt::red);
				 rule.pattern = QRegExp("//[^\n]*");
				 rule.format = singleLineCommentFormat;
				 highlightingRules.append(rule);

				 multiLineCommentFormat.setForeground(Qt::red);

				 commentStartExpression = QRegExp("/\\*");
				 commentEndExpression = QRegExp("\\*/");
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

	foreach (const HighlightingRule &rule, highlightingRules) {
			 QRegExp expression(rule.pattern);
			 int index = expression.indexIn(text);
			 while (index >= 0) {
				 int length = expression.matchedLength();
				 setFormat(index, length, rule.format);
				 index = expression.indexIn(text, index + length);
			 }
		 }
	setCurrentBlockState(0);
	int startIndex = 0;
		if (previousBlockState() != 1)
			startIndex = commentStartExpression.indexIn(text);

	while (startIndex >= 0) {
			 int endIndex = commentEndExpression.indexIn(text, startIndex);
			 int commentLength;
			 if (endIndex == -1) {
				 setCurrentBlockState(1);
				 commentLength = text.length() - startIndex;
			 } else {
				 commentLength = endIndex - startIndex
								 + commentEndExpression.matchedLength();
			 }
			 setFormat(startIndex, commentLength, multiLineCommentFormat);
			 startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
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
