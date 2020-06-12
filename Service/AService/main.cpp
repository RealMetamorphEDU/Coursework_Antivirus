#include <Windows.h>
#include <iostream>
#include <QFileInfo>
#include <QCoreApplication>
#include "aservicelog.h"
#include "controller.h"
#include "aserviceevents.h"

char SERVICE_NAME[]{"AService"};
char DISPLAY_NAME[]{"AntivirusService"};


void WINAPI serviceMain(int argc, char *argv[]);
void WINAPI controlHandler(DWORD control);
void srvInstall();
void srvUninstall();

AServiceLog *logger = nullptr;
Controller *controller;

void main(int argc, char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "install") == 0) // Install service
            srvInstall();
        else if (strcmp(argv[1], "uninstall") == 0) // Uninstall service
            srvUninstall();
        else // Bad usage
            std::cout << "Usage: AService [install | uninstall]" << std::endl;
    } else {
        // Создаём точку входа сервиса
        SERVICE_TABLE_ENTRYA entryTable[2]; // entry point for service
        entryTable[0] = {SERVICE_NAME, LPSERVICE_MAIN_FUNCTIONA(serviceMain)};
        entryTable[1] = {nullptr, nullptr};
        // Start control dispatcher
        logger = new AServiceLog(SERVICE_NAME);
        logger->setLevel(Level::INFO);
        if (!StartServiceCtrlDispatcherA(entryTable)) {
            logger->critical("STARTUP", "Event dispatcher didn't start.");
            std::cerr << "Critical error: " << GetLastError() << std::endl;
            delete logger;
        }
    }
}

void WINAPI serviceMain(int argc, char *argv[]) {
    if (logger == nullptr)
        logger = new AServiceLog(SERVICE_NAME);
    // Register control event handler
    logger->info("MAIN", "Initialization process started.");
    SERVICE_STATUS_HANDLE statusHandle = RegisterServiceCtrlHandlerA(SERVICE_NAME, controlHandler);
    if (!statusHandle) {
        logger->critical("MAIN", "Event handler is not registered.");
        delete logger;
        return;
    }
    SERVICE_STATUS status = {SERVICE_WIN32_OWN_PROCESS, SERVICE_START_PENDING, 0, 0, 0, 0, 3000};
    SetServiceStatus(statusHandle, &status);
    QCoreApplication app(argc, argv);
    AServiceBaseLoader::initLoader(nullptr);
    controller = new Controller(logger, statusHandle, &app);
    if (!controller->isBreak()) {
        QCoreApplication::connect(&app, &QCoreApplication::aboutToQuit, controller, &Controller::deleteLater);
        QCoreApplication::exec();
    } else {
        delete controller;
    }
    delete AServiceBaseLoader::getInstance();
    status.dwCurrentState = SERVICE_STOPPED;
    SetServiceStatus(statusHandle, &status);
}

void WINAPI controlHandler(DWORD control) {
    QCoreApplication::postEvent(controller, new ControlEvent(control), Qt::HighEventPriority);
}

void srvInstall() {
    QByteArray arr(MAX_PATH, 0);
    GetModuleFileNameA(nullptr, arr.data(), MAX_PATH);
    QFileInfo info(arr);
    std::string path = QString("\"").append(info.canonicalFilePath()).append("\"").toStdString();

    // Get a handle to the SCM database. 
    SC_HANDLE scManager = OpenSCManagerA(nullptr, nullptr,SC_MANAGER_CREATE_SERVICE | SC_MANAGER_MODIFY_BOOT_CONFIG);

    if (nullptr == scManager) {
        std::cerr << "OpenSCManager failed " << GetLastError() << ".\n";
        return;
    }

    // Create the service
    SC_HANDLE service = CreateServiceA(scManager, SERVICE_NAME, DISPLAY_NAME, SERVICE_ALL_ACCESS,
                                       SERVICE_WIN32_OWN_PROCESS, SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL,
                                       path.c_str(), nullptr, nullptr, nullptr, nullptr, nullptr);

    if (service == nullptr) {
        std::cerr << "CreateService failed with " << GetLastError() << ".\n";
        CloseServiceHandle(scManager);
        return;
    }
    if (AServiceLog::registerSource(SERVICE_NAME))
        std::cout << "Log registered successfully." << std::endl;
    std::cout << "Service installed successfully." << std::endl;

    CloseServiceHandle(service);
    CloseServiceHandle(scManager);
}

void srvUninstall() {
	
    // Get a handle to the SCM database. 
    SC_HANDLE scManager = OpenSCManagerA(nullptr, nullptr,
                                         SC_MANAGER_CREATE_SERVICE | SC_MANAGER_ENUMERATE_SERVICE |
                                         SC_MANAGER_MODIFY_BOOT_CONFIG);

    // Open service
    SC_HANDLE service = OpenServiceA(scManager, SERVICE_NAME, SERVICE_ALL_ACCESS);
    LPSERVICE_STATUS contrRet = new SERVICE_STATUS;
    if (!ControlService(
        service,
        SERVICE_CONTROL_STOP,
        contrRet)) {
        std::cerr << "Error deleting the service" << std::endl;
        CloseServiceHandle(service);
        CloseServiceHandle(scManager);
    }
    // Delete service
    bool status = DeleteService(service);
    if (status)
        std::cout << "service was successfully deleted." << std::endl;
    else
        std::cerr << "Error deleting the service" << std::endl;
    if (AServiceLog::doUnregisteredSource(SERVICE_NAME))
        std::cout << "Log was successfully unregistered." << std::endl;
    CloseHandle(service);
    CloseHandle(scManager);
}
