#ifndef TSENDDATAGROUPBOX_H
#define TSENDDATAGROUPBOX_H

#include "TPackageFormat.h"

#include <QGroupBox>
#include <QFormLayout>
#include <QComboBox>
#include <QLineEdit>

#include <optional>

class TSendDataGroupBox : public QGroupBox
{
    Q_OBJECT

    QFormLayout* _package_frm_lt;
    QComboBox* _type_data_cmb_bx;
    QComboBox* _type_signal_cmb_bx;
    QLineEdit* _id_ln_edit;
    QLineEdit* _parameter_ln_edit;
    QLineEdit* _matrix_ln_edit;
    QLineEdit* _mask_ln_edit;

public:
    TSendDataGroupBox(QWidget* parent = nullptr);
    ~TSendDataGroupBox();

    std::optional<Package> get_package();

private:
    template<typename D, typename R>
    R get_combo_box_var(const QComboBox* cmbbx) {
        auto data = cmbbx->itemData(cmbbx->currentIndex());
        if (!data.isNull()) {
            if (data.canConvert<D>()) {
                return static_cast<R>(data.value<D>());
            }
        }

        throw;
    }

private slots:
    void currentTypeDataChanged(int index);

}; //class TSendDataGroupBox
//-------------------------------------------------------------------

#endif // TSENDDATAGROUPBOX_H
