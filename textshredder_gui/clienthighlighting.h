#ifndef CLIENTHIGHLIGHTING_H
#define CLIENTHIGHLIGHTING_H

#include <QSyntaxHighlighter>
#include "../textshredder_diff_match_patch/diff_match_patch.h"

class ClientHighlighting : public QSyntaxHighlighter
{
public:
	ClientHighlighting(QObject *parent);
	ClientHighlighting(QTextDocument *parent);
	ClientHighlighting(QTextEdit *parent);

	using QSyntaxHighlighter::highlightBlock;
	void highlightBlock(const QString &text);

	void setPatches(QList<Patch> patches);
	void clearPatches();


private:
	QList<Patch> patches;
	QList<Diff> diffs;


};

#endif // CLIENTHIGHLIGHTING_H
