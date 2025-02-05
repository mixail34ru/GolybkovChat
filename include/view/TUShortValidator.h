#ifndef TUSHORTVALIDATOR_H
#define TUSHORTVALIDATOR_H

#include "ICorrectLine.h"
#include <QIntValidator>

class TUShortValidator : public ICorrectLine
{
    Q_OBJECT
    Q_INTERFACES(ICorrectLine)

    bool _is_correct;
    QValidator* _validator;

    struct Range{
        int min = 1;
        int max = 300;
    };
    Range _range;

public:
    explicit TUShortValidator(QObject* parent = nullptr);
    TUShortValidator(int min = 1, int max = 300, QObject* parent = nullptr);
    virtual ~TUShortValidator();

    virtual bool isCorrect() const override;
    virtual bool checkLineCorrect(const QString &text) override;
    virtual QValidator* getValidator() const override;
    virtual QString delete_Null(QString &text) override;

    void setRange(int min, int max);

};
//-------------------------------------------------------------------

#endif // TUSHORTVALIDATOR_H
