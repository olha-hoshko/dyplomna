#ifndef USERINFOMODEL_C_H
#define USERINFOMODEL_C_H

#include <QObject>
#include <QString>
#include <QQmlEngine>
#include <QJSEngine>

#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QJsonValue>
#include <QJsonObject>
#include <QStandardPaths>

#include "user.h"

class UserInfoModel_c : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString surname READ surname WRITE setSurname NOTIFY surnameChanged)
    Q_PROPERTY(QString group READ group WRITE setGroup NOTIFY groupChanged)

public:
    static UserInfoModel_c* instance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

public slots:
    QString username() const;
    QString password() const;
    QString name() const;
    QString surname() const;
    QString group() const;
    void setUsername(const QString &_username);
    void setPassword(const QString &_password);
    void setName(const QString &_name);
    void setSurname(const QString &_surname);
    void setGroup(const QString &_group);
    void getUserInfo(Student &_student);

private:
    explicit UserInfoModel_c(QObject *_parent_ptr = nullptr);

    const QString studentJsonFileName{"studentsinfo.json"};
    QJsonDocument loadJson(const QString &fileName);

signals:
    void usernameChanged();
    void passwordChanged();
    void nameChanged();
    void surnameChanged();
    void groupChanged();

private:
    Student mStudent;
    static UserInfoModel_c* mInstance_ptr;
};

#endif // USERINFOMODEL_C_H
