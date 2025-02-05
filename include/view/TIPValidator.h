#ifndef TIPVALIDATOR_H
#define TIPVALIDATOR_H

#include "ICorrectLine.h"

#include <QRegularExpressionValidator>

class TIPValidator : public ICorrectLine
{
    Q_OBJECT
    Q_INTERFACES(ICorrectLine)

    bool _is_correct;
    QValidator* _validator;

public:
    explicit TIPValidator(QObject* parent = nullptr);
    virtual ~TIPValidator();

    virtual bool isCorrect() const override;
    virtual bool checkLineCorrect(const QString &text) override;
    virtual QValidator* getValidator() const override;
    virtual QString delete_Null(QString &text) override;

};//-------------------------------------------------------------------

#endif // TIPVALIDATOR_H
