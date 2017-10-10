/// \file   loggerview.cpp
/// \brief  Stream for Assimp logging subsystem.
/// \author smal.root@gmail.com
/// \date   2016

#include "loggerview.hpp"

// Header files, Qt.
#include <QTime>

CLoggerView::CLoggerView(QTextBrowser* pOutputWidget)
	: mOutputWidget(pOutputWidget)
{
}

void CLoggerView::write(const char *pMessage)
{
	mOutputWidget->insertPlainText(QString("[%1] %2").arg(QTime::currentTime().toString()).arg(pMessage));
}
