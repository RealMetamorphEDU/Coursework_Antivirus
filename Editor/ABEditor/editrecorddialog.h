#ifndef EDITRECORDDIALOG_H
#define EDITRECORDDIALOG_H
#include <QFileDialog>
#include "signaturerecord.h"

namespace Ui {
    class EditRecordDialog;
};


class EditRecordDialog: public QDialog {
Q_OBJECT
    SignatureRecord *record;
    bool sigSet;
    QByteArray selectedData;
    bool checkFields() const;
public:
    explicit EditRecordDialog(QWidget *parent = Q_NULLPTR);
    explicit EditRecordDialog(SignatureRecord *record, QWidget *parent = Q_NULLPTR);
    ~EditRecordDialog();
    SignatureRecord* getRecord() const;
private slots:
    void checkAccept();
    void chooseSig();
    void chosenSig();
    void changedPrefixLen(int value) const;
private:
    Ui::EditRecordDialog *ui;
};

#endif