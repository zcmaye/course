#include "ExpandableDialog.h"
#include "./ui_ExpandableDialog.h"

ExpandableDialog::ExpandableDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ExpandableDialog)
{
    ui->setupUi(this);

    ui->secondaryGroupBox->hide();
    ui->tertiaryGroupBox->hide();
    layout()->setSizeConstraint(QLayout::SetFixedSize);
}

ExpandableDialog::~ExpandableDialog()
{
    delete ui;
}

