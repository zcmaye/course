// documentproperty.cpp

#include <QtGlobal>
#include <QtCore>
#include <QDebug>

#include "xlsxdocument.h"

int documentproperty()
{
    QXlsx::Document xlsx;
    xlsx.write("A1", "View the properties through:");
    xlsx.write("A2", "Office Button -> Prepare -> Properties option in Excel");

    xlsx.setDocumentProperty("title", "This is an example spreadsheet");
    xlsx.setDocumentProperty("subject", "With document properties");
    xlsx.setDocumentProperty("creator", "Debao Zhang");
    xlsx.setDocumentProperty("company", "HMICN");
    xlsx.setDocumentProperty("category", "Example spreadsheets");
    xlsx.setDocumentProperty("keywords", "Sample, Example, Properties");
    xlsx.setDocumentProperty("description", "Created with Qt Xlsx");

    xlsx.saveAs("documentproperty.xlsx");
    return 0;
}
