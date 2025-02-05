#include "TIntValidator.h"

TIntValidator::TIntValidator(QObject* parent) : ICorrectLine(parent)
{
    _validator = new QIntValidator(this);
    _is_correct = false;
    setRange(INT_MIN, INT_MAX);
}

TIntValidator::TIntValidator(int index, QObject* parent) : ICorrectLine(parent)
{
    _is_correct = false;
    if (index == 0) // таймер
    {
        _validator = new QIntValidator(1, INT_MAX, this);
        setRange(1, INT_MAX);
    }
    else if (index == 1) // матрица
    {
        _validator = new QIntValidator(this);
        setRange(INT32_MIN, INT32_MAX);
    }
    else if (index == 2) // маска
    {
        _validator = new QIntValidator(this);
        setRange(INT_MIN, INT_MAX);
    }
}

TIntValidator::~TIntValidator()
{

}

QValidator* TIntValidator::getValidator() const
{
    return _validator;
}

bool TIntValidator::isCorrect() const
{
    return _is_correct;
}

bool TIntValidator::checkLineCorrect(const QString &text)
{
    if (text == "")
        return _is_correct = false;
    long long num = text.toLongLong();
    if (num >=_range.min && num <= _range.max)
        _is_correct = true;
    else
        _is_correct = false;

    return _is_correct;
}

void  TIntValidator::setRange(int min, int max)
{
    _range.min = min;
    _range.max = max;
}

QString TIntValidator::delete_Null(QString &text)
{
    long long num = text.toLongLong();
    text = QString::number(num);
    return text;
}//------------------------------------------------------------------
