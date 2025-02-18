#include "TUShortLineEdit.h"
<<<<<<< HEAD
#include "TUShortValidator.h"
=======
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884

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
<<<<<<< HEAD
    //_checker = new TUShortValidator(this);
    /*_is_correct = _checker->checkLineCorrect(text);

    if (_is_correct == true)
    {
        this->setStyleSheet("QLineEdit { color: black }");
        emit EnteredCorrectParams(_is_correct);
    }
    else
    {
        this->setStyleSheet("QLineEdit { color: red }");
        emit EnteredCorrectParams(_is_correct);
    }

    _is_correct = _checker->checkLineCorrect(text);

    if (_checker->checkLineCorrect(text) == true)
    {
        this->setStyleSheet("QLineEdit { color: black }");
        emit EnteredCorrectParams(_checker->isCorrect());
    }
    else
    {
        this->setStyleSheet("QLineEdit { color: red }");
        emit EnteredCorrectParams(_is_correct);
    }
*/


=======
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
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
