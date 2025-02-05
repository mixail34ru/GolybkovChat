#include "TDoubleValidator.h"

TDoubleValidator::TDoubleValidator(QObject* parent) : ICorrectLine(parent)
{
    _validator = new QDoubleValidator(this);
    _is_correct = false;
}

TDoubleValidator::~TDoubleValidator()
{

}

QValidator* TDoubleValidator::getValidator() const
{
    return _validator;
}

bool TDoubleValidator::isCorrect() const
{
    return _is_correct;
}

bool TDoubleValidator::checkLineCorrect(const QString &text)
{
    if (text == "")
        return _is_correct = false;

    QString str = text;
    str.replace(QChar(',') , QChar('.'));

    double num = str.toDouble();
    if (!std::isinf(num))
        _is_correct = true;
    else
        _is_correct = false;

    return _is_correct;
}

QString TDoubleValidator::delete_Null(QString &text)
{
    text.replace(QChar(',') , QChar('.'));
    double num = text.toDouble();
    text = QString::number(num);
    text.replace(QChar('.') , QChar(','));

    return text;
}//------------------------------------------------------------------
