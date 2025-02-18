#ifndef TUSHORTLINEEDIT_H
#define TUSHORTLINEEDIT_H

#include <QLineEdit>
<<<<<<< HEAD
#include "ICorrectLine.h"
=======
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884

class TUShortLineEdit : public QLineEdit
{
    Q_OBJECT

    bool _is_correct;

    void constructor();
<<<<<<< HEAD
    ICorrectLine* _checker;
=======
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884

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
