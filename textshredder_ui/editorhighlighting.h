#ifndef EDITORHIGHLIGHTING_H
#define EDITORHIGHLIGHTING_H

#include <QSyntaxHighlighter>
#include "../textshredder_core/libraries/diff_match_patch/diff_match_patch.h"

class EditorHighLighting : public QSyntaxHighlighter
{
public:
	EditorHighLighting(QObject *parent);
	EditorHighLighting(QTextDocument *parent);
	EditorHighLighting(QTextEdit *parent);

	using QSyntaxHighlighter::highlightBlock;
	void highlightBlock(const QString &text);

	void setPatches(QList<Patch> patches);
	void clearPatches();
	void setHighlighting(bool HighLightingOn);

private:
	QList<Patch> patches;
	QList<Diff> diffs;
	int editPosition;
	bool highlightingOn;

	struct HighlightingRule
		 {
			 QRegExp pattern;
			 QTextCharFormat format;
		 };
		 QVector<HighlightingRule> highlightingRules;

		 QRegExp commentStartExpression;
		 QRegExp commentEndExpression;

		 QTextCharFormat keywordFormat;
		 QTextCharFormat classFormat;
		 QTextCharFormat singleLineCommentFormat;
		 QTextCharFormat multiLineCommentFormat;
		 QTextCharFormat quotationFormat;
		 QTextCharFormat functionFormat;



};

#endif // EDITORHIGHLIGHTING_H
