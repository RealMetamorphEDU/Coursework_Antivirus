#include "choosesigdialog.h"

#include <QGridLayout>
#include <QPushButton>
#include "qhexedit.h"
#include "QGroupBox"

ChooseSigDialog::ChooseSigDialog(QFile *file, QWidget *parent) : QDialog(parent) {
    setWindowTitle("Выбор сигнатуры");
    auto *extensionGroup = new QGroupBox(this);
    auto *extensionLayout = new QVBoxLayout(extensionGroup);
    sigEdit = new QHexEdit(extensionGroup);
    sigEdit->setHexCaps(true);
    sigEdit->setReadOnly(true);
    sigEdit->setData(*file);
    auto *chooseButton = new QPushButton("Выбрать", extensionGroup);
    extensionLayout->addWidget(sigEdit);
    extensionLayout->addWidget(chooseButton);
    extensionGroup->setLayout(extensionLayout);
    connect(chooseButton, SIGNAL(clicked()), this, SLOT(preAccepted()));
    extensionGroup->setGeometry(10, 10, 576, 444);
}

const QByteArray& ChooseSigDialog::getSelectedData() const {
    return selected;
}

void ChooseSigDialog::preAccepted() {
    selected = sigEdit->selectedData();
    accept();
}
