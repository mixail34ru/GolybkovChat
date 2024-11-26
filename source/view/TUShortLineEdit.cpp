#include "TUShortLineEdit.h"

#include <QIntValidator>

TUShortLineEdit::TUShortLineEdit(QWidget* parent)
    : QLineEdit(parent), _is_correct(false)
{
    constructor();
}//------------------------------------------------------------------


TUShortLineEdit::TUShortLineEdit(const QString &contents, QWidget* parent)
    : QLineEdit(parent), _is_correct(false)
{
    constructor();
    this->setText(contents);
}//------------------------------------------------------------------


TUShortLineEdit::~TUShortLineEdit() {
}//------------------------------------------------------------------


void TUShortLineEdit::constructor() {
    this->setValidator(new QIntValidator(0, USHRT_MAX, this));
    connect(
        this, SIGNAL(textChanged(QString)),
        this, SLOT(checkLineCorrect(QString))
    );
}//------------------------------------------------------------------


bool TUShortLineEdit::isCorrect() const {
    return _is_correct;
}//------------------------------------------------------------------


void TUShortLineEdit::checkLineCorrect(const QString &text) {
    unsigned int num = text.toUInt();
    if (num >= 0 && num <= USHRT_MAX) {
        this->setStyleSheet("QLineEdit { color: black }");

        if (_is_correct != true) {
            _is_correct = true;
            emit EnteredCorrectParams(_is_correct);
        }
    }
    else {
        this->setStyleSheet("QLineEdit { color: red }");

        if (_is_correct != false) {
            _is_correct = false;
            emit EnteredCorrectParams(_is_correct);
        }
    }
}//------------------------------------------------------------------
