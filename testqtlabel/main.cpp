#include "mainwindow.h"
#include "spreadsheet.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();

    Q_INIT_RESOURCE(spreadsheet);

    QApplication app(argc, argv);
    SpreadSheet sheet(10, 6);
    sheet.setWindowIcon(QPixmap(":/images/interview.png"));
    sheet.show();
    return app.exec();
}
