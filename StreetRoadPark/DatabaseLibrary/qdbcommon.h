#ifndef QDBCOMMON_H
#define QDBCOMMON_H

namespace Db {
    typedef enum __OperationType { // CRUD
        DataInsert = 0,
        DataSelect,
        DataUpdate,
        DataDelete
    } OperationType;
}

#endif // QDBCOMMON_H
