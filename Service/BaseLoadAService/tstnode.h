#ifndef TSTNODE_H
#define TSTNODE_H

class SignatureRecord;
#include <QVector>

typedef unsigned char byte;

class TSTNode {
    int count;
    SignatureRecord **array;
public:
    byte element;
    bool isEnd;

    TSTNode *equal;
    TSTNode *left;
    TSTNode *right;

    TSTNode(byte el, bool end);
    ~TSTNode();

    bool addRecord(SignatureRecord* record);
    QVector<SignatureRecord*> getRecords() const;
};

#endif // TSTNODE_H
