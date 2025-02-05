#ifndef TDOUBLEVALIDATOR_H
#define TDOUBLEVALIDATOR_H

#include "ICorrectLine.h"

class TDoubleValidator : public ICorrectLine
{
    Q_OBJECT
    Q_INTERFACES(ICorrectLine)

    bool _is_correct;
    QValidator* _validator;

public:
    explicit TDoubleValidator(QObject* parent = nullptr);
    virtual ~TDoubleValidator();

    virtual bool isCorrect() const override;
    virtual bool checkLineCorrect(const QString &text) override;
    virtual QValidator* getValidator() const override;
    virtual QString delete_Null(QString &text) override;

};//-------------------------------------------------------------------

#endif // TDOUBLEVALIDATOR_H
