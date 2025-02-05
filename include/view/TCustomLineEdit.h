#ifndef TCUSTOMLINEEDIT_H
#define TCUSTOMLINEEDIT_H

#include "ICorrectLine.h"

#include <QLineEdit>

class TCustomLineEdit: public QLineEdit
{
    Q_OBJECT

    ICorrectLine* _checker;
    void constructor();

public:
    TCustomLineEdit(ICorrectLine* validator, QWidget* parent = nullptr);
    TCustomLineEdit(ICorrectLine* validator, const QString &str, QWidget* parent = nullptr);
    ~TCustomLineEdit();

    bool getCorrect() const;
    void delete_Null();

private slots:
    void checkLineCorrect(const QString &text);

signals:
    void EnteredCorrectParams(bool);

}; //class TCustomLineEdit
//-------------------------------------------------------------------

#endif // TCUSTOMLINEEDIT_H
