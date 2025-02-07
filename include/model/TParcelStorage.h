#ifndef TPARCELSTORAGE_H
#define TPARCELSTORAGE_H

#include "TPackageFormat.h"

#include <vector>

class TParcelStorage
{
public:
    TParcelStorage() = default;
    ~TParcelStorage() = default;

    void push_back(){};

private:
    std::vector<ViewSendPackage> _parcel;

};//class TParcelStorage
//-------------------------------------------------------------------

#endif // TPARCELSTORAGE_H
