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
#ifndef QG_LINEANGLEOPTIONS_H
#define QG_LINEANGLEOPTIONS_H

#include<memory>
#include<QWidget>

class RS_ActionInterface;
class RS_ActionDrawLineAngle;
namespace Ui {
class Ui_LineAngleOptions;
}

class QG_LineAngleOptions : public QWidget
{
    Q_OBJECT

public:
    QG_LineAngleOptions(QWidget* parent = 0, Qt::WindowFlags fl = {});
    ~QG_LineAngleOptions();

public slots:
    virtual void setAction( RS_ActionInterface * a, bool update );
    virtual void updateAngle( const QString & a );
    virtual void updateLength( const QString & l );
    virtual void updateSnapPoint( int sp );

protected:
    RS_ActionDrawLineAngle* action = nullptr;

protected slots:
    virtual void languageChange();

private:
	void saveSettings();
	std::unique_ptr<Ui::Ui_LineAngleOptions> ui;
	int m_snapPoint = 0;
	bool m_bFixedAngle = false;
};

#endif // QG_LINEANGLEOPTIONS_H
