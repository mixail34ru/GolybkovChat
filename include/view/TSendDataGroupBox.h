#ifndef TSENDDATAGROUPBOX_H
#define TSENDDATAGROUPBOX_H

#include "TPackageFormat.h"

#include "TCustomLineEdit.h"

#include <QGroupBox>
#include <QFormLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

#include <optional>

class TCorrectItemMap;

class TSendDataGroupBox : public QGroupBox
{
    Q_OBJECT

    TCorrectItemMap* _correct_map;

<<<<<<< HEAD
    QVBoxLayout* _form_lt;
    QHBoxLayout* _button_frm_lt;
=======
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
    QFormLayout* _package_frm_lt;
    QComboBox* _type_data_cmb_bx;
    QComboBox* _type_signal_cmb_bx;

    TCustomLineEdit* _id_ln_edit;
    TCustomLineEdit* _parameter_ln_edit;
    TCustomLineEdit* _matrix_ln_edit;
    TCustomLineEdit* _mask_ln_edit;

    QPushButton* _add_pack;
    QPushButton* _change_pack;

public:
    explicit TSendDataGroupBox(QWidget* parent = nullptr);
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

        throw; //!< TODO
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

signals:
    void EnteredUncorrectParams(QObject* obj, bool flag);
    void addPackageActivated(ViewSendPackage pack);

}; //class TSendDataGroupBox
//-------------------------------------------------------------------

#endif // TSENDDATAGROUPBOX_H
