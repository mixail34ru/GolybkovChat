#ifndef TSENDDATAGROUPBOX_H
#define TSENDDATAGROUPBOX_H

#include "TPackageFormat.h"

#include <QGroupBox>
#include <QFormLayout>
#include <QComboBox>
#include <QLineEdit>

#include <optional>

class TCorrectItemMap;

class TSendDataGroupBox : public QGroupBox
{
    Q_OBJECT

    TCorrectItemMap* _correct_map;

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

    std::optional<ViewSendPackage> get_package();

    void SetEnableDataField(bool flag);

private:
    template<typename D>
    D get_combo_box_var(const QComboBox* cmbbx) {
        auto data = cmbbx->itemData(cmbbx->currentIndex());
        if (!data.isNull()) {
            if (data.canConvert<D>()) {
                return data.value<D>();
            }
        }

        throw;
    }

private slots:
    void CorrectSignalEmitent(bool flag);
    void currentTypeDataChanged(int index);
    void Validate_id_ln_edit(const QString& text);
    void Validate_parameter_ln_edit(const QString& text);
    void Validate_matrix_ln_edit(const QString& text);
    void Validate_mask_ln_edit(const QString& text);

signals:
    void EnteredUncorrectParams(QObject* obj, bool flag);

}; //class TSendDataGroupBox
//-------------------------------------------------------------------

#endif // TSENDDATAGROUPBOX_H
