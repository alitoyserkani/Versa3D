#ifndef SCRIPTEDITOR_H
#define SCRIPTEDITOR_H


#include <QPlainTextEdit>
#include <QObject>
//#include <QTextCursor>

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE

class LineNumberArea;

//![codeeditordefinition]

class ScriptEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    ScriptEditor(QWidget *parent = 0);


    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *lineNumberArea;
};

//![codeeditordefinition]
//![extraarea]

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(ScriptEditor *editor) : QWidget(editor) {
        scriptEditor = editor;
    }

    QSize sizeHint() const override {
        return QSize(scriptEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        scriptEditor->lineNumberAreaPaintEvent(event);
    }

private:
    ScriptEditor *scriptEditor;
};

#endif // SCRIPTEDITOR_H
