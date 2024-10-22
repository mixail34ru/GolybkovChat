#include "TSendDataGroupBox.h"
#include "TPackageFormat.h"

TSendDataGroupBox::TSendDataGroupBox(QWidget* parent) : QGroupBox(parent)
{
    /* Тип данных */

    _type_data_cmb_bx = new QComboBox(this);
    for (auto& it: type_data_set) {
        _type_data_cmb_bx->addItem(it.label,  QVariant::fromValue(it.type));
    }

    connect(
        _type_data_cmb_bx, SIGNAL(currentIndexChanged(int)),
        this, SLOT(currentTypeDataChanged(int))
    );

    /* Тип сигнала */

    _type_signal_cmb_bx = new QComboBox(this);
    for (auto& it: type_signal_set) {
        _type_signal_cmb_bx->addItem(it.label,  QVariant::fromValue(it.type));
    }

    /* Номер параметра */

    _id_ln_edit = new QLineEdit("1", this);

    /* Значение параметра */

    _parameter_ln_edit = new QLineEdit("1", this);
    _matrix_ln_edit = new QLineEdit("1", this);
    _mask_ln_edit = new QLineEdit("1", this);

    /* Настройка параметров виджета */

    _package_frm_lt = new QFormLayout(this);
    _package_frm_lt->addRow("Тип данных:", _type_data_cmb_bx);
    _package_frm_lt->addRow("Тип сигнала:", _type_signal_cmb_bx);
    _package_frm_lt->addRow("ID параметра:", _id_ln_edit);
    _package_frm_lt->addRow("Значение:", _parameter_ln_edit);
    _package_frm_lt->addRow("Матрица:", _matrix_ln_edit);
    _package_frm_lt->addRow("Маска:", _mask_ln_edit);

    currentTypeDataChanged(_type_data_cmb_bx->currentIndex());

    this->setTitle("Содержимое отправляемого пакета");
    this->setLayout(_package_frm_lt);
}//------------------------------------------------------------------


TSendDataGroupBox::~TSendDataGroupBox() {
}//------------------------------------------------------------------


std::optional<Package> TSendDataGroupBox::get_package() {
    try {
        Package pack;

        pack.type_data = get_combo_box_var<TypeData, int8_t>(_type_data_cmb_bx);
        pack.type_signal = get_combo_box_var<TypeSygnal, int8_t>(_type_signal_cmb_bx);
        pack.id = _id_ln_edit->text().toUShort();

        TypeData type = static_cast<TypeData>(pack.type_data);
        if (type == TypeData::INPUT_DOUBLE || type == TypeData::OUTPUT_DOUBLE) {
            pack.payload.parameter = _parameter_ln_edit->text().toDouble();
        }
        else if (type == TypeData::INPUT_INT32 || type == TypeData::OUTPUT_INT32){
            pack.payload.word = _matrix_ln_edit->text().toInt();
        }
        else {
            pack.payload.llword = static_cast<int64_t>(_mask_ln_edit->text().toInt()) << 32;
            pack.payload.llword = pack.payload.llword | static_cast<int64_t>(_matrix_ln_edit->text().toInt());
        }

        return pack;
    }
    catch (...) {

    }

    return std::nullopt;
}//------------------------------------------------------------------


void TSendDataGroupBox::currentTypeDataChanged(int index) {
    auto data = _type_data_cmb_bx->itemData(index);
    if (!data.isNull()) {
        if (data.canConvert<TypeData>()) {
            auto type = data.value<TypeData>();

            if (type == TypeData::INPUT_DOUBLE || type == TypeData::OUTPUT_DOUBLE) {
                _package_frm_lt->setRowVisible(_parameter_ln_edit, true);
                _package_frm_lt->setRowVisible(_matrix_ln_edit, false);
                _package_frm_lt->setRowVisible(_mask_ln_edit, false);
            }
            else if (type == TypeData::INPUT_INT32 || type == TypeData::OUTPUT_INT32){
                _package_frm_lt->setRowVisible(_parameter_ln_edit, false);
                _package_frm_lt->setRowVisible(_matrix_ln_edit, true);
                _package_frm_lt->setRowVisible(_mask_ln_edit, false);
            }
            else {
                _package_frm_lt->setRowVisible(_parameter_ln_edit, false);
                _package_frm_lt->setRowVisible(_matrix_ln_edit, true);
                _package_frm_lt->setRowVisible(_mask_ln_edit, true);
            }
        }
    }
}//------------------------------------------------------------------
