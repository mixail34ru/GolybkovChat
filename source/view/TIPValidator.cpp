#include "TIPValidator.h"

QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
QRegularExpression ip_regexp("^" + ipRange + "\\." + ipRange + "\\." + ipRange + "\\." + ipRange + "$");

TIPValidator::TIPValidator(QObject *parent) : ICorrectLine(parent)
{
    _validator = new QRegularExpressionValidator(ip_regexp, this);
    _is_correct = false;
}

TIPValidator::~TIPValidator()
{

}

QValidator* TIPValidator::getValidator() const
{
    return _validator;
}

bool TIPValidator::isCorrect() const
{
    return _is_correct;
}

bool TIPValidator::checkLineCorrect(const QString &text)
{
    QRegularExpressionMatch match = ip_regexp.match(text);
    if (match.hasMatch()) {
        _is_correct = true;
    }
    else
       _is_correct = false;

    return _is_correct;
}

QString TIPValidator::delete_Null(QString &text)
{
    return text;
}//------------------------------------------------------------------
