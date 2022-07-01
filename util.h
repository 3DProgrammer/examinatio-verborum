#ifndef EXAMINATIO_VERBORUM_UTIL_H
#define EXAMINATIO_VERBORUM_UTIL_H
#define quickSetting(name,type,default) QSettings().value(QString::fromStdString(std::string("AUTO_SETTING")+#name),default).value<type>()
#endif//EXAMINATIO_VERBORUM_UTIL_H
