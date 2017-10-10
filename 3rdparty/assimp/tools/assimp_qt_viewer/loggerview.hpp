/// \file   loggerview.hpp
/// \brief  Stream for Assimp logging subsystem.
/// \author smal.root@gmail.com
/// \date   2016

#pragma once

// Header files, Qt.
#include <QTextBrowser>

// Header files, Assimp.
#include <assimp/DefaultLogger.hpp>

/// \class CLoggerView
/// GUI-stream for Assimp logging subsytem. Get data for logging and write it to output widget.
class CLoggerView final : public Assimp::LogStream
{
private:

	QTextBrowser* mOutputWidget;///< Widget for displaying messages.

public:

	/// \fn explicit CLoggerView(QTextBrowser* pOutputWidget)
	/// Constructor.
	/// \param [in] pOutputWidget - pointer to output widget.
	explicit CLoggerView(QTextBrowser* pOutputWidget);

	/// \fn virtual void write(const char *pMessage)
	/// Write message to output widget. Used by Assimp.
	/// \param [in] pMessage - message for displaying.
	virtual void write(const char *pMessage);
};
