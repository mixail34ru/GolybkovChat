#ifndef TUSHORTLINEEDIT_H
#define TUSHORTLINEEDIT_H

#include <QLineEdit>

class TUShortLineEdit : public QLineEdit
{
    Q_OBJECT

    bool _is_correct;

    void constructor();

public:
    TUShortLineEdit(QWidget* parent = nullptr);
    TUShortLineEdit(const QString &contents, QWidget* parent = nullptr);
    ~TUShortLineEdit();

    bool isCorrect() const;

private slots:
    void checkLineCorrect(const QString &text);

signals:
    void EnteredCorrectParams(bool);

}; //class TUShortLineEdit
//-------------------------------------------------------------------

#endif // TUSHORTLINEEDIT_H
