#include "TClient.h"

#include <QDebug>

TClient::TClient(QObject* parent) : QObject(parent) {
}//------------------------------------------------------------------


TClient::~TClient() {
    StopSendingMessage();
}//------------------------------------------------------------------


void TClient::SendMessage(
    const std::string& host, uint16_t port, const void* buffer, size_t size)
{
    try { _client.SendDataTo(host.c_str(), port, buffer, size); }
    catch (...) { qDebug() << "exception TClient::SendMessage"; }

    emit statusSendingChanged(false);
}//------------------------------------------------------------------


void TClient::SendParsel(NetAddress info)
{
    std::vector<Package> vec;
    for (int i = 0; i < _storage.size(); i++)
    {
        vec.push_back(ViewSendPackageToPackageConverter(_storage.at(i)));
    }
    const void* buffer = vec.data();
    size_t size = _storage.size() * sizeof(Package);
    SendMessage(info.ip, info.port, buffer, size);
}

void TClient::StartSendingMessage(
    uint32_t timeout,
    const std::string& host, uint16_t port, const void* buffer, size_t size,
    handler_exception_t hndl_except)
{
    try {
        if (!_timer && timeout > 0) {
            // локальный буфер
            std::shared_ptr<char[]> local_buff(new char[size]);
            memcpy(local_buff.get(), buffer, size);

            _timer = std::make_unique<wstd::timer>(
                std::chrono::milliseconds(timeout),
                [this, timeout, host, port, local_buff, size]() {
                    _client.SendDataTo(host.c_str(), port, local_buff.get(), size);
                    qDebug() << "timeout " << timeout;
                },
                true,
                [this, hndl_except](std::exception_ptr eptr, wstd::timer* timer) {
                    hndl_except(eptr, this);
                }
            );
        }
    }
    catch (...) {
        qDebug() << "exception TClient::StartTimerMessage";
    }

    emit statusSendingTimerChanged(IsTimerSending());
}//------------------------------------------------------------------


void TClient::SendTimerParsel(uint timeout, NetAddress info, handler_exception_t hndl_except)
{
    std::vector<Package> vec;
    for (int i = 0; i < _storage.size(); i++)
    {
        vec.push_back(ViewSendPackageToPackageConverter(_storage.at(i)));
    }
    const void* buffer = vec.data();
    size_t size = _storage.size() * sizeof(Package);
    StartSendingMessage(timeout, info.ip, info.port, buffer, size, hndl_except);
}


void TClient::StopSendingMessage() {
    if (_timer) _timer.reset();
    emit statusSendingTimerChanged(IsTimerSending());
}//------------------------------------------------------------------


bool TClient::IsTimerSending() const {
    return (_timer.get() != nullptr ? true : false);
}//------------------------------------------------------------------


const QVector<ViewSendPackage>& TClient::getStorage() const noexcept {
    return _storage;
}//------------------------------------------------------------------


void TClient::appendToStorage(const ViewSendPackage& value) {
    _storage.append(value);
    emit storageInserted(_storage.size() - 1, 1);
}//------------------------------------------------------------------


void TClient::removeFromStorage(int i, int count) {
    if (!_storage.empty() && i >= 0) {
        if ( (i < _storage.size()) && (i + count < _storage.size()) ) {
            _storage.remove(i, count);
            emit storageErased(i, count);
        }
        else if (i < _storage.size()) {
            count = _storage.size() - i;
            _storage.remove(i, count);
            emit storageErased(i, count);
        }
    }
}//------------------------------------------------------------------


void TClient::clearStorage() {
    _storage.clear();
    emit storageCleared();
}//------------------------------------------------------------------


void TClient::checkPackages() const {
    for (auto& it : _storage) {
        qDebug() << "CheckPackages: "
                 << "TypeData: " << static_cast <int8_t>(it.type_data)
                 << "\tTypeSignal: " << static_cast <int8_t>(it.type_signal)
                 << "\tID: " << it.id
                 << "\tPayload.parameter: " << it.payload.parameter
                 << "\tPayload.word: " << it.payload.word
                 << "\tPayload.llword: " << it.payload.llword;
    }
}//------------------------------------------------------------------


Package TClient::ViewSendPackageToPackageConverter(
    const ViewSendPackage& info) const noexcept
{
    return Package{
        static_cast<int8_t>(info.type_data),
        static_cast<int8_t>(info.type_signal),
        info.id,
        info.payload.parameter
    };
}//------------------------------------------------------------------
