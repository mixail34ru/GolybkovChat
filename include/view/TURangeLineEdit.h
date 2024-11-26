#ifndef TURANGELINEEDIT_H
#define TURANGELINEEDIT_H

#include <QLineEdit>

class TURangeLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    struct Range{
        int min = 1;
        int max = 300;
    };
//Range _range;
    TURangeLineEdit(QWidget* parent = nullptr);
    TURangeLineEdit(const QString &contents, Range range, QWidget* parent = nullptr);
    TURangeLineEdit(const QString &contents, int min = 1, int max = 300, QWidget* parent = nullptr);
    ~TURangeLineEdit();

    bool isCorrect() const;

    void setRange(Range range);
    void setRange(int min, int max);

    Range range();

private:
    bool _is_correct;

    void constructor();
    Range _range;

private slots:
    void checkLineCorrect(const QString &text);

signals:
    void EnteredCorrectParams(bool);

}; //class TURangeLineEdit
//-------------------------------------------------------------------

#endif // TURANGELINEEDIT_H
