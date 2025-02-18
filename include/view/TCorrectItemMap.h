#ifndef TCORRECTITEMMAP_H
#define TCORRECTITEMMAP_H

#include <QObject>

#include <unordered_map>

class TCorrectItemMap : public QObject {
    Q_OBJECT

    bool _isCorrect;
    std::unordered_map<QObject*, bool> _map;

public:
    TCorrectItemMap(QObject* parent = nullptr) : _isCorrect(true) {}

    bool Status() const {
        return _isCorrect;
    }

    size_t Size() const {
        return _map.size();
    }

    void EmplaceItem(QObject* obj, bool flag) {
        _map.emplace(obj, flag);
        CheckCorrectStatus(flag);
    }

    void EraseItem(QObject* obj) {
        _map.erase(obj);
        CheckCorrectStatus(true);
    }

    void Clear() {
        _map.clear();
        CheckCorrectStatus(true);
    }

    void SetItemStatus(QObject* obj, bool flag) {
        auto it = _map.find(obj);
        if (it != _map.end()) {
            if (it->second != flag) {
                it->second = flag;
                CheckCorrectStatus(flag);
            }
        }
    }

<<<<<<< HEAD
    bool GetItemStatus(QObject* obj) const {
=======
    bool GetItemStatus(QObject* obj) {
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
        auto it = _map.find(obj);
        if (it != _map.end())
            return it->second;

<<<<<<< HEAD
        return true; //!< TODO exception out_of_range
=======
        return false; //!< TODO exception out_of_range
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
    }

private:
    void CheckCorrectStatus(bool flag) {
        if (_isCorrect != flag) {
            bool status = true;

            for (auto& it: _map) {
                if (it.second == false) {
                    status = false;
                    break;
                }
            }

            if (_isCorrect != status) {
                _isCorrect = status;
                emit CorrectStatusChanged(_isCorrect);
            }
        }
    }

signals:
    void CorrectStatusChanged(bool);

}; //class TCorrectItemMap
//---------------------------------------------------------------

#endif // TCORRECTITEMMAP_H
