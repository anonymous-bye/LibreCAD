/****************************************************************************
**
** This file is part of the LibreCAD project, a 2D CAD program
**
** Copyright (C) 2010 R. van Twisk (librecad@rvt.dds.nl)
** Copyright (C) 2001-2003 RibbonSoft. All rights reserved.
**
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software 
** Foundation and appearing in the file gpl-2.0.txt included in the
** packaging of this file.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**
** This copyright notice MUST APPEAR in all copies of the script!  
**
**********************************************************************/


#ifndef RS_DEBUG_H
#define RS_DEBUG_H

#include <QTextStream>
#ifdef __hpux
#include <sys/_size_t.h>
#endif

class QString;

/** print out a debug header*/
#define DEBUG_HEADER debugHeader(__FILE__, __func__, __LINE__);
void debugHeader(char const* file, char const* func, int line);
#define RS_DEBUG RS_Debug::instance()
#define RS_DEBUG_VERBOSE DEBUG_HEADER \
	RS_Debug::instance()

// stream style logging
// Example: LC_LOG<<"logging debugging message"; // default log level: D_DEBUGGING
//          LC_LOG(D_ERROR)<<"Logging error message"; // specified logging level: D_ERROR
#define LC_LOG RS_Debug::Log()
#define LC_ERR RS_Debug::Log(RS_Debug::D_ERROR)

/**
 * Debugging facilities.
 *
 * @author Andrew Mustun
 */
class RS_Debug {

public:
    /**
     * Enum for debug levels. Only messages of the current
     * or a higher level are printed.
     * <ul>
     *  <li>D_NOTHING:  nothing
     *  <li>D_CRITICAL: critical messages
     *  <li>D_ERROR:    errors
     *  <li>D_WARNING:  warnings
     *  <li>D_NOTICE:   notes
     *  <li>D_INFORMATIONAL: infos
     *  <li>D_DEBUGGING: very verbose
     * </ul>
     */
    enum RS_DebugLevel { D_NOTHING,
                         D_CRITICAL,
                         D_ERROR,
                         D_WARNING,
                         D_NOTICE,
                         D_INFORMATIONAL,
                         D_DEBUGGING };

private:
    RS_Debug();
    RS_Debug(const RS_Debug&)=delete;
	RS_Debug& operator = (const RS_Debug&)=delete;
	RS_Debug(RS_Debug&&)=delete;
	RS_Debug& operator = (RS_Debug&&)=delete;

public:
    ~RS_Debug();
    static RS_Debug* instance();

    /**
     * @brief The LogStream class: Support for debugging info by the c++ stream style
     *
     * Example:
     *      LC_LOG(D_ERROR)<<"Log text";
     */
    class LogStream : public QTextStream {
    public:
        LogStream(RS_DebugLevel level = D_DEBUGGING);
        ~LogStream() override;

        LogStream& operator () (RS_DebugLevel level)
        {
            m_debugLevel = level;
            return *this;
        }

    private:
        QString m_string;
        RS_DebugLevel m_debugLevel;
    };

    static LogStream Log(RS_DebugLevel level = D_DEBUGGING);

    void setLevel(RS_DebugLevel level);
    RS_DebugLevel getLevel();
    void print(RS_DebugLevel level, const char* format ...);
    void print(const char* format ...);
    void print(const QString& text);
    void printUnicode(const QString& text);
    void timestamp();
    void setStream(FILE* s) {
        stream = s;
    }

private:
    RS_DebugLevel debugLevel = D_INFORMATIONAL;
    FILE* stream = nullptr;
};

#endif
// EOF
