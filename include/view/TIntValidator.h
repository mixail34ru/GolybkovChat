#ifndef TINTVALIDATOR_H
#define TINTVALIDATOR_H

#include "ICorrectLine.h"

#include <QIntValidator>
#include <QRegularExpressionValidator>

class TIntValidator : public ICorrectLine
{
    Q_OBJECT
    Q_INTERFACES(ICorrectLine)

    bool _is_correct;
    QValidator* _validator;

    struct Range{
        int min;
        int max;
    };
    Range _range;

public:
    explicit TIntValidator(QObject* parent = nullptr);
    TIntValidator(int num, QObject* parent = nullptr);
    virtual ~TIntValidator();

    virtual bool isCorrect() const override;
    virtual bool checkLineCorrect(const QString &text) override;
    virtual QValidator* getValidator() const override;
    virtual QString delete_Null(QString &text) override;
    void setValidators(const QString &text);

    void setRange(int min, int max);
};

#endif // TINTVALIDATOR_H
