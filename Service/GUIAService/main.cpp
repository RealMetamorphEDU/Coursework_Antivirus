#include <QGuiApplication>
#include "controller.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    Controller controller(&app);
    app.setOrganizationName("somename");
    app.setOrganizationDomain("somename");
    return app.exec();
}
