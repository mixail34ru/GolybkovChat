#ifndef TPACKAGEFORMAT_H
#define TPACKAGEFORMAT_H

#include <cstdint>

#include <QString>
#include <QMetaType>

enum class TypeData : int8_t {
    INPUT_DOUBLE  = -1,  //!< Занести в свою базу и использовать как значение параметрического сигнала
    INPUT_INT32   = -3,  //!< Занести в свою базу и использовать как значение дискретного слова
    INPUT_INT64   = -4,  //!< Занести в свою базу и использовать как значение параметрического (дискретного) сигнала
    OUTPUT_DOUBLE =  1,  //!< Вернуть абоненту, приславшему запрос,  значение параметрического сигнала из своей базы
    OUTPUT_INT32  =  3,  //!< Вернуть абоненту, приславшему запрос,  значение дискретного слова из своей базы
    OUTPUT_INT64  =  4   //!< Вернуть абоненту, приславшему запрос,  значение дискретного слова из своей базы в виде битового набора
}; //enum class TypeData
Q_DECLARE_METATYPE(TypeData)
//-------------------------------------------------------------------


enum class TypeSygnal : int8_t {
    ANALOG            = 1,  //!< Аналоговый
    MKIO              = 2,  //!< МКИО
    MACH_TO_MACH      = 3,  //!< Межмашинный обмен
    PBK               = 4,  //!< ПБК
    PARAMETRIC_SIGNAL = 5,  //!< Параметрический сигнал
    ONETIME_COMMAND   = 6   //!< Разовая команда
}; //enum class TypeSygnal
Q_DECLARE_METATYPE(TypeSygnal)
//-------------------------------------------------------------------


template<typename T>
struct ComboBoxDataSet {
    T type;
    QString label;
}; //struct ComboBoxDataSet
//-------------------------------------------------------------------


const static std::array<ComboBoxDataSet<TypeData>, 6> type_data_set {
    ComboBoxDataSet<TypeData>{ TypeData::INPUT_DOUBLE,  "(-1) double (занести)" },
    ComboBoxDataSet<TypeData>{ TypeData::INPUT_INT32,   "(-3) int32_t (занести)" },
    ComboBoxDataSet<TypeData>{ TypeData::INPUT_INT64,   "(-4) int64_t (занести)" },
    ComboBoxDataSet<TypeData>{ TypeData::OUTPUT_DOUBLE, "(1) double (вернуть)" },
    ComboBoxDataSet<TypeData>{ TypeData::OUTPUT_INT32,  "(3) int32_t (вернуть)" },
    ComboBoxDataSet<TypeData>{ TypeData::OUTPUT_INT64,  "(4) int64_t (вернуть)" }
};


const static std::array<ComboBoxDataSet<TypeSygnal>, 6> type_signal_set {
    ComboBoxDataSet<TypeSygnal>{ TypeSygnal::ANALOG,            "(1) Аналоговый" },
    ComboBoxDataSet<TypeSygnal>{ TypeSygnal::MKIO,              "(2) МКИО" },
    ComboBoxDataSet<TypeSygnal>{ TypeSygnal::MACH_TO_MACH,      "(3) Межмашинный обмен" },
    ComboBoxDataSet<TypeSygnal>{ TypeSygnal::PBK,               "(4) ПБК" },
    ComboBoxDataSet<TypeSygnal>{ TypeSygnal::PARAMETRIC_SIGNAL, "(5) Параметрический сигнал" },
    ComboBoxDataSet<TypeSygnal>{ TypeSygnal::ONETIME_COMMAND,   "(6) Разовая команда" }
};

#pragma pack(push, 1)
struct Package {
    int8_t type_data;
    int8_t type_signal;
    uint16_t id;

    union Payload {
        double parameter;
        int32_t word;
        int64_t llword;
    } payload;
}; //struct Package
#pragma pack(pop)
//-------------------------------------------------------------------


struct ViewSendPackage {
    TypeData type_data;
    TypeSygnal type_signal;
    uint16_t id;

    union Payload {
        double parameter;
        int32_t word;
        int64_t llword;
    } payload;
}; //struct ViewSendPackage
//-------------------------------------------------------------------


struct NetAddress {
    uint16_t port;
    std::string ip;
}; //struct NetAddress
//-------------------------------------------------------------------


struct ViewSendInfo {
    ViewSendPackage package;
    NetAddress address;
}; //struct SendInfo
//-------------------------------------------------------------------

#endif // TPACKAGEFORMAT_H
