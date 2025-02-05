#ifndef ICORRECTLINE_H
#define ICORRECTLINE_H

#include <QObject>
#include <QString>
#include <QValidator>

 class ICorrectLine : public QObject
{
    Q_OBJECT
public:
    using QObject::QObject;
    virtual ~ICorrectLine() {};

    virtual bool isCorrect() const = 0;
    virtual bool checkLineCorrect(const QString &text) = 0;
    virtual QValidator* getValidator() const = 0;
    virtual QString delete_Null(QString &text) = 0;

}; //class ICorrectLine
Q_DECLARE_INTERFACE(ICorrectLine, "Interface")
//-------------------------------------------------------------------

#endif // ICORRECTLINE_H
