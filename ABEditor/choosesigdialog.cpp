#include "choosesigdialog.h"

#include <QGridLayout>
#include <QPushButton>
#include "qhexedit.h"
#include "QGroupBox"

ChooseSigDialog::ChooseSigDialog(QFile *file, QWidget *parent) : QDialog(parent) {
    setWindowTitle("Выбор сигнатуры");
    QGroupBox *extensionGroup = new QGroupBox(this);
    QVBoxLayout *extensionLayout = new QVBoxLayout(extensionGroup);
    sigEdit = new QHexEdit(extensionGroup);
    sigEdit->setHexCaps(true);
    sigEdit->setReadOnly(true);
    sigEdit->setData(*file);
    QPushButton *chooseButton = new QPushButton("Выбрать", extensionGroup);
    extensionLayout->addWidget(sigEdit);
    extensionLayout->addWidget(chooseButton);
    extensionGroup->setLayout(extensionLayout);
    connect(chooseButton, SIGNAL(clicked()), this, SLOT(preAccepted()));
    extensionGroup->setGeometry(10, 10, 576, 444);
}

ChooseSigDialog::~ChooseSigDialog() {
}

const QByteArray& ChooseSigDialog::getSelectedData() {
    return selected;
}

void ChooseSigDialog::preAccepted() {
    selected = sigEdit->selectedData();
    accept();
}
