#include "TSendDataGroupBox.h"

#include "TPackageFormat.h"
#include "TCorrectItemMap.h"

#include <QRegularExpressionValidator>

#include <climits>
#include <cmath>

TSendDataGroupBox::TSendDataGroupBox(QWidget* parent)
    : QGroupBox(parent)
{
    _correct_map = new TCorrectItemMap(this);
    connect(
        _correct_map, SIGNAL(CorrectStatusChanged(bool)),
        this, SLOT(CorrectSignalEmitent(bool))
    );

    /* Тип данных */

    _type_data_cmb_bx = new QComboBox(this);
    for (auto& it: type_data_set)
        _type_data_cmb_bx->addItem(it.label,  QVariant::fromValue(it.type));

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
    _correct_map->EmplaceItem(_id_ln_edit, true);
    _id_ln_edit->setValidator(
        new QIntValidator(0, USHRT_MAX, _id_ln_edit)
    );
    connect(
        _id_ln_edit, SIGNAL(textChanged(QString)),
        this, SLOT(Validate_id_ln_edit(QString))
    );

    /* Значение параметра */

    _parameter_ln_edit = new QLineEdit("1", this);
    _parameter_ln_edit->setValidator(new QDoubleValidator(_parameter_ln_edit));
    connect(
        _parameter_ln_edit, SIGNAL(textChanged(QString)),
        this, SLOT(Validate_parameter_ln_edit(QString))
    );
    _correct_map->EmplaceItem(_parameter_ln_edit, true);

    _matrix_ln_edit = new QLineEdit("1", this);
    _matrix_ln_edit->setValidator(new QIntValidator(_matrix_ln_edit));
    connect(
        _matrix_ln_edit, SIGNAL(textChanged(QString)),
        this, SLOT(Validate_matrix_ln_edit(QString))
    );
    _correct_map->EmplaceItem(_matrix_ln_edit, true);

    _mask_ln_edit = new QLineEdit("1", this);
    _mask_ln_edit->setValidator(new QIntValidator(_mask_ln_edit));
    connect(
        _mask_ln_edit, SIGNAL(textChanged(QString)),
        this, SLOT(Validate_mask_ln_edit(QString))
    );
    _correct_map->EmplaceItem(_mask_ln_edit, true);

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


std::optional<ViewSendPackage> TSendDataGroupBox::get_package() {
    try {
        ViewSendPackage pack;

        pack.type_data = get_combo_box_var<TypeData>(_type_data_cmb_bx);
        pack.type_signal = get_combo_box_var<TypeSygnal>(_type_signal_cmb_bx);
        pack.id = _id_ln_edit->text().toUShort();

        TypeData type = static_cast<TypeData>(pack.type_data);
        if (type == TypeData::INPUT_DOUBLE || type == TypeData::OUTPUT_DOUBLE) {
            QString temp = _parameter_ln_edit->text().replace(QChar(',') , QChar('.'));
            pack.payload.parameter = temp.toDouble();
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


void TSendDataGroupBox::SetEnableDataField(bool flag) {
    _type_data_cmb_bx->setEnabled(flag);
    _type_signal_cmb_bx->setEnabled(flag);
    _id_ln_edit->setEnabled(flag);
    _parameter_ln_edit->setEnabled(flag);
    _matrix_ln_edit->setEnabled(flag);
    _mask_ln_edit->setEnabled(flag);
}//------------------------------------------------------------------


void TSendDataGroupBox::CorrectSignalEmitent(bool flag) {
    auto data = _type_data_cmb_bx->currentData();
    if (!data.isNull()) {
        if (data.canConvert<TypeData>()){
            auto type = data.value<TypeData>();

            if (type == TypeData::INPUT_DOUBLE || type == TypeData::OUTPUT_DOUBLE) {
                emit EnteredUncorrectParams(this, _correct_map->GetItemStatus(_parameter_ln_edit));
            }
            else if (type == TypeData::INPUT_INT32 || type == TypeData::OUTPUT_INT32) {
                emit EnteredUncorrectParams(this, _correct_map->GetItemStatus(_matrix_ln_edit));
            }
            else {
                emit EnteredUncorrectParams(this,
                    _correct_map->GetItemStatus(_matrix_ln_edit) && _correct_map->GetItemStatus(_mask_ln_edit)
                 );
            }
        }
    }
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

    CorrectSignalEmitent(true);
}//------------------------------------------------------------------


void TSendDataGroupBox::Validate_id_ln_edit(const QString& text) {
    uint32_t num = text.toUInt();
    if (num >= 0 && num <= USHRT_MAX) {
        _id_ln_edit->setStyleSheet("QLineEdit { color: black }");
        _correct_map->SetItemStatus(_id_ln_edit, true);

    }
    else {
        _id_ln_edit->setStyleSheet("QLineEdit { color: red }");
        _correct_map->SetItemStatus(_id_ln_edit, false);
    }
}//------------------------------------------------------------------


void TSendDataGroupBox::Validate_parameter_ln_edit(const QString& text) {
    QString str = text;
    str.replace(QChar(',') , QChar('.'));

    double num = str.toDouble();
    if (!std::isinf(num)) {
        _parameter_ln_edit->setStyleSheet("QLineEdit { color: black }");
        _correct_map->SetItemStatus(_parameter_ln_edit, true);
    }
    else {
        _parameter_ln_edit->setStyleSheet("QLineEdit { color: red }");
        _correct_map->SetItemStatus(_parameter_ln_edit, false);
    }
}//------------------------------------------------------------------


void TSendDataGroupBox::Validate_matrix_ln_edit(const QString& text) {
    long long num = text.toLongLong();
    if ((num >= INT32_MIN) && (num <= INT32_MAX)) {
        _matrix_ln_edit->setStyleSheet("QLineEdit { color: black }");
        _correct_map->SetItemStatus(_matrix_ln_edit, true);
    }
    else {
        _matrix_ln_edit->setStyleSheet("QLineEdit { color: red }");
        _correct_map->SetItemStatus(_matrix_ln_edit, false);
    }
}//------------------------------------------------------------------


void TSendDataGroupBox::Validate_mask_ln_edit(const QString& text) {
    long long num = text.toLongLong();
    if (num >= INT_MIN && num <= INT_MAX) {
        _mask_ln_edit->setStyleSheet("QLineEdit { color: black }");
        _correct_map->SetItemStatus(_mask_ln_edit, true);
    }
    else {
        _mask_ln_edit->setStyleSheet("QLineEdit { color: red }");
        _correct_map->SetItemStatus(_mask_ln_edit, false);
    }
}//------------------------------------------------------------------
