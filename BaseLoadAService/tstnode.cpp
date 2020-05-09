#include "tstnode.h"
#include "signaturerecord.h"

TSTNode::TSTNode(byte el, bool end) {
    element = el;
    isEnd = end;
    left = nullptr;
    equal = nullptr;
    right = nullptr;
    count = 0;
    array = nullptr;
}

TSTNode::~TSTNode() {
    if (left != nullptr)
        delete left;
    if (equal != nullptr)
        delete equal;
    if (right != nullptr)
        delete right;
    if (array != nullptr) {
        delete[] array;
    }
}

bool TSTNode::addRecord(SignatureRecord *record) {
    if (array == nullptr) {
        array = new SignatureRecord*[1];
        array[0] = record;
        count = 1;
        return true;
    }
    for (int i = 0; i < count; ++i) {
        if (*array[i] == *record)
            return false;
    }
    SignatureRecord **nArr = new SignatureRecord*[++count];
    for (int i = 0; i < count - 1; ++i) {
        nArr[i] = array[i];
    }
    nArr[count - 1] = record;
    delete[] array;
    array = nArr;
    return true;
}

QVector<SignatureRecord*> TSTNode::getRecords() const {
    QVector<SignatureRecord*> records(count);
    for (int i = 0; i < count; ++i) {
        records.append(array[i]);
    }
    return records;
}
