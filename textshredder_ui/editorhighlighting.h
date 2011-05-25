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


private:
	QList<Patch> patches;
	QList<Diff> diffs;
	int editPosition;
	bool highlightingOn;




};

#endif // EDITORHIGHLIGHTING_H
