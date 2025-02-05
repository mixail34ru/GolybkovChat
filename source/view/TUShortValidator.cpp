#include "TUShortValidator.h"

TUShortValidator::TUShortValidator(QObject* parent) : ICorrectLine(parent)
{
    _validator = new QIntValidator(0, USHRT_MAX, this);
    _is_correct = false;
    setRange(0, USHRT_MAX);
}

TUShortValidator::TUShortValidator(int min, int max, QObject* parent)
    : ICorrectLine(parent)
{
    _validator = new QIntValidator(0, USHRT_MAX, this);
    _is_correct = false;
    setRange(min, max);
}

TUShortValidator::~TUShortValidator()
{

}

QValidator* TUShortValidator::getValidator() const
{
    return _validator;
}

bool TUShortValidator::isCorrect() const
{
    return _is_correct;
}

bool TUShortValidator::checkLineCorrect(const QString &text)
{
    if (text == "")
        return _is_correct = false;

    unsigned int num = text.toUInt();
    if (num >= _range.min && num <= _range.max) {
        if (_is_correct != true) {
            _is_correct = true;
        }
    }
    else {
        if (_is_correct != false) {
            _is_correct = false;
        }
    }

    return _is_correct;
}

void  TUShortValidator::setRange(int min, int max)
{
    _range.min = min;
    _range.max = max;
}

QString TUShortValidator::delete_Null(QString &text)
{
    unsigned int num = text.toUInt();
    text = QString::number(num);
    return text;
}//------------------------------------------------------------------
