#include "TCustomLineEdit.h"

TCustomLineEdit::TCustomLineEdit(ICorrectLine* validator, QWidget* parent)
    : QLineEdit(parent)
{
    _checker = validator;
    this->setValidator(validator->getValidator());
    constructor();
}

TCustomLineEdit::TCustomLineEdit(ICorrectLine* validator, const QString &str, QWidget* parent)
    : QLineEdit(parent)
{
    _checker = validator;

    this->setValidator(validator->getValidator());
    constructor();
    this->setText(str);
}

TCustomLineEdit::~TCustomLineEdit()
{
}

void TCustomLineEdit::constructor() {
    connect(
        this, SIGNAL(textChanged(QString)),
        this, SLOT(checkLineCorrect(QString))
        );
}

void TCustomLineEdit::checkLineCorrect(const QString &text) {
    if (_checker->checkLineCorrect(text) == true)
    {
        this->setStyleSheet("QLineEdit { color: black }");
        emit EnteredCorrectParams(_checker->isCorrect());
    }
    else
    {
        this->setStyleSheet("QLineEdit { color: red }");
        emit EnteredCorrectParams(_checker->isCorrect());
    }
}

bool TCustomLineEdit::getCorrect() const
{
    return _checker->isCorrect();
}

void TCustomLineEdit::delete_Null()
{
    QString str = this->text();
    this->setText(_checker->delete_Null(str));
}//------------------------------------------------------------------
