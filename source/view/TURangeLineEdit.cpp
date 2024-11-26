#include "TURangeLineEdit.h"

#include <QIntValidator>

TURangeLineEdit::TURangeLineEdit(QWidget* parent)
    : QLineEdit(parent), _is_correct(false)
{
    constructor();
}//------------------------------------------------------------------


TURangeLineEdit::TURangeLineEdit(const QString &contents, Range range, QWidget* parent)
    : QLineEdit(parent), _is_correct(false)
{
    constructor();
    setRange(Range());
    this->setText(contents);
}//------------------------------------------------------------------

TURangeLineEdit::TURangeLineEdit(const QString &contents, int min, int max, QWidget* parent)
    : QLineEdit(parent), _is_correct(false)
{
    constructor();
    setRange(min, max);
    this->setText(contents);
}//------------------------------------------------------------------

TURangeLineEdit::~TURangeLineEdit() {
}//------------------------------------------------------------------


void TURangeLineEdit::constructor() {
    this->setValidator(new QIntValidator(0, USHRT_MAX, this));
    connect(
        this, SIGNAL(textChanged(QString)),
        this, SLOT(checkLineCorrect(QString))
        );
}//------------------------------------------------------------------


bool TURangeLineEdit::isCorrect() const {
    return _is_correct;
}//------------------------------------------------------------------


void  TURangeLineEdit::setRange(Range range)
{
    _range = range;
}//------------------------------------------------------------------

void  TURangeLineEdit::setRange(int min, int max)
{
    _range.min = min;
    _range.max = max;
}//------------------------------------------------------------------


void TURangeLineEdit::checkLineCorrect(const QString &text)
{
    unsigned int num = text.toUInt();
    if (num >= _range.min && num <= _range.max) {
        this->setStyleSheet("QLineEdit { color: black }");

        if (_is_correct != true) {
            _is_correct = true;
            emit EnteredCorrectParams(_is_correct);
        }
        //emit EnteredCorrectParams(_is_correct);
    }
    else {
        this->setStyleSheet("QLineEdit { color: red }");

        if (_is_correct != false) {
            _is_correct = false;
            emit EnteredCorrectParams(_is_correct);
        }
    }
}

TURangeLineEdit::Range TURangeLineEdit::range()
{
    return _range;
}
//------------------------------------------------------------------
