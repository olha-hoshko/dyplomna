#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QIcon>

#include <userinfomodel_c.h>
#include <logincontroller_c.h>
#include "documenthandler.h"
#include "lecturecontroller_c.h"
#include "networkmodel_c.h"
#include "courselistmodel_c.h"
#include "testcontroller_c.h"
#include "testmodel.h"
#include "recommendationlistmodel_c.h"
#include "chartmodel_c.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QStandardPaths>
#include <QDir>
#include "chat/sqlcontactmodel.h"
#include "chat/sqlconversationmodel.h"

using namespace QtCharts;

static void connectToChatDatabase()
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.isValid()) {
        database = QSqlDatabase::addDatabase("QSQLITE");
        if (!database.isValid())
            qFatal("Cannot add database: %s", qPrintable(database.lastError().text()));
    }

    const QDir writeDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    if (!writeDir.mkpath("."))
        qFatal("Failed to create writable directory at %s", qPrintable(writeDir.absolutePath()));

    const QString fileName = writeDir.absolutePath() + "/chat-database.sqlite3";
    database.setDatabaseName(fileName);
    if (!database.open()) {
        qFatal("Cannot open database: %s", qPrintable(database.lastError().text()));
        QFile::remove(fileName);
    }
}

int main(int argc, char *argv[])  
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    qmlRegisterSingletonType(QUrl("qrc:/UI/ClientLoginConstants.qml"), "LoginPage", 1, 0, "ClientLoginConstants");
    qmlRegisterSingletonType<UserInfoModel_c>("Models", 1, 0, "UserInfoModel", &UserInfoModel_c::qmlInstance);
    qmlRegisterSingletonType<CourseListModel_c>("Models", 1, 0, "CourseModel", &CourseListModel_c::qmlInstance);
    qmlRegisterSingletonType<TestModel>("Models", 1, 0, "TestModel", &TestModel::qmlInstance);
    qmlRegisterSingletonType<RecommendationListModel_c>("Models", 1, 0, "RecommendationModel", &RecommendationListModel_c::qmlInstance);
    qmlRegisterSingletonType<ChartModel_c>("Models", 1, 0, "ChartModel", &ChartModel_c::qmlInstance);

    qmlRegisterType<LoginController_c>("Controllers", 1, 0, "ClientLoginController");
    qmlRegisterType<DocumentHandler>("Controllers", 1, 0, "DocumentHandler");
    qmlRegisterType<LectureController_c>("Controllers", 1, 0, "LectureController");
    qmlRegisterType<TestController_c>("Controllers", 1, 0, "TestController");

    //chat database
    qmlRegisterType<SqlContactModel>("io.qt.examples.chattutorial", 1, 0, "SqlContactModel");
    qmlRegisterType<SqlConversationModel>("io.qt.examples.chattutorial", 1, 0, "SqlConversationModel");

    connectToChatDatabase();

    QApplication app(argc, argv);

    app.setWindowIcon(QIcon(":/UI/images/windowIcon.ico"));

    QQmlApplicationEngine engine;

    auto network = NetworkModel_c::instance();
    Q_UNUSED(network)

    const QUrl url(QStringLiteral("qrc:/UI/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    QApplication::setQuitOnLastWindowClosed(false);

    return app.exec();
}
