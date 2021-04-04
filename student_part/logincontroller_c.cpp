#include "logincontroller_c.h"

#include "userinfomodel_c.h"
#include "loginverificationmodel_c.h"

LoginController_c::LoginController_c(QObject *parent) : QObject(parent)
{}

void LoginController_c::login(const QString &_username, const QString &_password)
{
    //передати рядки моделі верифікації
    if(LoginVerificationModel_c::instance()->loginVerificationSuccessful(_username, _password))
    {
        //якщо всьо ок, то *рядки внизу* (потім мб відкрити звідси наступне вікно)
        UserInfoModel_c::instance()->setUsername(_username);
        UserInfoModel_c::instance()->setPassword(_password);
    }
    else
    {
        //якщо верифікація не пройшла, то даєм сигнал
        emit loginError();
    }

}

void LoginController_c::registration(const QString &_name, const QString &_surname,
                                     const QString &_group, const QString &_username,
                                     const QString &_password)
{
    //передати рядки моделі верифікації
    if(LoginVerificationModel_c::instance()->registrationVerificationSuccessful(_username, _password,
                                                                                _name, _surname, _group))
    {
        //якщо всьо ок
        UserInfoModel_c::instance()->setUsername(_username);
        UserInfoModel_c::instance()->setPassword(_password);
        UserInfoModel_c::instance()->setName(_name);
        UserInfoModel_c::instance()->setSurname(_surname);
        UserInfoModel_c::instance()->setGroup(_group);
    }
    else
    {
        //якщо верифікація не пройшла, то ошипка!1
        emit registrationError();
    }
}